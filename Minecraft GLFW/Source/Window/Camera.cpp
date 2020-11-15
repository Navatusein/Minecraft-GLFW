#include "Camera.h"

void Camera::UpdateVector() {
    Front = vec3(Rotation * vec4(0, 0, -1, 1));
    Right = vec3(Rotation * vec4(1, 0, 0, 1));
    Up = vec3(Rotation * vec4(0, 1, 0, 1));
}

Camera::Camera(vec3 Position, float Fov, float render_dist) : Position(Position), Fov(Fov), render_dist(render_dist), Rotation(Rotation) {
    UpdateVector();
    /*
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;
    */
}

void Camera::Rotate(float x, float y, float z) {
    Rotation = rotate(Rotation, z, vec3(0, 0, 1));
    Rotation = rotate(Rotation, y, vec3(0, 1, 0));
    Rotation = rotate(Rotation, x, vec3(1, 0, 0));

    UpdateVector();
}

void Camera::Update() {
    yaw += Events::deltaX * 0.05;
    pitch += Events::deltaY * 0.5;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Front = glm::normalize(front);
}

mat4 Camera::GetProjection() {
    float Aspect = (float)Window::Width / (float)Window::Height;
    return glm::perspective(Fov, Aspect, 0.1f, 100.0f);
}

mat4 Camera::GetView() {
    return glm::lookAt(Position, Position + Front, Up);
}
