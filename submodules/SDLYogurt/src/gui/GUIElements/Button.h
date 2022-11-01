#pragma once
extern "C"
{
#include <SDL2/SDL.h>
}
#include "GUIElement.h"
#include "Texture.h"
#include <array>
#include <functional>
#include <string>

/** Button class. What is a button ?
 *  A click button launches an action uppon the click event. It must handle
 * click, hover events. On those event, must be redrawn. On click, must launch
 * an action. Callback ?
 */
class Button : public GUIElement
{
public:
    enum ButtonStatus
    {
        Default,
        Clicked,
        Hover
    };

    Button() = default;
    Button (const std::array<std::string, 3>& paths);

    void onEvent (const SDL_Event&) override;
    void render (SDL_Renderer*&) override;

    // void (*onClick)() = []{}; C-way
    std::function<void()> onClick = [] {}; // Modern C++ way

protected:
private:
    bool clicked = false;
    bool hover = false;
    std::array<Texture, 3> textures;
    std::array<std::string, 3> paths;
};
