#include "Camera.h"


Camera::Camera(vec3 Position, float Fov, float render_dist) : Position(Position), Fov(Fov), render_dist(render_dist), Rotation(Rotation) { 
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    yaw = -90.0f;
    pitch = 0.0f;
    
}
void Camera::Update() {
    yaw += Events::deltaX * 0.15;
    pitch += Events::deltaY * 0.15;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    if (yaw > 360) {
        yaw = 0;
    }
    if (yaw < 0) {
        yaw = 360;
    }
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Front = glm::normalize(front);
}

mat4 Camera::GetProjection() {
    float Aspect = (float)Window::Width / (float)Window::Height;
    return glm::perspective(Fov, Aspect, 0.1f, render_dist);
}

mat4 Camera::GetView() {
    return glm::lookAt(Position, Position + Front, glm::vec3(0.0f, 1.0f, 0.0f));
}
