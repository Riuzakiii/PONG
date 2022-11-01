#include "Score.h"

Score::Score (const unsigned int& MAX_SCORE,
              unsigned int& score1,
              unsigned int& score2,
              Engine& engine,
              ScoreTexts& scoreTexts,
              Text& winOrLooseText)
    : MAX_SCORE (MAX_SCORE), score1 (score1), score2 (score2), engine (engine),
      scoreTexts (scoreTexts), winOrLooseText (winOrLooseText){};

void Score::callback (const Collision& collision)
{
    if (dynamic_cast<Ground*> (collision.getSource()) != nullptr)
    {
        auto side = collision.getSide();

        bool scored = false;

        if ((side ^ Collision::Up) == 0)
        {
            ++score1;
            scoreTexts.setTextScore1 (score1);
            scored = true;
        }
        else if ((side ^ Collision::Down) == 0)
        {
            ++score2;
            scoreTexts.setTextScore2 (score2);
            scored = true;
        }

        if (scored)
        {
            auto& objs = engine.getObjects();
            for (auto& obj : objs)
            {
                obj->reset();
            }
        }

        if (score1 >= MAX_SCORE)
        {
            winOrLooseText.setText ("You win !");
            winOrLooseText.setVisible (true);
        }
        else if (score2 >= MAX_SCORE)
        {
            winOrLooseText.setText ("You loose !");
            winOrLooseText.setVisible (true);
        }
    }
}
