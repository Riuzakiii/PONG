#include "Texture.h"

Texture::Texture (SDL_Renderer*& gRenderer, const std::string& path)
{
    loadFromPath (gRenderer, path);
}

Texture::~Texture()
{
    free();
}

void Texture::free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture (texture);
        texture = nullptr;
    }
}

SDL_Texture* Texture::get() { return texture; }

bool Texture::loadFromPath (SDL_Renderer*& gRenderer, const std::string& path)
{
    free();

    SDL_Surface* loadedSurface = IMG_Load (path.c_str());

    if (loadedSurface == nullptr)
    {
        SDL_LogInfo (SDL_LOG_CATEGORY_APPLICATION, "Could not load image");// NOLINT(cppcoreguidelines-pro-type-vararg)
        assert (false);
    }
    else
    {
        w = loadedSurface->w;
        h = loadedSurface->h;
        texture = SDL_CreateTextureFromSurface (gRenderer, loadedSurface);
        if (texture == nullptr)
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
            SDL_LogInfo (SDL_LOG_CATEGORY_APPLICATION,
                         "Could not load texture");
            // NOLINTEND(cppcoreguidelines-pro-type-vararg)
            assert (false);
        }
        else
        {
            return true;
        }
        SDL_FreeSurface (loadedSurface);
    }
    return false;
}

void Texture::render (SDL_Renderer*& gRenderer,
                      const int x,
                      const int y,
                      SDL_Rect* clip,
                      double angle,
                      SDL_Point* center,
                      SDL_RendererFlip flip)
{
    SDL_Rect renderRect{x, y, w, h};
    if (clip != nullptr)
    {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }
    SDL_RenderCopyEx (
        gRenderer, texture, clip, &renderRect, angle, center, flip);
}

// Creates image from font string
bool Texture::loadFromRenderedText (SDL_Renderer*& gRenderer,
                                    TTF_Font*& font,
                                    const std::string& textureText,
                                    SDL_Color textColor)
{
    if (texture != nullptr)
    {
        free();
    }

    SDL_Surface* textSurface =
        TTF_RenderText_Solid (font, textureText.c_str(), textColor);

    if (textSurface == nullptr)
    {
        // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
        SDL_LogWarn (SDL_LOG_CATEGORY_APPLICATION,
                     "Could not render text to surface");// NOLINT(cppcoreguidelines-pro-type-vararg)
        // NOLINTEND(cppcoreguidelines-pro-type-vararg)
        return false;
    }

    texture = SDL_CreateTextureFromSurface (gRenderer, textSurface);
    if (texture == nullptr)
    {
        // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
        SDL_LogWarn (SDL_LOG_CATEGORY_APPLICATION,
                        "Could not make texture from surface");// NOLINT(cppcoreguidelines-pro-type-vararg)
        // NOLINTEND(cppcoreguidelines-pro-type-vararg)
        return false;
    }
    // Get image dimensions
    w = textSurface->w;
    h = textSurface->h;

    SDL_FreeSurface (textSurface);
    return texture != nullptr;
}

void Texture::setColor (const uint8_t red,
                        const uint8_t green,
                        const uint8_t blue)
{
    SDL_SetTextureColorMod (texture, red, green, blue);
}

void Texture::setAlpha (const uint8_t alpha)
{
    SDL_SetTextureAlphaMod (texture, alpha);
}

void Texture::setBlendMode (const SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode (texture, blending);
}

int Texture::getWidth() const { return w; }

int Texture::getHeight() const { return h; }

bool Texture::isNull() const { return texture == nullptr; }
