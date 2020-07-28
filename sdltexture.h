#include <SDL2/SDL.h>

class SDLTexture
{
public:
    SDLTexture(SDL_Renderer *renderer, SDL_Surface *surface)
    {
        _texture = SDL_CreateTextureFromSurface(renderer, surface);
    }
    ~SDLTexture()
    {
        if (_texture)
        {
            SDL_DestroyTexture(_texture);
        }
    }

    operator SDL_Texture *()
    {
        return _texture;
    }

private:
    SDL_Texture *_texture;
};
