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

class FreeBall : public Object
{
public:
    FreeBall (Position position, Velocity velocity);

    Position getNextPos (const Collision& collision) override;

    void render (SDL_Renderer*& gRenderer) override;

    void reset() override;

private:
    int currentState = Directions::None;
    int tickMs = 0;
    Texture texture;
    Timer timer;
    Position initPos;
};
