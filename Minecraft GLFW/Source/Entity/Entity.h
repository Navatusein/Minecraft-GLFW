#pragma once

#include <glm/glm.hpp>

class Entity {
public:
    glm::vec3 Position;
    glm::vec3 View;

	glm::vec3 Velocity;
	glm::vec3 m_acceleration;

	float LastTime;
	float Delta;

	bool isOnGround;
};