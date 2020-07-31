#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_SysWMinfo info;

    if (SDL_Init(0))
    {
        puts(SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
    if (!window)
    {
        puts(SDL_GetError());
        return -1;
    }

    SDL_VERSION(&info.version); /* initialize info structure with SDL version info */

    if (SDL_GetWindowWMInfo(window, &info))
    { /* the call returns true on success */
        /* success */
        const char *subsystem = "an unknown system!";
        switch (info.subsystem)
        {
        case SDL_SYSWM_UNKNOWN:
            break;
        case SDL_SYSWM_WINDOWS:
            subsystem = "Microsoft Windows(TM)";
            break;
        case SDL_SYSWM_X11:
            subsystem = "X Window System";
            break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
        case SDL_SYSWM_WINRT:
            subsystem = "WinRT";
            break;
#endif
        case SDL_SYSWM_DIRECTFB:
            subsystem = "DirectFB";
            break;
        case SDL_SYSWM_COCOA:
            subsystem = "Apple OS X";
            break;
        case SDL_SYSWM_UIKIT:
            subsystem = "UIKit";
            break;
#if SDL_VERSION_ATLEAST(2, 0, 2)
        case SDL_SYSWM_WAYLAND:
            subsystem = "Wayland";
            break;
        case SDL_SYSWM_MIR:
            subsystem = "Mir";
            break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
        case SDL_SYSWM_ANDROID:
            subsystem = "Android";
            break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_SYSWM_VIVANTE:
            subsystem = "Vivante";
            break;
        case SDL_SYSWM_OS2:
            subsystem = "OS/2";
            break;
#endif
        }

        SDL_Log("This program is running SDL version %d.%d.%d on %s",
                (int)info.version.major,
                (int)info.version.minor,
                (int)info.version.patch,
                subsystem);
    }
    else
    {
        /* call failed */
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't get window information: %s", SDL_GetError());
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
