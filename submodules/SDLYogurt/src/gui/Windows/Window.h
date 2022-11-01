#pragma once

#include "GUIElement.h"
extern "C"
{
#include <SDL2/SDL.h>
}
#include <string>

/** Window abstract class.
 *   @brief Window abstract class : a name, width, height, window ptr and
 * surface ptr.
 *
 */

class Window : public GUIElement
{
public:
    void render (SDL_Renderer*&){};

protected:
    Window() = default;
    Window (const std::string title, const int width, const int height)
        : title (title), width (width), height (height){};

    virtual bool init() = 0;
    SDL_Window* gWindow = nullptr;
    SDL_Surface* gSurface = nullptr;
    std::string title = "";
    int width = 0;
    int height = 0;
};
