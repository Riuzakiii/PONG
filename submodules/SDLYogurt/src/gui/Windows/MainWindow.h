#pragma once
extern "C"
{
#include <SDL2/SDL.h>
#include <SDL_image.h>
}
#include "Engine.h"
#include "GUIElement.h"
#include "Timer.h"
#include "Window.h"
#include <string>
#include <vector>

class MainWindow : public Window
{
public:
    MainWindow (const std::string& title, const int width, const int height);
    virtual ~MainWindow();

    /** @fn bool run()
     *  @brief Run the event and rendering loops. Will call the guiElements
     * onEvent() and render().
     */
    bool run();

    void addElement (GUIElement& element) override;

    [[nodiscard]] double getFPS() const;

    void setEngine (Engine*);

private:
    /** @fn bool init()
     *  @brief Load the main Window, main surface and renderer
     */
    bool init() override;

    [[nodiscard]] static int EventFilter (void*, SDL_Event*);

    SDL_Renderer* gRenderer = nullptr;
    std::vector<GUIElement*> guiElements;
    Timer fpsTimer;
    double fps = 0.;
    Timer fpsCap;

    static constexpr auto N_FRAMES_FPS = 10;
    static constexpr int N_FPS_FRAME = 60;
    static constexpr int N_MS_FRAME = (int)((1. / N_FPS_FRAME) * 1000);

    Engine* engine = nullptr;
};
