#include "Player.h"

Player::Player(World* world) : world(world) {
	FOV = 100.f;
	renderDist = 10000.f;
	camera = new Camera(vec3(0, 30, 1), radians(FOV), renderDist);

	LastTime = glfwGetTime();
	Delta = 0.0f;

	Speed = 15;
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
			world->SetBlock(0, iend.x, iend.y, iend.z);
		}

		if (Events::JustClicked(KM_MOUSE_BUTTON_2)) {
			glm::vec3 end;
			glm::vec3 norm;
			glm::vec3 iend;
			world->RayCast(camera->Position, camera->Front, 20.f, end, norm, iend);
			world->SetBlock(3, iend.x + norm.x, iend.y + norm.y, iend.z + norm.z);
		}



		if (Events::Pressed(KM_KEY_W)) {
			camera->Position += camera->Front * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_S)) {
			camera->Position -= camera->Front * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_D)) {
			camera->Position += glm::normalize(glm::cross(camera->Front, vec3(0.0f, 1.0f, 0.0f))) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_A)) {
			camera->Position -= glm::normalize(glm::cross(camera->Front, vec3(0.0f, 1.0f, 0.0f))) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_SPACE)) {
			camera->Position.y += Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_LEFT_SHIFT)) {
			camera->Position.y -= Delta * Speed;
		}
		
		/*
		CamY += -Events::deltaY / Window::Height * 2;
		CamX += -Events::deltaX / Window::Height * 2;

		if (CamY < -radians(89.0f)) {
			CamY = -radians(89.0f);
		}
		if (CamY > radians(89.0f)) {
			CamY = radians(89.0f);
		}
		camera->Rotation = mat4(1.f);
		camera->Rotate(CamY, CamX, 0);
		*/
		camera->Update();
	}
}

Camera* Player::getCamera() {
	return camera;
}

Player::~Player() {
	delete camera;
}
