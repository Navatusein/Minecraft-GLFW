#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Window.h"

using namespace glm;


class Camera {
private:
	void UpdateVector();
public:
	vec3 Front;
	vec3 Right;
	vec3 Up;
	vec3 Position;

	float Fov;
	mat4 Rotation;

	Camera(vec3 Position, float Fov);

	void Rotate(float x, float y, float z);

	mat4 GetProjection();
	mat4 GetView();

};

