#include "Camera.h"


Camera::Camera(vec3* Position, vec3* View, float* Fov, float RenderDistance) : Position(Position), View(View), Fov(Fov), RenderDistance(RenderDistance) {
 
}
void Camera::Update() {

}

mat4 Camera::GetProjection() {
    return glm::perspective(glm::radians(*Fov), (float)Window::Width / (float)Window::Height, 0.1f, RenderDistance);
}

mat4 Camera::GetView() {
	glm::vec3 absolutePosition = glm::vec3(Position->x, Position->y + 1.5, Position->z);
    return glm::lookAt(absolutePosition, absolutePosition + *View, glm::vec3(0.0f, 1.0f, 0.0f));
}

vec3 Camera::GetPosition() {
	return glm::vec3(Position->x, Position->y + 1.5, Position->z);
}
