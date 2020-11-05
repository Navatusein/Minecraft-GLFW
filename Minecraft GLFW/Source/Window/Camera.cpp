#include "Camera.h"

void Camera::UpdateVector() {
    Front = vec3(Rotation * vec4(0, 0, -1, 1));
    Right = vec3(Rotation * vec4(1, 0, 0, 1));
    Up = vec3(Rotation * vec4(0, 1, 0, 1));
}

Camera::Camera(vec3 Position, float Fov) : Position(Position), Fov(Fov), Rotation(Rotation) {
    UpdateVector();
}

void Camera::Rotate(float x, float y, float z) {
    Rotation = rotate(Rotation, z, vec3(0, 0, 1));
    Rotation = rotate(Rotation, y, vec3(0, 1, 0));
    Rotation = rotate(Rotation, x, vec3(1, 0, 0));

    UpdateVector();
}

mat4 Camera::GetProjection() {
    float Aspect = (float)Window::Width / (float)Window::Height;
    return glm::perspective(Fov, Aspect, 0.1f, 100.0f);
}

mat4 Camera::GetView() {
    return glm::lookAt(Position, Position + Front, Up);
}
