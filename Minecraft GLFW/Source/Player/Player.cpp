#include "Player.h"

const vec3 Dimensions(0.5, 1.5, 0.5);

void Player::CollisionTest(const vec3& Velocity__) {
	for (int x = Position.x - Dimensions.x; x < Position.x + Dimensions.x; x++) {
		for (int y = Position.y - Dimensions.y; y < Position.y + 0.7; y++) {
			for (int z = Position.z - Dimensions.z; z < Position.z + Dimensions.z; z++) {
				auto block = world->GetBlock(x, y, z);
				if (block) {
					if (block->GetID() != 0) {
						if (Velocity__.y > 0) {
							Position.y = y - Dimensions.y;
							Velocity.y = 0;
						}
						else if (Velocity__.y < 0) {
							isOnGround = true;
							Position.y = y + Dimensions.y + 1;
							Velocity.y = 0;
						}

						if (Velocity__.x > 0) {
							Position.x = x - Dimensions.x;
						}
						else if (Velocity__.x < 0) {
							Position.x = x + Dimensions.x + 1;
						}

						if (Velocity__.z > 0) {
							Position.z = z - Dimensions.z;
						}
						else if (Velocity__.z < 0) {
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

	Speed = 0.2;

	isFlying = false;
	isFlyOn = false;
	isOnGround = false;
}

void Player::Update() {
	KeyBoardUpdate();
	MouseUpdate();
	PhysicUpdate();
	CheckCollision();
}

void Player::CheckCollision() {

	Velocity += m_acceleration;
	m_acceleration = { 0, 0, 0 };

	Position.x += Velocity.x * Delta;
	CollisionTest({ Velocity.x, 0, 0 });

	Position.y += Velocity.y * Delta;
	CollisionTest({ 0, Velocity.y, 0 });

	Position.z += Velocity.z * Delta;
	CollisionTest({ 0, 0, Velocity.z });
	
	Velocity.x *= 0.95;
	Velocity.z *= 0.95;

	if (isFlying) {
		Velocity.y *= 0.95f;
	}
	
}

void Player::PhysicUpdate() {
	if (!isFlying) {
		if (!isOnGround) {
			Velocity.y -= 40 * Delta;
		}
		isOnGround = false;
	}

	if (Position.y <= -10 && !isFlying) {
		Position.y = 300;
	}

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
			m_acceleration.x += cos(radians(yaw)) * Speed;
			m_acceleration.z += sin(radians(yaw)) * Speed;
		}

		if (Events::Pressed(KM_KEY_S)) {
			m_acceleration.x -= cos(radians(yaw)) * Speed;
			m_acceleration.z -= sin(radians(yaw)) * Speed;
		}

		if (Events::Pressed(KM_KEY_D)) {
			m_acceleration.x -= cos(radians(yaw - 90)) * Speed;
			m_acceleration.z -= sin(radians(yaw - 90)) * Speed;
		}

		if (Events::Pressed(KM_KEY_A)) {
			m_acceleration.x += cos(radians(yaw - 90)) * Speed;
			m_acceleration.z += sin(radians(yaw - 90)) * Speed;
		}

		if (Events::Pressed(KM_KEY_SPACE)) {
			if (!isFlying) {
				if (isOnGround) {
					isOnGround = false;
					m_acceleration.y += Speed * 50;
				}
			}
			else {
				m_acceleration.y += Speed * 3;
			}
		}
		if (Events::Pressed(KM_KEY_V)) {
			m_acceleration = { 0,0,0 };
		}

		if (Events::Pressed(KM_KEY_LEFT_SHIFT)) {
			m_acceleration.y -= Speed;
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
