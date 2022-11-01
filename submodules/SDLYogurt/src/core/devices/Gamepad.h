#include <cmath>

#include "Device.h"
extern "C"
{
#include <SDL2/SDL.h>
}

class Gamepad : protected Device
{
public:
    Gamepad (const std::string& name, const uint16_t JOYSTICK_DEADZONE = 100);
    ~Gamepad();

    bool init() override;
    [[nodiscard]] double getAngle (const bool flip = true) const;
    [[nodiscard]] static double toDeg (const double angleRad);

    /**
     * @param y y val, y axis oriented upward
     */
    void setY (const int16_t& y);
    /**
     * @param x x val, x axis oriented to the right
     */
    void setX (const int16_t& x);

    [[nodiscard]] uint16_t getDeadzone() const;

private:
    SDL_Joystick* gamepad = nullptr;
    uint16_t JOYSTICK_DEADZONE = 100;

    int16_t x = 0;
    int16_t y = 0;
    static constexpr double pi = 3.14159265359;
};
