
extern "C"
{
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}
#include "Application.h"
#include "GUIElement.h"
#include "MainWindow.h"

#include "Ball.h"
#include "FPSCounter.h"
#include "GameEngine.h"
#include "Score.h"
#include "ScoreTexts.h"
#include "Wall.h"

#include <memory>

#define DBG(msg) std::cout << (msg) << std::endl;

int main ([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    Application app;

    constexpr int width = 640;
    constexpr int height = 480;
    unsigned int score1 = 0;
    unsigned int score2 = 0;
    unsigned int MAX_SCORE = 2;

    std::vector<std::unique_ptr<Object>> objects;
    MainWindow mainWindow ("SDL", width, height);
    FPSCounter fpsCounter{};
    ScoreTexts scoreTexts;
    Text winOrLooseText{"You win", "media/Roboto-Regular.ttf", 50};
    mainWindow.addElement (fpsCounter);
    mainWindow.addElement (scoreTexts);
    mainWindow.addElement (winOrLooseText);

    scoreTexts.setBounds ((int)(0.8 * width), 0, (int)0.2 * width, height);
    winOrLooseText.setBounds ((int)(0.4 * width),
                              (int)(0.4 * height),
                              (int)(0.2 * width),
                              (int)(0.2 * height));
    winOrLooseText.setVisible (false);

    objects.push_back (
        std::make_unique<FreeBall> (Position{width / 2., height / 4. + 60}, Velocity{-100., -100.}));
    objects.push_back (
        std::make_unique<Wall> (Position{0.5 * width, 3. * height / 4.}, Velocity{200., 200.}));
    objects.push_back (
        std::make_unique<MovingWall> (Position{0.5 * width, height / 4.}, Velocity{200., 200.}));

    const auto& wallPosition = objects[1]->getPosition();
    const auto& movingWallPosition = objects[2]->getPosition();
    objects[1]->setPosition (
        {wallPosition.x - (double)objects[1]->getSize().width, wallPosition.y});
    objects[2]->setPosition (
        {movingWallPosition.x - (double)objects[2]->getSize().width,
         movingWallPosition.y});

    std::unique_ptr<GameEngine> engine =
        std::make_unique<GameEngine> (width, height, std::move (objects));
    Score score{MAX_SCORE, score1, score2, *engine, scoreTexts, winOrLooseText};

    engine->getObjects()[0]->addListener (&score);
    mainWindow.setEngine (engine.get());
    mainWindow.run();

    return 0;
}
