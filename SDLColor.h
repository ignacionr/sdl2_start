#include <SDL2/SDL.h>

class SDLColor
{
public:
    SDLColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = SDL_ALPHA_OPAQUE)
        : _sdlColor{red, green, blue, alpha} // initialize the values / not sending the temp objects
    {
        //_sdlColor = SDL_Color{red, green, blue, alpha}; // assign values in positions - struct this creates temp color and copy
    }

    operator SDL_Color()
    {
        return _sdlColor;
    }

private:
    SDL_Color _sdlColor;
};
