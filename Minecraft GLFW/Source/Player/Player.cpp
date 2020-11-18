#include "Player.h"

Player::Player(World* world) : world(world) {
	FOV = 100.f;
	renderDist = 10000.f;
	camera = new Camera(&Position, &View, radians(FOV), renderDist);

	LastTime = glfwGetTime();
	Delta = 0.0f;

	Speed = 10;
}

void Player::KeyBoardUpdate() {
	float currentTime = glfwGetTime();
	Delta = currentTime - LastTime;
	LastTime = currentTime;

	// Events test
	if (Events::JustPressed(KM_KEY_ESCAPE)) {
		Window::SetWindowShouldClose(true);
	}
	if (Events::JustPressed(KM_KEY_TAB)) {
		Events::ToogleCursor();
	}

	if (Events::lockedCursor) {

		if (Events::JustClicked(KM_MOUSE_BUTTON_1)) {
			glm::vec3 end;
			glm::vec3 norm;
			glm::vec3 iend;
			world->RayCast(Position, View, 20.f, end, norm, iend);
			if(world->GetBlock(iend.x, iend.y, iend.z)->GetID() != 0) {
				world->SetBlock(0, iend.x, iend.y, iend.z);
			}
		}

		if (Events::JustClicked(KM_MOUSE_BUTTON_2)) {
			glm::vec3 end;
			glm::vec3 norm;
			glm::vec3 iend;
			world->RayCast(Position, View, 20.f, end, norm, iend);
			if(world->GetBlock(iend.x, iend.y, iend.z)->GetID() != 0) {
				world->SetBlock(3, iend.x + norm.x, iend.y + norm.y, iend.z + norm.z);
			}
		}

		if (Events::Pressed(KM_KEY_W)) {
			Position.x += cos(radians(yaw)) * Delta * Speed;
			Position.z += sin(radians(yaw)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_S)) {
			Position.x -= cos(radians(yaw)) * Delta * Speed;
			Position.z -= sin(radians(yaw)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_D)) {
			Position.x -= cos(radians(yaw - 90)) * Delta * Speed;
			Position.z -= sin(radians(yaw - 90)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_A)) {
			Position.x += cos(radians(yaw - 90)) * Delta * Speed;
			Position.z += sin(radians(yaw - 90)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_SPACE)) {
			Position.y += Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_LEFT_SHIFT)) {
			Position.y -= Delta * Speed;
		}
		MouseUpdate();
	}
}

void Player::MouseUpdate() {
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
	glm::vec3 view_;
	view_.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	view_.y = sin(glm::radians(pitch));
	view_.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	View = glm::normalize(view_);
}

Camera* Player::getCamera() {
	return camera;
}

Player::~Player() {
	delete camera;
}
