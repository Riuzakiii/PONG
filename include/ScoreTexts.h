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

class ScoreTexts : public GUIElement
{
public:
    ScoreTexts();

    void onEvent (const SDL_Event&) override;

    void render (SDL_Renderer*&) override;

    void setTextScore1 (unsigned int& score1);

    void setTextScore2 (unsigned int& score2);

    void setBounds (int x, int y, int width, int height);

private:
    Text textScore1{"Score 1", "media/Roboto-Regular.ttf", 15};
    Text textScore2{"Score 2", "media/Roboto-Regular.ttf", 15};
};
