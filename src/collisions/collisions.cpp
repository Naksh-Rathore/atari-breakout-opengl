#define _USE_MATH_DEFINES
#include <cmath>

#include "shapes/circle.h"
#include "shapes/rectangle.h"

#include "collisions/collisions.h"

namespace Collision {
    bool circleRectangle(Shape::Circle& circle, Shape::Rectangle& rect, float rectWidth, float rectHeight) {
        float circleDistanceX { abs(circle.x() - rect.x()) };
        float circleDistanceY { abs(circle.y() - rect.y()) };

        if (circleDistanceX > (rectWidth / 2 + circle.radius())) { return false; }
        if (circleDistanceY > (rectHeight / 2 + circle.radius())) { return false; }
    
        if (circleDistanceX <= (rectWidth / 2)) { return true; } 
        if (circleDistanceY <= (rectHeight / 2)) { return true; }

        float cornerDistanceSquared { pow((circleDistanceX - rectWidth/2), 2) + pow((circleDistanceY - rectHeight/2), 2) };
    
        return (cornerDistanceSquared <= pow(circle.radius(), 2));
    }

    bool circleRectangle(float circleX, float circleY, float circleRadius, float rectX, float rectY, float rectWidth, float rectHeight) {
        float circleDistanceX { abs(circleX - rectX) };
        float circleDistanceY { abs(circleY - rectY) };

        if (circleDistanceX > (rectWidth / 2 + circleRadius)) { return false; }
        if (circleDistanceY > (rectHeight / 2 + circleRadius)) { return false; }
    
        if (circleDistanceX <= (rectWidth / 2)) { return true; } 
        if (circleDistanceY <= (rectHeight / 2)) { return true; }

        float cornerDistanceSquared { pow((circleDistanceX - rectWidth/2), 2) + pow((circleDistanceY - rectHeight/2), 2) };
    
        return (cornerDistanceSquared <= pow(circleRadius, 2));
    }
}
