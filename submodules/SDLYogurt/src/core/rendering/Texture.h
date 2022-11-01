#pragma once
extern "C"
{
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}
#include <cassert>
#include <string>

class Texture
{
public:
    Texture() = default;
    Texture (SDL_Renderer*& gRenderer, const std::string& path);
    ~Texture();

    /**
     * Load texture from PNG file using SDL_Image
     */
    bool loadFromPath (SDL_Renderer*& gRenderer, const std::string& path);
    SDL_Texture* get();
    void render (SDL_Renderer*& gRenderer,
                 const int x,
                 const int y,
                 SDL_Rect* clip = nullptr,
                 double angle = 0.0,
                 SDL_Point* center = nullptr,
                 SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Creates image from font string
    bool loadFromRenderedText (SDL_Renderer*& gRenderer,
                               TTF_Font*& font,
                               const std::string& textureText,
                               SDL_Color textColor);

    void setColor (const uint8_t red, const uint8_t green, const uint8_t blue);

    // Set blending
    void setBlendMode (const SDL_BlendMode blending);

    // Set alpha modulatio
    void setAlpha (const uint8_t alpha);

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;

    bool isNull() const;

private:
    /**
     * Free the texture using SDL function SDL_DestroyTexture
     */
    void free();

    SDL_Texture* texture = nullptr;

    int w = 0;
    int h = 0;
};
