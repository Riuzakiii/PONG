#include "ScoreTexts.h"

ScoreTexts::ScoreTexts()
{
    addElement (textScore1);
    addElement (textScore2);
}

void ScoreTexts::onEvent (const SDL_Event& /*event*/) {}

void ScoreTexts::render (SDL_Renderer*& /*renderer*/)
{
}

void ScoreTexts::setTextScore1 (unsigned int& score1)
{
    std::stringstream sstr;
    sstr << "Score 1 " << (int)score1;
    textScore1.setText (sstr.str());
}

void ScoreTexts::setTextScore2 (unsigned int& score2)
{
    std::stringstream sstr;
    sstr << "Score 2 " << (int)score2;
    textScore2.setText (sstr.str());
}

void ScoreTexts::setBounds (int x, int y, int width, int height)
{
    GUIElement::setBounds (x, y, width, height);
    textScore2.setBounds (x, 0, width, (int)std::round (0.1 * height));
    textScore1.setBounds (x,
                          height - (int)std::round (0.1 * height),
                          width,
                          (int)std::round (0.1 * height));
}
