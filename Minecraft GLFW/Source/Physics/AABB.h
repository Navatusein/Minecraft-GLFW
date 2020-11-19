#pragma once

#include <glm/glm.hpp>

#include "../ErrorHandling.h"

using namespace glm;

class AABB {
private:
	vec3 Dimensions;
	vec3 Max;
	vec3 Min;

public:
	AABB(const vec3& Dimensions);

	bool isCollodingWith(AABB& other);

	void Update(vec3& Position);

	vec3 getDimensions();

};

