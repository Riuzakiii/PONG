#include "Button.h"

Button::Button (const std::array<std::string, 3>& paths_)
{
    std::copy (paths_.begin(), paths_.end(), paths.begin());
}

void Button::render (SDL_Renderer*& gRenderer)
{
    if (textures[ButtonStatus::Default].get() == nullptr)
    {
        textures[ButtonStatus::Default].loadFromPath (
            gRenderer, paths[ButtonStatus::Default]);
    }
    if (textures[ButtonStatus::Clicked].get() == nullptr)
    {
        textures[ButtonStatus::Clicked].loadFromPath (
            gRenderer, paths[ButtonStatus::Clicked]);
    }
    if (textures[ButtonStatus::Hover].get() == nullptr)
    {
        textures[ButtonStatus::Hover].loadFromPath (gRenderer,
                                                    paths[ButtonStatus::Hover]);
    }

    if (clicked)
    {
        textures[ButtonStatus::Clicked].render (gRenderer, m_x, m_y);
    }
    else if (hover)
    {
        textures[ButtonStatus::Hover].render (gRenderer, m_x, m_y);
    }
    else
    {
        textures[ButtonStatus::Default].render (gRenderer, m_x, m_y);
    }
}

void Button::onEvent (const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN ||
        event.type == SDL_MOUSEBUTTONUP)
    {
        int posX = 0;
        int posY = 0;

        SDL_GetMouseState (&posX, &posY);

        const bool insideX =
            posX <= (m_x + textures[ButtonStatus::Default].getWidth()) &&
            posX >= m_x;
        const bool insideY =
            posY <= (m_y + textures[ButtonStatus::Default].getHeight()) &&
            posY >= m_y;

        if (insideX && insideY)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                onClick();
                clicked = true;
                return;
            }
            clicked = false;
            hover = true;
            return;
        }
    }

    clicked = false;
    hover = false;
}
