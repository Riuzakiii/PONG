#pragma once
extern "C"
{
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
}
#include "GUIElement.h"
#include "Texture.h"
#include <string>

class Image : public GUIElement
{
public:
    Image (std::string path);

    void render (SDL_Renderer*&) override;
    void onEvent (const SDL_Event& event) override;

private:
    std::string path;
    Texture texture;
};
