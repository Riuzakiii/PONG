#include "Gamepad.h"

Gamepad::Gamepad (const std::string& name, const uint16_t JOYSTICK_DEADZONE)
    : Device (name), JOYSTICK_DEADZONE (JOYSTICK_DEADZONE)
{
}

Gamepad::~Gamepad() { gamepad = nullptr; }

bool Gamepad::init()
{
    if (SDL_NumJoysticks() < 1)
    {
        SDL_LogWarn (SDL_LOG_CATEGORY_APPLICATION, "No joystick connected");// NOLINT(cppcoreguidelines-pro-type-vararg)
        return false;
    }

    gamepad = SDL_JoystickOpen (0);
    if (gamepad == nullptr)
    {
        SDL_LogWarn (SDL_LOG_CATEGORY_APPLICATION, "Could not open controller");// NOLINT(cppcoreguidelines-pro-type-vararg)
        return false;
    }
    return true;
}

double Gamepad::getAngle (const bool flip) const
{
    double angle = 0.;
    double flip_coeff = 1.;
    if (flip)
    {
        flip_coeff = -1.;
    }
    if (flip_coeff * x > 0)
    {
        angle = std::atan ((double)y / (double)x * flip_coeff);
    }
    else
    {
        angle = pi - std::atan (-1. * (double)y / (double)x * flip_coeff);
    }

    if (angle > pi)
    {
        return angle - 2. * pi;// NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    }
    return angle;
}

double Gamepad::toDeg (const double angleRad) { return 180. * angleRad / pi; }// NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

void Gamepad::setY (const int16_t& newY) { y = newY; }
void Gamepad::setX (const int16_t& newX) { x = newX; }

uint16_t Gamepad::getDeadzone() const { return JOYSTICK_DEADZONE; }
