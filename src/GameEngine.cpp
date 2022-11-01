#include "GameEngine.h"

GameEngine::GameEngine (const int& width,
                        const int& height,
                        std::vector<std::unique_ptr<Object>>&& objects)
    : Engine (width, height, std::move (objects))
{
    addDevice (std::make_unique<Directions>());
}
