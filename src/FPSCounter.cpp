#include "FPSCounter.h"

FPSCounter::FPSCounter() { addElement (text); }

void FPSCounter::onEvent (const SDL_Event& /*event*/) {}

void FPSCounter::render (SDL_Renderer*& /*renderer*/)
{
    sstr.str ("");
    auto* window = dynamic_cast<MainWindow*> (parents.back());

    if (window != nullptr)
    {
        sstr << static_cast<int>(window->getFPS());
    }
    else
    {
        sstr << "No FPS";
    }
    text.setText (sstr.str());
}
