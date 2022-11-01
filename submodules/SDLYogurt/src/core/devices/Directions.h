#pragma once

#include "Device.h"
extern "C"
{
#include <SDL2/SDL.h>
}

class Directions : public Device
{
public:
    enum States
    {
        None = 0,
        Up = 2,
        Down = 4,
        Left = 8,
        Right = 16
    };

    Directions()
        : Device ("directions"), statesPtr (SDL_GetKeyboardState (nullptr))
    {
    }

    [[nodiscard]] virtual int getState() const override
    {
        int state = States::None;

        if (statesPtr[SDL_SCANCODE_UP])
        {
            state += States::Up;
        }
        if (statesPtr[SDL_SCANCODE_DOWN])
        {
            state += States::Down;
        }
        if (statesPtr[SDL_SCANCODE_LEFT])
        {
            state += States::Left;
        }
        if (statesPtr[SDL_SCANCODE_RIGHT])
        {
            state += States::Right;
        }
        return state;
    }

private:
    const uint8_t* statesPtr = nullptr;
};
