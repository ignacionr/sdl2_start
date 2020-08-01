#include <SDL2/SDL.h>
#include <stdio.h>
#include <memory>
#include <iostream>
#include <list>
#include <thread>

#include "sdladapters.h"
#include "scene.h"
#include "scenemanager.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Program
{
public:
    ~Program();
    int run(int speed);
    int getOffset(int speed, int rectY, int center);

private:
    SDL_Window *_window{nullptr};
};

Program::~Program()
{
    if (_window)
    {
        SDL_DestroyWindow(_window);
    }
}

int Program::run(int speed)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // C Runtime writing to the stderr
        // fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        // fputs("This is an error!", stderr);
        // C++ Runtime writing to the stderr
        std::cerr << "Could not initialize sdl2: "
                  << SDL_GetError() << std::endl;
        return -1; // return to the OS
    }
    // SDL_Window *window = NULL;   // assingment initialization
    _window = SDL_CreateWindow(
        "hello_sdl2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (_window == NULL)
    {
        std::cerr << "Could not create a window :" << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Rect rc[3] = {{0, 0, 100, 100},
                      {100, 0, 100, 100},
                      {200, 0, 100, 100}};

    auto renderer{std::make_unique<sdl::Renderer>(_window)};

    std::unique_ptr<sdl::Texture> cat_texture;
    {
        sdl::Surface cat("rsc/download.jpeg");
        cat_texture = std::make_unique<sdl::Texture>(*renderer, cat);
    } // the destructor for cat is called right here

    SDL_Event ev;
    int center = (SCREEN_HEIGHT / 2) - rc[0].h;
    sdl::Color white{255, 255, 255};

    for (auto waitResult = SDL_PollEvent(&ev); !waitResult || ev.type != SDL_QUIT; waitResult = SDL_PollEvent(&ev))
    {
        renderer->SetDrawColor(white);
        //    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        renderer->Clear();
        //SDL_RenderClear(renderer);

        renderer->Copy(*cat_texture, nullptr, &rc[0]);
        renderer->Copy(*cat_texture, nullptr, &rc[1]);
        renderer->Copy(*cat_texture, nullptr, &rc[2]);

        // HOMEWORK: the speed of movement is currently 4 (static)
        //           SCREEN_HEIGHT is the total of the movement, after which it will wrapup [0-SCREEN_HEIGHT)
        //           let's make it so the speed is greater the farther the image is from the center
        //           center = SCREEN_HEIGHT / 2
        //           distance_to_center = abs(rc.y - center)
        // auto distance_to_center = abs(rc.y - center);
        // auto offset = distance_to_center * speed / center + 1;

        rc[0].y += getOffset(speed, rc[0].y, center);
        rc[0].y %= SCREEN_HEIGHT;

        rc[1].y += getOffset(12, rc[1].y, center);
        rc[1].y %= SCREEN_HEIGHT;

        rc[2].y += getOffset(14, rc[2].y, center);
        rc[2].y %= SCREEN_HEIGHT;

        renderer->Present();
    }

    SDL_Quit();
    return 0;
}

int Program::getOffset(int speed, int rectY, int center)
{
    auto distance_to_center = abs(rectY - center);
    return distance_to_center * speed / center + 1;
}

int main(int argc, char *args[])
{
    // create an instance of the program
    Program program;
    return program.run(10);
    // run it
    // return the value yielded
}