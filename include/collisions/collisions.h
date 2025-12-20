#ifndef COLLISION_H
#define COLLISION_H

#define _USE_MATH_DEFINES
#include <cmath>

#include "shapes/circle.h"
#include "shapes/rectangle.h"

namespace Collision {
    bool circleRectangle(Shape::Circle& circle, Shape::Rectangle& rect, float rectWidth, float rectHeight);
    bool circleRectangle(float circleX, float circleY, float circleRadius, float rectX, float rectY, float rectWidth, float rectHeight);

}

#endif
