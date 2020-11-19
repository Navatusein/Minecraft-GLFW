#include "AABB.h"

AABB::AABB(const vec3& Dimensions) : Dimensions(Dimensions){}

bool AABB::isCollodingWith(AABB& other) {
    return  (Min.x <= other.Max.x && Max.x >= Min.x) && (Min.y <= other.Max.y && Max.y >= Min.y) && (Min.z <= other.Max.z && Max.z >= Min.z);
}

void AABB::Update(vec3& Position) {
    Min = Position;
    Max = Min + Dimensions;
}


vec3 AABB::getDimensions() {
    return Dimensions;
}
