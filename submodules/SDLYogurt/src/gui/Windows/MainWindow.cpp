#include "MainWindow.h"

MainWindow::MainWindow (const std::string& title,
                        const int width,
                        const int height)
    : Window (title, width, height)
{
    SDL_SetEventFilter (EventFilter, nullptr);
}

MainWindow::~MainWindow()
{
    SDL_DestroyRenderer (gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow (gWindow);
    gWindow = nullptr;
}

bool MainWindow::init()
{
    gWindow = SDL_CreateWindow (title.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                width,
                                height,
                                SDL_WINDOW_SHOWN);

    if (gWindow == nullptr)
    {
        return false;
    }

    gSurface = SDL_GetWindowSurface (gWindow);
    if (gSurface == nullptr)
    {
        // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
        SDL_LogWarn (SDL_LOG_CATEGORY_APPLICATION,
                        "Could not load surface window");
        // NOLINTEND(cppcoreguidelines-pro-type-vararg)
        return false;
    }
    gRenderer = SDL_CreateRenderer (gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
        SDL_LogWarn (SDL_LOG_CATEGORY_APPLICATION,
                        "Could not load renderer");
        // NOLINTEND(cppcoreguidelines-pro-type-vararg)
        return false;
    }

    SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}

bool MainWindow::run()
{
    bool shouldQuit = false;
    SDL_Event event;
    if (!init())
    {
        // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
        SDL_LogInfo (SDL_LOG_CATEGORY_APPLICATION,
                     "Could not load main window or main surface");
        // NOLINTEND(cppcoreguidelines-pro-type-vararg)
        return false;
    }

    fpsTimer.start();
    auto fpsTime = fpsTimer.getTickMilliseconds();
    auto frameCount = 0;

    fpsCap.start();
    auto startTime = fpsCap.getTickMilliseconds();

    SDL_SetRenderDrawColor (gRenderer, 0xff, 0xff, 0xff, 0xff);

    while (!shouldQuit)
    {
        const auto tickBeforeNextFrame =
            fpsCap.getTickMilliseconds() - startTime;

        while (SDL_PollEvent (&event) != 0 &&
                tickBeforeNextFrame < N_MS_FRAME)
        {
            if (event.type == SDL_QUIT)
            {
                return true;
            }

            for (auto* child : children)
            {
                child->onEvent (event);
            }
            if (engine != nullptr)
            {
                engine->onEvent (event);
            }
        }
        if (engine != nullptr)
        {
            engine->onDeviceState();
        }
        if (tickBeforeNextFrame >= N_MS_FRAME)
        {
            SDL_RenderClear (gRenderer);
            for (auto* child : children)
            {
                if (child->visible)
                {
                    child->renderAll (gRenderer);
                }
            }
            ++frameCount;
            if (frameCount == N_FRAMES_FPS)
            {
                fps = 1000. * static_cast<double>(frameCount) /
                        static_cast<double>(fpsTimer.getTickMilliseconds() - fpsTime);
                frameCount = 0;
                fpsTime = fpsTimer.getTickMilliseconds();
            }

            if (engine != nullptr)
            {
                engine->runPhysics();
                engine->render (gRenderer);
            }
            SDL_RenderPresent (gRenderer);
            startTime = fpsCap.getTickMilliseconds();
        }
    }

    return true;
}

void MainWindow::addElement (GUIElement& element)
{
    children.emplace_back (&element);
    element.parents.emplace_back (this);
}

double MainWindow::getFPS() const { return fps; }

int MainWindow::EventFilter(void* /*userdata*/, SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_WINDOWEVENT:
        switch (event->window.event)
        {
        case SDL_WINDOWEVENT_MOVED:
            return 0;
            break;
        default:
            return 1;
            break;
        }
        break;
    default:
        return 1;
        break;
    }
}

void MainWindow::setEngine (Engine* enginePtr) { engine = enginePtr; }
