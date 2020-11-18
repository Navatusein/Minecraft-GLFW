#include "Player.h"

Player::Player(World* world) : world(world) {
	FOV = 100.f;
	renderDist = 10000.f;
	camera = new Camera(vec3(0, 30, 1), radians(FOV), renderDist);

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
			world->RayCast(camera->Position, camera->Front, 20.f, end, norm, iend);
			if(world->GetBlock(iend.x, iend.y, iend.z)->GetID() != 0) {
				world->SetBlock(0, iend.x, iend.y, iend.z);
			}
		}

		if (Events::JustClicked(KM_MOUSE_BUTTON_2)) {
			glm::vec3 end;
			glm::vec3 norm;
			glm::vec3 iend;
			world->RayCast(camera->Position, camera->Front, 20.f, end, norm, iend);
			if(world->GetBlock(iend.x, iend.y, iend.z)->GetID() != 0) {
				world->SetBlock(3, iend.x + norm.x, iend.y + norm.y, iend.z + norm.z);
			}
		}

		const float PI = 3.141592653;

		if (Events::Pressed(KM_KEY_W)) {
			camera->Position.x += cos(radians(camera->yaw)) * Delta * Speed;
			camera->Position.z += sin(radians(camera->yaw)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_S)) {
			camera->Position.x -= cos(radians(camera->yaw)) * Delta * Speed;
			camera->Position.z -= sin(radians(camera->yaw)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_D)) {
			camera->Position.x -= cos(radians(camera->yaw - 90)) * Delta * Speed;
			camera->Position.z -= sin(radians(camera->yaw - 90)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_A)) {
			camera->Position.x += cos(radians(camera->yaw - 90)) * Delta * Speed;
			camera->Position.z += sin(radians(camera->yaw - 90)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_SPACE)) {
			camera->Position.y += Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_LEFT_SHIFT)) {
			camera->Position.y -= Delta * Speed;
		}
		camera->Update();
	}
}

Camera* Player::getCamera() {
	return camera;
}

Player::~Player() {
	delete camera;
}
