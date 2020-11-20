#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Window.h"
#include "Events.h"

using namespace glm;


class Camera {
private:
	vec3* View;
	vec3* Position;

	float* Fov;
	float RenderDistance;
public:
	Camera(vec3* Position, vec3* View, float* Fov, float render_dist);

	void Update();

	mat4 GetProjection();
	mat4 GetView();
	vec3 GetPosition();

};

