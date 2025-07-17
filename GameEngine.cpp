#include "GameEngine.h"

GameEngine::GameEngine()
{
    is_running = true;
    point_size = 2;
    speed = 0.003;
}

// Initializes SDL, creates window & surface, and generates stars
bool GameEngine::InitGameEngine()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow(
        "StarField",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!window)
    {
        cout << "Window creation failed....\n";
        return false;
    }

    surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        cout << "Surface creation failed: " << SDL_GetError() << endl;
        return false;
    }

    InitGeneration();
    return true;
}

// Fills the stars array with STAR_COUNT new random stars
void GameEngine::InitGeneration()
{
    for (int i = 0; i < STAR_COUNT; i++)
        stars[i] = NewStar();
}

void GameEngine::Delay()
{
    SDL_Delay(1000 * speed);
}

// Returns a new star with random position, velocity, and speedFactor
struct Star GameEngine::NewStar()
{
    double x = ((double)rand() / RAND_MAX) * 200 - 100;
    double y = ((double)rand() / RAND_MAX) * 200 - 100;
    double vx = speed * ((double)rand() / RAND_MAX) - 0.5;
    double vy = speed * ((double)rand() / RAND_MAX) - 0.5;
    double speedFactor = ((double)rand() / RAND_MAX) * 0.5;
    return Star{x, y, vx, vy, speedFactor};
}

bool GameEngine::IsRunning()
{
    return is_running;
}

// Draws black background and renders each star
void GameEngine::Render()
{
    SDL_Rect black_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_FillRect(surface, &black_rect, COLOR_BLACK);

    for (int i = 0; i < STAR_COUNT; i++)
    {
        struct Star *pstar = &stars[i];
        double x = pstar->x + CENTER_X;
        double y = pstar->y + CENTER_Y;
        int size = (int)(pstar->speedFactor * 5);

        SDL_Rect star = (SDL_Rect){x, y, size, size};
        SDL_FillRect(surface, &star, COLOR_WHITE);
    }

    SDL_UpdateWindowSurface(window);
}

// Updates star positions and regenerates stars that go off-screen
void GameEngine::MoveStars()
{
    for (int i = 0; i < STAR_COUNT; i++)
    {
        struct Star *pstar = &stars[i];

        // Update position
        pstar->x = pstar->x + pstar->vx;
        pstar->y = pstar->y + pstar->vy;

        // Accelerate outward
        pstar->vx = pstar->speedFactor * (pstar->x) / 100;
        pstar->vy = pstar->speedFactor * (pstar->y) / 100;

        // If out of screen, replace with a new star
        if (pstar->x + CENTER_X < 0 || pstar->x + CENTER_X > WINDOW_WIDTH ||
            pstar->y + CENTER_Y < 0 || pstar->y + CENTER_Y > WINDOW_HEIGHT)
        {
            stars[i] = NewStar();
        }
    }
}

// Handles SDL events (currently only quit)
void GameEngine::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.quit.type == SDL_QUIT)
            is_running = false;
    }
}

// Cleans up resources and shuts down SDL
void GameEngine::Quit()
{
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}
