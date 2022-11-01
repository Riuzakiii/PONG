#pragma once

extern "C"
{
#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <SDL_ttf.h>
}

#include "GUIElement.h"
#include "Texture.h"
#include <string>

class Text : public GUIElement
{
public:
    Text() = default;
    Text (std::string& text, const std::string& fontPath, const int ptsize);
    Text (std::string&& text, const std::string& fontPath, const int ptsize);
    ~Text();

    void render (SDL_Renderer*&) override;
    void onEvent (const SDL_Event&) override;
    void setText (const std::string& text);
    void setText (std::string&& text);
    bool setFont (const std::string& fontPath, const int ptsize);
    void setColor (const uint8_t r,
                   const uint8_t g,
                   const uint8_t b,
                   const uint8_t a);

private:
    std::string text = "";
    SDL_Color textColor{0, 0, 0, 255};
    int ptsize = 11;
    TTF_Font* font = nullptr;
    Texture texture;
    bool reload = true;
};
