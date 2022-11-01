#include "Image.h"

Image::Image (std::string path) : path (std::move(path)) {}

void Image::render (SDL_Renderer*& gRenderer)
{
    if (texture.get() == nullptr)
    {
        texture.loadFromPath (gRenderer, path);
    }
    if (texture.get() != nullptr)
    {
        texture.render (gRenderer, m_x, m_y);
    }
}

void Image::onEvent (const SDL_Event& /*event*/) {}
