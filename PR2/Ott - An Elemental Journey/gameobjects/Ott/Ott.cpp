#include "Ott.h"

Ott::Ott(const Vector2D& position, Texture* texture, PlayState* game, const Scale& scale) : Entity(position, texture, Vector2D(0, 0), 5, game, scale) {

}

void Ott::handleEvents(const SDL_Event& event) {
#pragma region CONTROLLER INPUT
	/*
	if (event.type == SDL_CONTROLLERAXISMOTION) {
		if (event.jaxis.which == 0) { // SABER QU� JOYSTICK SE HA MOVIDO
			// X axis motion
			if (event.jaxis.axis == 0) { // SABER QU� EJE SE HA MOVIDO
				if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) xDir = -1; // Left to dead zone
				else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) xDir = 1; // Right to dead zone
				else xDir = 0;
			}
			// Y axis motion
			else if (event.jaxis.axis == 1) {
				if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) yDir = -1; // Below to dead zone
				else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) yDir = 1; // Above dead zone
				else yDir = 0;
			}

			else if (event.jaxis.axis == 2 || event.jaxis.axis == 3) {
				cout << "Right Joystick" << endl;
			}

			else if (event.jaxis.axis == 4) {
				cout << "LEFT TRIGGER: " + to_string((int)event.jaxis.value) << endl;
			}

			else if (event.jaxis.axis == 5) {
				cout << "RIGHT TRIGGER: " + to_string((int)event.jaxis.value) << endl;
			}
		}
	}

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		Uint8 button = event.jbutton.button;

		if (button == SDL_CONTROLLER_BUTTON_A) {
			cout << " uwu" << endl;
		}
		else if (button == SDL_CONTROLLER_BUTTON_B) {
			cout << "owo" << endl;
		}
		else if (button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
			cout << "awa" << endl;
		}
		else cout << (int)button << endl;
	}
	*/
#pragma endregion

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			jump();
		}
	}
}

bool Ott::canJump() {
	return ground;
}

void Ott::jump() {
	if (canJump()) {
		animState = JUMPING;
		speed = Vector2D(speed.getX(), jumpForce);
	}
}

void Ott::update() {
#pragma region CONTROLLER INPUT
	/*
	// C�lculo de �ngulo para mostar direcci�n en la que apunta el Joystick
	arrowAngle = atan2((double)yDir, (double)xDir) * (180 / M_PI);
	if (xDir == 0 && yDir == 0) arrowAngle = 0;
	*/
#pragma endregion
	timer++;
	if (timer >= ANIMATION_FRAME_RATE) {
		timer = 0;
		if (animState == IDLE)
		{
			row = 0;
			col = (col + 1) % 2;
		}
		if (animState == JUMPING)
		{
			row = 5;
			col = 2;
		}
		if (animState == PEAK) {
			row = 5;
			col = 3;
		}
		if (animState == FALLING) {
			row = 5;
			col = 4;
		}
		if (animState == LAND) {
			row = 5;
			col = 5;
		}
		// avanzar framde de animation
	}

	onGround = getRect();
	onGround.y += onGround.h;
	onGround.h = -jumpForce - 1;

	if (speed.getY() > 1.5) {
		animState = FALLING;
		timer = ANIMATION_FRAME_RATE;
	}
	if (speed.getY() < 0.5 && speed.getY() > -0.5 && !ground) {
		animState = PEAK;
		timer = ANIMATION_FRAME_RATE;
	}

	position = position + speed;
#pragma region Detecci�n de suelo??? y colisiones
	SDL_Rect groundCol;
	bool col = false;
	static_cast<PlayState*>(game)->ottCollide(getRect(), onGround, groundCol, col, ground);
	if (ground) {
		animState = IDLE;
		if (!notGroundedBefore) {
			animState = LAND;
			timer = ANIMATION_FRAME_RATE;
			position = Vector2D(groundCol.x, groundCol.y - height);
			speed = Vector2D(speed.getX(), 0);
		}
		notGroundedBefore = true;
	}
	if (speed.getY() < -1) notGroundedBefore = false;
#pragma endregion

}

void Ott::useGravity() {
	speed = Vector2D(speed.getX(), speed.getY() + static_cast<PlayState*>(game)->Gravity());
}

void Ott::render() const {
#pragma region CONTROLLER INPUT
	/*
	texture->renderFrame(getRect(), 0, 0, arrowAngle);
	*/
#pragma endregion
	texture->renderFrame(getRect(), row, col);
}

#pragma endregion