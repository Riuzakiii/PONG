#include "Wall.h"

Wall::Wall (Position position, Velocity velocity)
    : Object ({}, position, velocity, Object::Type::Moving)
{
}

Position Wall::getNextPos (const Collision& collision)
{
    Position newPosition = getPosition();

    if (!collision)
    {
        const auto& velocity = getVelocity();
        const auto tickMs = timer.getTickMilliseconds();
        if ((currentState & Directions::Left) != 0)
        {
            newPosition.x -= velocity.x * tickMs / 1000.;
        }
        if ((currentState & Directions::Right) != 0)
        {
            newPosition.x += velocity.x * tickMs / 1000.;
        }
        timer.reset();
    }
    return newPosition;
}

void Wall::render (SDL_Renderer*& gRenderer)
{
    if (texture.isNull())
    {
        texture.loadFromPath (gRenderer, "media/wall.png");
        setSize ({texture.getWidth(), texture.getHeight()});
    }

    const auto& position = getPosition();
    texture.render (gRenderer,
                    static_cast<int> (position.x),
                    static_cast<int> (position.y));
}

void Wall::onDeviceState (const int state) { currentState = state; }

void Wall::reset()
{
    Object::reset();
    timer.reset();
    tickMs = 0;
}

MovingWall::MovingWall (Position position, Velocity velocity)
    : Object ({}, position, velocity, Object::Type::Moving)
{
    timer.start();
}

Position MovingWall::getNextPos (const Collision& collision)
{
    Position newPosition = getPosition();

    auto side = collision.getSide();
    auto velocity = getVelocity();
    if (collision && (side & (Collision::Left | Collision::Right)) != 0)
    {
        velocity.x *= -1;
        setVelocity (velocity);
    }

    if (!collision)
    {
        auto newTickMs = timer.getTickMilliseconds();
        newPosition.x += velocity.x * (newTickMs - tickMs) / 1000.;
        tickMs = newTickMs;
    }

    return newPosition;
}
void MovingWall::render (SDL_Renderer*& gRenderer)
{
    if (texture.isNull())
    {
        texture.loadFromPath (gRenderer, "media/wall.png");
        setSize ({texture.getWidth(), texture.getHeight()});
    }
    const auto& position = getPosition();

    texture.render (gRenderer,
                    static_cast<int> (position.x),
                    static_cast<int> (position.y));
}

void MovingWall::onDeviceState (const int state) { currentState = state; }

void MovingWall::reset()
{
    Object::reset();
    timer.reset();
    tickMs = 0;
}
