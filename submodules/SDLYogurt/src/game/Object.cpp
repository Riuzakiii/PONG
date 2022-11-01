#include "Object.h"

Object::Object (const Size& size,
                const Position& position,
                const Velocity& velocity,
                const Type& type)
    : size (size), position (position), velocity (velocity),
      initPosition (position), initVelocity (velocity), type (type)
{
}

void Object::reset()
{
    position = initPosition;
    velocity = initVelocity;
}

void Object::addListener (Collision::Listener* collisionListener)
{
    if (collisionListener != nullptr)
    {
        collisionListeners.push_back (collisionListener);
    }
}

bool Object::removeListener (Collision::Listener* collisionListener)
{
    auto listener =
        std::find_if (collisionListeners.begin(),
                      collisionListeners.end(),
                      [&collisionListener] (Collision::Listener* listener)
                      { return collisionListener == listener; });

    if (listener != collisionListeners.end())
    {
        collisionListeners.erase (listener);
        return true;
    }

    return false;
}

const Position& Object::getPosition() const { return position; }

void Object::setPosition (const Position& newPosition)
{
    position = newPosition;
}

const Velocity& Object::getVelocity() const { return velocity; }

void Object::setVelocity (const Velocity& newVelocity)
{
    velocity = newVelocity;
}

[[nodiscard]] const Size& Object::getSize() const { return size; }

void Object::setSize (const Size& newSize) { size = newSize; }

[[nodiscard]] const std::vector<Collision::Listener*>&
    Object::getCollisionListeners() const
{
    return collisionListeners;
}

[[nodiscard]] const Object::Type& Object::getType() const { return type; }
