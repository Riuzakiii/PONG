#pragma once
extern "C"
{
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
}

/** Initialize and exit SDL Lib and Modules.
 *
 */
class Application
{
public:
    Application();

    ~Application();

private:
    static bool initImage();
    static bool initTTF();
    static bool init (const uint16_t flags = SDL_INIT_VIDEO);
    static void exit();
};
