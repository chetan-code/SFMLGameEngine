#include "Physics.h"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    //todo : overlap rectangle size of the bounding boxes of entites a and b
    return Vec2(0,0);
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    //same as above method just uses entity previous position
    return Vec2();
}


