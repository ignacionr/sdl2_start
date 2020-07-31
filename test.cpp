#include <SDL2/SDL.h>
#include <stdio.h>
#include <memory>
#include <iostream>
#include <list>

#include "sdlsurface.h"
#include "scene.h"
#include "scenemanager.h"
#include "sdltexture.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Program
{
public:
    ~Program();
    int run();

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

int Program::run()
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
    SDL_Rect rc{0, 0, 100, 100};

    auto renderer{SDL_CreateRenderer(_window,
                                     -1,
                                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE)}; // render is an abstract class
    if (!renderer)
    {
        std::cerr << "Could not create a renderer :" << SDL_GetError() << std::endl;
        return -1;
    }

    std::unique_ptr<SDLTexture> cat_texture;
    {
        SDLSurface cat("rsc/download.jpeg");
        cat_texture = std::make_unique<SDLTexture>(renderer, cat);
    } // the destructor for cat is called right here

    SDL_Event ev;
    int center = SCREEN_HEIGHT / 2;
    int speed = 4;
    for (auto waitResult = SDL_PollEvent(&ev); !waitResult || ev.type != SDL_QUIT; waitResult = SDL_PollEvent(&ev))
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, *cat_texture, NULL, &rc);

        // HOMEWORK: the speed of movement is currently 4 (static)
        //           SCREEN_HEIGHT is the total of the movement, after which it will wrapup [0-SCREEN_HEIGHT)
        //           let's make it so the speed is greater the farther the image is from the center
        //           center = SCREEN_HEIGHT / 2
        //           distance_to_center = abs(rc.y - center)
        if (rc.y > center)
        {
            rc.y += speed * 2;
        }
        else
        {
            rc.y += speed;
        }

        rc.y %= SCREEN_HEIGHT;
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}

int main(int argc, char *args[])
{
    // create an instance of the program
    Program program;
    return program.run();
    // run it
    // return the value yielded
}