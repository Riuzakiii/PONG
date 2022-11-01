#include "Application.h"
#include <cassert>

Application::Application() { init(); }

Application::~Application() { exit(); }

bool Application::init (const uint16_t flags)
{
    if (SDL_Init (flags) < 0)
    {
        return false;
    }
    initImage();
    initTTF();
    SDL_LogSetAllPriority (SDL_LOG_PRIORITY_DEBUG);
    return true;
}

bool Application::initImage()
{
    if ((IMG_Init (IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
    {
        SDL_LogInfo (SDL_LOG_CATEGORY_APPLICATION, "Could not load PNG Module");// NOLINT(cppcoreguidelines-pro-type-vararg)
        return false;
    }
    return true;
}

bool Application::initTTF()
{
    if (TTF_Init() == -1)
    {
        SDL_LogWarn (SDL_LOG_CATEGORY_APPLICATION, "Could not load SDL TTF");// NOLINT(cppcoreguidelines-pro-type-vararg)
        return false;
    }
    return true;
}

void Application::exit()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
