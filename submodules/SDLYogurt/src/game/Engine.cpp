#include "Engine.h"

Engine::Engine (const int& width,
                const int& height,
                std::vector<std::unique_ptr<Object>>&& objects)
    : objects (std::move (objects)), physics ({width, height}){};

void Engine::render (SDL_Renderer*& gRenderer)
{
    for (const auto& object : objects)
    {
        object->render (gRenderer);
    }
}

void Engine::onEvent (SDL_Event event)
{
    for (const auto& object : objects)
    {
        object->onEvent (event);
    }
}

void Engine::onDeviceState()
{
    for (const auto& device : devices)
    {
        const auto state = device->getState();
        for (const auto& object : objects)
        {
            object->onDeviceState (state);
        }
    }
}

void Engine::runPhysics() { physics.compute (objects); }

std::vector<std::unique_ptr<Object>>& Engine::getObjects() { return objects; }

void Engine::addDevice (std::unique_ptr<Device>&& device) { devices.push_back (std::move(device)); }
