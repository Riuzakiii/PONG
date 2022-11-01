#include "Text.h"
#include <cassert>

Text::Text (std::string& text, const std::string& fontPath, const int ptsize)
    : text (text)
{
    setFont (fontPath, ptsize);
}
Text::Text (std::string&& text, const std::string& fontPath, const int ptsize)
    : text (std::move (text))
{
    setFont (fontPath, ptsize);
}

Text::~Text()
{
    if (font != nullptr)
    {
        TTF_CloseFont (font);
    }
}

void Text::render (SDL_Renderer*& gRenderer)
{
    if (reload)
    {
        if (font != nullptr)
        {
            texture.loadFromRenderedText (gRenderer, font, text, textColor);
            reload = false;
        }
    }
    if (!texture.isNull())
    {
        texture.render (gRenderer, m_x, m_y);
    }
}

void Text::onEvent (const SDL_Event& /*event*/) {}

void Text::setText (const std::string& newText)
{
    text = newText;
    reload = true;
}

void Text::setText (std::string&& newText)
{
    text = std::move (newText);
    reload = true;
}

bool Text::setFont (const std::string& fontPath, const int ptsize_)
{
    if (font != nullptr)
    {
        TTF_CloseFont (font);
    }
    ptsize = ptsize_;
    font = TTF_OpenFont (fontPath.c_str(), ptsize);

    return font == nullptr;
}

void Text::setColor (const uint8_t r,
                     const uint8_t g,
                     const uint8_t b,
                     const uint8_t a)
{
    textColor = SDL_Color{r, g, b, a};
}
