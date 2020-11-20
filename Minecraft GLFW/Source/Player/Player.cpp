#include "Player.h"

const vec3 Dimensions(0.4, 1.5, 0.4);


Player::Player(World* world) :HitBox(Dimensions), world(world) {
	
	Position = {5, 16, 5};

	FOV = 100.f;
	renderDist = 10000.f;
	camera = new Camera(&Position, &View, radians(FOV), renderDist);

	yaw = 90;
	pitch = 0;

	LastTime = glfwGetTime();
	Delta = 0.0f;

	Speed = 5;
	JumpForce = 8;

	isFlying = false;
	isFlyOn = false; // this doesn't seem to be used
	isOnGround = false;
}

void Player::Update() {
	KeyBoardUpdate();
	MouseUpdate();
	PhysicUpdate();
	CheckCollision();
}

void Player::CheckCollision() {

	Velocity += m_acceleration * Delta;
	m_acceleration = { 0, 0, 0 };

	CollisionTest();

	Position.x += Velocity.x * Delta;
	Position.y += Velocity.y * Delta;
	Position.z += Velocity.z * Delta;

}

void Player::PhysicUpdate() {
	if (!isFlying) {
		if (!isOnGround) {
			if(Velocity.y > -TERMINAL_VELOCITY) {
				m_acceleration.y -= GRAVITY;
			}
		}
	}

	// drag
	float drag = 0.95 * Delta; // this is temporary, until better implementation 

	Velocity.x *= -drag + 1;
	Velocity.z *= -drag + 1;
	if(isFlying) {
		Velocity.y *= -drag + 1;
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
				world->SetBlock_u(0, iend.x, iend.y, iend.z);
			}
		}

		if (Events::JustClicked(KM_MOUSE_BUTTON_2)) {
			glm::vec3 end;
			glm::vec3 norm;
			glm::vec3 iend;
			world->RayCast(Position, View, 20.f, end, norm, iend);
			if(world->GetBlock(iend.x, iend.y, iend.z)->GetID() != 0) {
				world->SetBlock_u(3, iend.x + norm.x, iend.y + norm.y, iend.z + norm.z);
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
			if (isFlying) {
				m_acceleration.y += Speed;
			}
			else {
				if(isOnGround) {
					Velocity.y += JumpForce;
					isOnGround = false;
				}
			}
		}

		if(Events::JustClicked(KM_KEY_SPACE)) {
			if(isOnGround) {
				Velocity.y += JumpForce;
				isOnGround = false;
			}
		}

	}
	else {
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


void Player::CollisionTest() {
	float definition = 0.1;

	bool yNeg_Obstructed = false;
	bool yPos_Obstructed = false;
	for(float x = Position.x - Dimensions.x; x <= Position.x + Dimensions.x; x += definition) {
		for(float z = Position.z - Dimensions.z; z <= Position.z + Dimensions.z; z += definition) {
			if(world->GetBlock(x, Position.y, z)) {
				if(world->GetBlock(x, Position.y, z)->GetID() != 0) {
					yNeg_Obstructed = true;
				}
			}
			if(world->GetBlock(x, Position.y + Dimensions.y, z)) {
				if(world->GetBlock(x, Position.y + Dimensions.y, z)->GetID() != 0) {
					yPos_Obstructed = true;
				}
			}
		}
	}

	bool zNeg_Obstructed = false;
	bool zPos_Obstructed = false;
	for(float x = Position.x - Dimensions.x; x <= Position.x + Dimensions.x; x += definition) {
		for(float y = Position.y; y <= Position.y + Dimensions.y; y += definition) {
			if(world->GetBlock(x, y, Position.z - Dimensions.z)) {
				if(world->GetBlock(x, y, Position.z - Dimensions.z)->GetID() != 0) {
					zNeg_Obstructed = true;
				}
			}
			if(world->GetBlock(x, y, Position.z + Dimensions.z)) {
				if(world->GetBlock(x, y, Position.z + Dimensions.z)->GetID() != 0) {
					zPos_Obstructed = true;
				}
			}
		}
	}

	bool xNeg_Obstructed = false;
	bool xPos_Obstructed = false;
	for(float z = Position.z - Dimensions.z; z <= Position.z + Dimensions.z; z += definition) {
		for(float y = Position.y; y <= Position.y + Dimensions.y; y += definition) {
			if(world->GetBlock(Position.x - Dimensions.x, y, z)) {
				if(world->GetBlock(Position.x - Dimensions.x, y, z)->GetID() != 0) {
					xNeg_Obstructed = true;
				}
			}
			if(world->GetBlock(Position.x + Dimensions.x, y, z)) {
				if(world->GetBlock(Position.x + Dimensions.x, y, z)->GetID() != 0) {
					xPos_Obstructed = true;
				}
			}
		}
	}

	if(Velocity.y < 0 && yNeg_Obstructed) {
		Velocity.y = 0;
	}
	else if(Velocity.y > 0 && yPos_Obstructed) {
		Velocity.y = 0;
	}

	if(Velocity.x < 0 && xNeg_Obstructed) {
		Velocity.x = 0;
	}
	else if(Velocity.x > 0 && xPos_Obstructed) {
		Velocity.x = 0;
	}

	if(Velocity.z < 0 && zNeg_Obstructed) {
		Velocity.z = 0;
	}
	else if(Velocity.z > 0 && zPos_Obstructed) {
		Velocity.z = 0;
	}
}

