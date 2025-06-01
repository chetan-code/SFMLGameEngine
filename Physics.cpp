#include "Physics.h"
#include <cstdlib>

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    Vec2 aPos = a->getComponent<CTransform>().pos;
    Vec2 bPos = b->getComponent<CTransform>().pos;
    Vec2 aHalfSize = a->getComponent<CBoundingBox>().halfSize;
    Vec2 bHalfSize = b->getComponent<CBoundingBox>().halfSize;
    Vec2 delta(abs(bPos.x - aPos.x), abs(bPos.y - aPos.y));
    Vec2 overlap;
    overlap.x = (aHalfSize.x + bHalfSize.x) - delta.x;
    overlap.y = (aHalfSize.y + bHalfSize.y) - delta.y;
    return overlap;
}

//Get overlap on previous frame
Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    Vec2 aPos = a->getComponent<CTransform>().prevPos;
    Vec2 bPos = b->getComponent<CTransform>().prevPos;
    Vec2 aHalfSize = a->getComponent<CBoundingBox>().halfSize;
    Vec2 bHalfSize = b->getComponent<CBoundingBox>().halfSize;
    Vec2 delta(abs(bPos.x - aPos.x), abs(bPos.y - aPos.y));
    Vec2 overlap;
    overlap.x = (aHalfSize.x + bHalfSize.x) - delta.x;
    overlap.y = (aHalfSize.y + bHalfSize.y) - delta.y;
    return overlap;
}


