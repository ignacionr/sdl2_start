#include <SDL2/SDL.h>
#include <stdio.h>
#include <memory>

#include "sdlsurface.h"
#include "scene.h"
#include "scenemanager.h"
#include "sdltexture.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[])
{
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
        "hello_sdl2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }
    // SDLSurface screenSurface(window);
    // auto white = SDL_MapRGB(screenSurface.format(), 0xFF, 0xFF, 0xFF);
    // auto red = SDL_MapRGB(screenSurface.format(), 0xFF, 0x0, 0x0);
    SDL_Rect rc{0, 0, 100, 100};

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        return -1;
    }

    std::unique_ptr<SDLTexture> cat_texture;
    {
        SDLSurface cat("rsc/download.jpeg");
        cat_texture = std::make_unique<SDLTexture>(renderer, cat);
    }

    SDL_Event ev;
    for (auto waitResult = SDL_PollEvent(&ev); !waitResult || ev.type != SDL_QUIT; waitResult = SDL_PollEvent(&ev))
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &rc);

        SDL_RenderCopy(renderer, *cat_texture, NULL, &rc);

        // SDL_FillRect(screenSurface, NULL, white);
        // SDL_FillRect(screenSurface, &rc, red);
        rc.y += 4;
        rc.y %= SCREEN_HEIGHT;
        SDL_RenderPresent(renderer);
        // SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}