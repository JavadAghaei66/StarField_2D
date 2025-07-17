#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define STAR_COUNT 1000

#define CENTER_X (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

#define COLOR_WHITE SDL_MapRGB(surface->format, 255, 255, 255)
#define COLOR_BLACK SDL_MapRGB(surface->format, 0, 0, 0)

struct Star
{
    double x, y;
    double vx, vy;
    double speedFactor;
};

class GameEngine
{
private:
    bool is_running;
    int point_size;
    double speed;
    struct Star stars[STAR_COUNT];
    SDL_Window *window;
    SDL_Surface *surface;

public:
    GameEngine();
    bool InitGameEngine();
    void InitGeneration();
    void Delay();
    struct Star NewStar();
    bool IsRunning();
    void Render();
    void MoveStars();
    void Input();
    void Quit();
};