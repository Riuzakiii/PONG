#include "Physics.h"

Physics::Physics (const int& width, const int& height)
    : width (width), height (height)
{
}

Position Physics::localToCenter (const Object& obj)
{
    const auto& pos = obj.getPosition();
    const auto& size = obj.getSize();
    return {pos.x + static_cast<double>(size.width) / 2., pos.y + static_cast<double>(size.height) / 2.};
}

Collision Physics::checkBoundingBox (const Position& posA,
                                     const Position& posB,
                                     const Size& sizeA,
                                     const Size& sizeB)
{

    const auto diffX = posA.x - posB.x;
    const auto diffY = posA.y - posB.y;
    const auto distX = std::abs (diffX);
    const auto distY = std::abs (diffY);

    Collision collision;
    uint8_t sidesVertical = Collision::None;
    uint8_t sidesHorizontal = Collision::None;

    if (diffX <= 0 && distX <= (sizeA.width))
    {
        sidesHorizontal |= Collision::Right;
    }
    else if (diffX > 0 && distX <= (sizeB.width))
    {
        sidesHorizontal |= Collision::Left;
    }

    if (diffY <= 0 && distY <= (sizeA.height))
    {
        sidesVertical |= Collision::Down;
    }
    else if (diffY > 0 && distY <= (sizeB.height))
    {
        sidesVertical |= Collision::Up;
    }

    if ((sidesHorizontal & (Collision::Left | Collision::Right)) != 0 &&
        (sidesVertical & (Collision::Up | Collision::Down)) != 0)
    {
        collision.setCollided (true);
        collision.addSides (sidesVertical);
        collision.addSides (sidesHorizontal);
    }
    return collision;
}

Collision Physics::isInbound (const Position& position,
                              const Object& object) const
{
    Collision collision;
    const auto& size = object.getSize();
    if (position.x < 0)
    {
        collision.addSides (Collision::Left);
    }
    else if (position.x > (width - size.width))
    {
        collision.addSides (Collision::Right);
    }

    if (position.y < 0)
    {
        collision.addSides (Collision::Up);
    }
    else if (position.y > (height - size.height))
    {
        collision.addSides (Collision::Down);
    }

    auto side = collision.getSide();

    if ((side & Collision::AllSides) != 0)
    {
        collision.setCollided (true);
    }

    return collision;
}

Position Physics::getInbound (const Position& position,
                              const Object& object) const
{
    Position positionInbound = position;
    const auto& size = object.getSize();

    bool inbound = isInbound (position, object);
    if (inbound)
    {
        return position;
    }

    if (position.x < 0)
    {
        positionInbound.x = 0;
    }
    else if (position.x > (width - size.width))
    {
        positionInbound.x = static_cast<double> (width - size.width);
    }

    if (position.y < 0)
    {
        positionInbound.y = 0;
    }
    else if (position.y > (height - size.height))
    {
        positionInbound.y = static_cast<double> (height - size.height);
    }

    return positionInbound;
}

void Physics::compute (std::vector<std::unique_ptr<Object>>& objects)
{
    std::vector<Position> nextPositions;
    nextPositions.reserve(objects.size());
    
    for (auto& object : objects)
    {
        nextPositions.push_back (object->getNextPos ({false}));
    }

    // Set the new position for moving objects only if there is no collision
    // for the new position
    for (size_t i = 0; i != objects.size(); ++i)
    {
        if (auto collision = isInbound (nextPositions[i], *objects[i]);
            collision)
        {
            Ground ground;
            collision.setSource (&ground);
            for (auto* collisionListener : objects[i]->getCollisionListeners())
            {
                collisionListener->callback (collision);
            }
            nextPositions[i] =
                getInbound (objects[i]->getNextPos (collision), *objects[i]);

            continue;
        }
        for (size_t j = 0; j != objects.size(); ++j)
        {
            if (i != j)
            {
                if (auto collision = checkBoundingBox (nextPositions[i],
                                                       nextPositions[j],
                                                       objects[i]->getSize(),
                                                       objects[j]->getSize());
                    collision)
                {
                    if (objects[i]->getType() == Object::Type::Moving)
                    {
                        for (auto* collisionListener :
                             objects[i]->getCollisionListeners())
                        {
                            collisionListener->callback (collision);
                        }

                        collision.setSource (objects[j].get());
                        nextPositions[i] = getInbound (
                            objects[i]->getNextPos (collision), *objects[i]);
                    }
                }
            }
        }
    }

    auto itPos = nextPositions.begin();
    auto itObj = objects.begin();
    while (itPos != nextPositions.end())
    {
        (*(itObj++))->setNextPos (*(itPos++));
    }
}
