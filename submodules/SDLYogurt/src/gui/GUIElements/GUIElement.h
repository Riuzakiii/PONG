#pragma once
extern "C"
{
#include <SDL2/SDL.h>
#include <SDL_image.h>
}
#include <vector>

struct GUIElement;

struct GUIElement
{
    virtual void render (SDL_Renderer*&) = 0;
    virtual void onEvent (const SDL_Event&){};
    virtual void setBounds (const int x, const int y, int width, int height)
    {
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
    }

    virtual void addElement (GUIElement& element)
    {
        children.emplace_back (&element);
        element.parents.emplace_back (this);
    }

    void renderAll (SDL_Renderer*& gRenderer)
    {
        render (gRenderer);
        for (auto*& child : children)
        {
            child->render (gRenderer);
        }
    }

    void setVisible (bool newVisible) { visible = newVisible; }

    int m_x = 0;
    int m_y = 0;
    int m_width = 0;
    int m_height = 0;
    bool visible = true;

    std::vector<GUIElement*> children;
    std::vector<GUIElement*> parents;
};
