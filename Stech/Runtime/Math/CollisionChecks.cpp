//
// Created by fer on 10/5/2021.
//

#include <cmath>
#include "CollisionChecks.h"


bool collision_circle_point(Vector2 circle, Vector2 point, float radius) {
    Vector2 delta = {circle.x - point.x, circle.y - point.y};
    return sqrt(delta.x*delta.x + delta.y*delta.y) < radius;
}