#pragma once
#include "Object.h"
#include <cmath>
#include <memory>
#include <vector>

extern "C"
{
#include <SDL2/SDL.h>
}

class Physics
{
public:
    Physics (const int& width, const int& height);

    [[nodiscard]] static Position localToCenter (const Object& obj);

    [[nodiscard]] static Collision checkBoundingBox (const Position& posA,
                                                     const Position& posB,
                                                     const Size& sizeA,
                                                     const Size& sizeB);

    [[nodiscard]] Collision isInbound (const Position& position,
                                       const Object& object) const;

    [[nodiscard]] Position getInbound (const Position& position,
                                       const Object& object) const;

    void compute (std::vector<std::unique_ptr<Object>>& objects);

private:
    const int width = 0;
    const int height = 0;
    static constexpr auto eps = 0.;
};
