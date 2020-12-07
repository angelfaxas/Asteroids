#pragma once 

#ifndef _physics_HPP
#define _physics_HPP

namespace Engine 
{
    float wrap(float x, float min, float max)
    {
        if (x < min)
        return max - (min - x);
        if (x > max)
        return min + (x - max);
        return x;
    }

    static constexpr float MAX_VELOCITY = 500.0f;
    static constexpr float THRUST = 15.0f;
    static constexpr float DRAG_FORCE = 0.999f;
    static constexpr float ANGLE_OFFSET = 90.0f;
    static constexpr float BULLET_SPEED = 250;
}
#endif