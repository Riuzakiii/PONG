#pragma once

extern "C"
{
#include <SDL2/SDL.h>
}

#include <algorithm>
#include <vector>

struct Position
{
    double x = 0;
    double y = 0;
};

struct Velocity
{
    double x = 0;
    double y = 0;
};

struct Acceleration
{
    double x = 0;
    double y = 0;
};

struct Size
{
    int width = 0;
    int height = 0;
};

class Object;

class Collision
{
public:
    static constexpr uint8_t Up = 1;
    static constexpr uint8_t Down = 2;
    static constexpr uint8_t Left = 4;
    static constexpr uint8_t Right = 8;
    static constexpr uint8_t None = 0;
    static constexpr uint8_t AllSides = Up | Down | Left | Right;

    Collision (bool collided = false, Object* source = nullptr)
        : collided (collided), source (source){};

    operator bool() const { return collided; }

    [[nodiscard]] uint8_t getSide() const { return side; }

    Object* getSource() const { return source; }

    void addSides (uint8_t newSide) { side ^= newSide; }

    void setCollided (const bool& newCollided) { collided = newCollided; }

    void setSource (Object* obj) { source = obj; }

    class Listener
    {
    public:
        virtual void callback (const Collision&) = 0;
    };

private:
    bool collided = false;
    uint8_t side = None;
    Object* source = nullptr;
};

class Object
{
public:
    enum class Type
    {
        Ground,
        Moving
    };

    Object (const Size& size,
            const Position& position,
            const Velocity& velocity,
            const Type& type);

    virtual ~Object() = default;

    virtual Position getNextPos (const Collision&) { return position; }
    void setNextPos (const Position& newPosition) { position = newPosition; }
    virtual void render (SDL_Renderer*&) = 0;
    virtual void onEvent (SDL_Event) {}
    virtual void onDeviceState (const int) {}

    virtual void reset();

    void addListener (Collision::Listener* collisionListener);

    bool removeListener (Collision::Listener* collisionListener);

    [[nodiscard]] const Position& getPosition() const;
    void setPosition (const Position&);
    [[nodiscard]] const Velocity& getVelocity() const;
    void setVelocity (const Velocity&);
    [[nodiscard]] const Size& getSize() const;
    void setSize (const Size&);
    [[nodiscard]] const std::vector<Collision::Listener*>&
        getCollisionListeners() const;
    [[nodiscard]] const Type& getType() const;

private:
    Size size;
    Position position;
    Velocity velocity;

    Position initPosition;
    Velocity initVelocity;

    Type type = Type::Moving;
    std::vector<Collision::Listener*> collisionListeners;
};

class Ground : public Object
{
public:
    Ground() : Object ({}, {}, {}, Object::Type::Ground) {}

    void render (SDL_Renderer*&) override{};
};
