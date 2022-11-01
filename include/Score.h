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
#include "ScoreTexts.h"
#include "Text.h"
#include "Texture.h"
#include "Timer.h"

class Score : public Collision::Listener
{
public:
    Score (const unsigned int& MAX_SCORE,
           unsigned int& score1,
           unsigned int& score2,
           Engine& engine,
           ScoreTexts& scoreTexts,
           Text& winOrLooseText);

    void callback (const Collision& collision) override;

private:
    const unsigned int& MAX_SCORE = 0;
    unsigned int score1 = 0;
    unsigned int score2 = 0;
    Engine& engine;
    ScoreTexts& scoreTexts;
    Text& winOrLooseText;
};
