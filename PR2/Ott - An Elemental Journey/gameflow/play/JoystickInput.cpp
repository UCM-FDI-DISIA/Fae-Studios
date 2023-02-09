#include "../play/JoystickInput.h"
#include "../../SDLApplication.h"
#include <iostream>

#pragma region JUMP OBJECT

JumpObject::JumpObject(const Vector2D& position, Texture* texture, PlayState* game, const Scale& scale) : Entity(position, texture, Vector2D(0, 0), 5, game, scale) {

}

void JumpObject::handleEvents(const SDL_Event& event) {
#pragma region CONTROLLER INPUT
	/*
	if (event.type == SDL_CONTROLLERAXISMOTION) {
		if (event.jaxis.which == 0) { // SABER QUÉ JOYSTICK SE HA MOVIDO
			// X axis motion
			if (event.jaxis.axis == 0) { // SABER QUÉ EJE SE HA MOVIDO
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

bool JumpObject::canJump() {
	return ground;
}

void JumpObject::jump() {
	if (canJump()) {
		animState = JUMPING;
		speed = Vector2D(speed.getX(), jumpForce);
	}
}

void JumpObject::update() {
#pragma region CONTROLLER INPUT
	/*
	// Cálculo de ángulo para mostar dirección en la que apunta el Joystick
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
#pragma region Detección de suelo??? y colisiones
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

void JumpObject::useGravity() {
	speed = Vector2D(speed.getX(), speed.getY() + static_cast<PlayState*>(game)->Gravity());
}

void JumpObject::render() const {
#pragma region CONTROLLER INPUT
	/*
	texture->renderFrame(getRect(), 0, 0, arrowAngle);
	*/
#pragma endregion
	texture->renderFrame(getRect(), row, col);
}

#pragma endregion

#pragma region PLAY STATE

PlayState::PlayState(SDLApplication* app) : GameState(2, app) {
#pragma region CONTROLLER INPUT
	/*
	JumpObject* input = new JumpObject(Vector2D(400 - 296 / 2, 300 - 214 / 2), app->getTexture("arrow", 2));
	*/
#pragma endregion
	JumpObject* ott = new JumpObject(Vector2D(0, 0), app->getTexture("ott", 2), this, Scale(0.3f, 0.3f));

	gr = new Ground(Vector2D(0, 400), app->getTexture("whiteBox", 2), Scale(0.8f, 0.25f));
	gameObjects.push_back(gr);
	gameObjects.push_back(ott);

	groundObjects.push_back(gr);
	physicObjects.push_back(ott);
}

void PlayState::ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground) {

	/*
		COMPROBACIÓN DE COLISIONES CON OBJETOS DE TIPO SUELO
	*/
	for (auto it : groundObjects) {
		col = it->collide(Ott, colRect);
		ground = it->collide(onGround, colRect);
	}
	/*
	cout << "GROUND: X: " + to_string(gr->getRect().x) << " Y: " + to_string(gr->getRect().y) << " H: " + to_string(gr->getRect().h) << " W: " + to_string(gr->getRect().w) << endl;
	cout << "OTT: X: " + to_string(Ott.x) << " Y: " + to_string(Ott.y) << " H: " + to_string(Ott.h) << " W: " + to_string(Ott.w) << endl;
	cout << col << endl;
	*/
}

void PlayState::update() {
	GameState::update();

	for (auto it : physicObjects) {
		if (!static_cast<JumpObject*>(it)->isGrounded()) {
			static_cast<JumpObject*>(it)->useGravity();
		}
	}
}
#pragma endregion

#pragma region GROUND
Ground::Ground(const Vector2D& position, Texture* texture, const Scale& scale) : CollisionObject(position, texture, scale) {

}
#pragma endregion