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

class Wall : public Object
{
public:
    Wall (Position position, Velocity velocity);

    Position getNextPos (const Collision& collision) override;

    void render (SDL_Renderer*& gRenderer) override;

    void onDeviceState (const int state) override;

    void reset() override;

private:
    Texture texture;
    int currentState = Directions::None;
    Timer timer;
    int tickMs = 0;
};

class MovingWall : public Object
{
public:
    MovingWall (Position position, Velocity velocity);

    Position getNextPos (const Collision& collision) override;

    void render (SDL_Renderer*& gRenderer) override;

    void onDeviceState (const int state) override;

    void reset() override;

private:
    Texture texture;
    int currentState = Directions::None;
    Timer timer;
    Position initPos;
    int tickMs = 0;
};
