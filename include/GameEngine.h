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

class GameEngine : public Engine
{
public:
    GameEngine (const int& width,
                const int& height,
                std::vector<std::unique_ptr<Object>>&& objects);
};
