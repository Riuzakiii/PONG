#pragma once
extern "C"
{
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}
#include "Application.h"
#include "Directions.h"
#include "Engine.h"
#include "GUIElement.h"
#include "MainWindow.h"
#include "Object.h"
#include "Text.h"
#include "Texture.h"
#include "Timer.h"

#include <sstream>

class FPSCounter : public GUIElement
{
public:
    FPSCounter();

    void onEvent (const SDL_Event&) override;

    void render (SDL_Renderer*&) override;

protected:
private:
    Text text{"test", "media/Roboto-Regular.ttf", 50};
    std::stringstream sstr;
};
