#pragma once
extern "C"
{
#include <SDL2/SDL.h>
}
#include "Device.h"
#include "Object.h"
#include "Physics.h"
#include <memory>
#include <vector>

class Engine
{
public:
    Engine (const int& width,
            const int& height,
            std::vector<std::unique_ptr<Object>>&& objects);
    virtual ~Engine() = default;

    virtual void render (SDL_Renderer*& gRenderer);

    virtual void onEvent (SDL_Event event);

    virtual void onDeviceState();

    void runPhysics();

    [[nodiscard]] std::vector<std::unique_ptr<Object>>& getObjects();

    void addDevice (std::unique_ptr<Device>&&); ///!takes ownership

protected:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Device>> devices;
    Physics physics;
};
