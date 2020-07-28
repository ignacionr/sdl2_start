#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class SDLSurface
{
public:
    SDLSurface(SDL_Window *window)
    {
        _surface = SDL_GetWindowSurface(window);
    }
    SDLSurface(const char *filename)
    {
        _surface = IMG_Load(filename);
        if (!_surface)
        {
            std::cerr << "Could not read " << filename << std::endl;
        }
    }
    ~SDLSurface()
    {
        if (_surface)
        {
            SDL_FreeSurface(_surface);
        }
    }

    auto format() const { return _surface->format; }
    operator SDL_Surface *() { return _surface; }

private:
    SDL_Surface *_surface;
};
