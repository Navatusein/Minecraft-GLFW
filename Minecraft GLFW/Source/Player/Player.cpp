#include "Player.h"

const vec3 Dimensions(0.5, 1.5, 0.5);

void Player::CollisionTest(const vec3& Velocity_) {
	for (size_t x = Position.x - Dimensions.x; x < Position.x + Dimensions.x; x++) {
		for (size_t y = Position.y - Dimensions.y; y < Position.y + Dimensions.y; y++) {
			for (size_t z = Position.z - Dimensions.z; z < Position.z + Dimensions.z; z++) {
				auto Block = world->GetBlock(x, y, z);
				if (Block) {
					if (Block->GetID() != 0) {
						if (Velocity_.x > 0)
						{
							Position.x = x - Dimensions.x;
						}
						if (Velocity_.x < 0)
						{
							Position.x = x + Dimensions.x + 1;
						}
						if (Velocity_.y > 0)
						{
							Position.y = y - Dimensions.y;
							Velocity.y = 0;
						}
						if (Velocity_.y < 0)
						{
							Position.y = y + Dimensions.y + 1;
							isOnGround = true;
							Velocity.y = 0;
						}
						if (Velocity_.z > 0)
						{
							Position.z = z - Dimensions.z;
						}
						if (Velocity_.z < 0)
						{
							Position.z = z + Dimensions.z + 1;
						}
					}
				}
			}
		}
	}
}

Player::Player(World* world) :HitBox(Dimensions), world(world) {
	
	Position = {0, 12, 0};

	FOV = 100.f;
	renderDist = 10000.f;
	camera = new Camera(&Position, &View, radians(FOV), renderDist);

	yaw = 90;
	pitch = 0;

	LastTime = glfwGetTime();
	Delta = 0.0f;

	Speed = 10;
}

void Player::CheckCollision() {
	Position.x += Velocity.x * Delta;
	CollisionTest({ Velocity.x, 0, 0 });

	Position.y += Velocity.y * Delta;
	CollisionTest({ 0, Velocity.y, 0 });

	Position.z += Velocity.z * Delta;
	CollisionTest({ 0, 0, Velocity.z });
	
	Velocity.x *= 0.996;
	Velocity.z *= 0.996;
	Velocity.y *= 0.996;
	
	std::cout << Velocity.x << " " << Velocity.y << " " << Velocity.z << "\n";
	
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
			Velocity.x += cos(radians(yaw)) * Delta * Speed;
			Velocity.z += sin(radians(yaw)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_S)) {
			Velocity.x -= cos(radians(yaw)) * Delta * Speed;
			Velocity.z -= sin(radians(yaw)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_D)) {
			Velocity.x -= cos(radians(yaw - 90)) * Delta * Speed;
			Velocity.z -= sin(radians(yaw - 90)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_A)) {
			Velocity.x += cos(radians(yaw - 90)) * Delta * Speed;
			Velocity.z += sin(radians(yaw - 90)) * Delta * Speed;
		}

		if (Events::Pressed(KM_KEY_SPACE)) {
			Velocity.y += Delta * Speed;
		}
		if (Events::Pressed(KM_KEY_V)) {
			Velocity = { 0,0,0 };
		}

		if (Events::Pressed(KM_KEY_LEFT_SHIFT)) {
			Velocity.y -= Delta * Speed;
		}
		MouseUpdate();
		CheckCollision();
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
