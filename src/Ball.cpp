#include "Ball.h"

FreeBall::FreeBall (Position position, Velocity velocity)
    : Object ({}, position, velocity, Object::Type::Moving)
{
    timer.start();
}

Position FreeBall::getNextPos (const Collision& collision)
{
    Position newPosition = getPosition();
    const auto& side = collision.getSide();
    auto velocity = getVelocity();

    if (collision)
    {
        if ((side & Collision::Right) != 0)
        {
            velocity.x = -std::abs (velocity.x);
        }
        else if ((side & Collision::Left) != 0)
        {
            velocity.x = std::abs (velocity.x);
        }

        if ((side & (Collision::Down)) != 0)
        {
            velocity.y = -std::abs (velocity.y);
        }
        else if ((side & (Collision::Up)) != 0)
        {
            velocity.y = std::abs (velocity.y);
        }
        setVelocity (velocity);
    }

    const auto newTickMs = timer.getTickMilliseconds();
    auto diff = (double)(newTickMs - tickMs);
    newPosition.x = newPosition.x + velocity.x * diff / 1000.;
    newPosition.y = newPosition.y + velocity.y * diff / 1000.;
    tickMs = newTickMs;

    return newPosition;
}

void FreeBall::render (SDL_Renderer*& gRenderer)
{
    if (texture.isNull())
    {
        texture.loadFromPath (gRenderer, "media/dot.png");
        setSize ({texture.getWidth(), texture.getHeight()});
    }
    const auto& position = getPosition();

    texture.render (gRenderer,
                    static_cast<int> (position.x),
                    static_cast<int> (position.y));
}

void FreeBall::reset()
{
    Object::reset();
    timer.reset();
    tickMs = 0;
}
