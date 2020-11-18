#include "Camera.h"


Camera::Camera(vec3* Position, vec3* View, float Fov, float RenderDistance) : Position(Position), View(View), Fov(Fov), RenderDistance(RenderDistance) {
 
}
void Camera::Update() {

}

mat4 Camera::GetProjection() {
    return glm::perspective(Fov, (float)Window::Width / (float)Window::Height, 0.1f, RenderDistance);
}

mat4 Camera::GetView() {
    return glm::lookAt(*Position, *Position + *View, glm::vec3(0.0f, 1.0f, 0.0f));
}
