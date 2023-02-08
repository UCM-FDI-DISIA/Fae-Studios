#include "../play/JoystickInput.h"
#include "../../SDLApplication.h"
#include <iostream>

#pragma region JUMP OBJECT

JumpObject::JumpObject(const Vector2D& position, Texture* texture,PlayState* game, const Scale& scale) : GameObject(position, texture, scale), game(game) {
	onGround = getRect();
	onGround.y += 2*onGround.h / 3;
	onGround.h *= 2/3;
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
		switch (animState) {
		case IDLE:
		{
			row = 1;
			col = (col + 1) % 2;
		}
		case JUMPING:
		{
			row = 5;
			col = (col + 1) % 8;
		}
		}
		// avanzar framde de animation
	}

#pragma region Detección de suelo??? y colisiones

	pair<bool,int> groundCol;
	bool col = false;
	game->ottCollide(getRect(), onGround, groundCol, col);

	if (groundCol.first) {
		ySpeed = 0;
		position = Vector2D(position.getX(), groundCol.second);
		cout << "collision" << endl;
	}
#pragma endregion

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
	JumpObject* ott = new JumpObject(Vector2D(0, 400 - 86), app->getTexture("ott", 2), this, Scale(0.3f,0.3f));
	
	gr = new Ground(Vector2D(0, 400), app->getTexture("whiteBox", 2), Scale(0.8f, 0.25f));
	gameObjects.push_back(gr);
	gameObjects.push_back(ott);
}

void PlayState::ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, pair<bool, int>& groundCol, bool& col) {
	
	groundCol = gr->collide(onGround);
	
}

#pragma endregion

#pragma region GROUND
Ground::Ground(const Vector2D& position, Texture* texture, const Scale& scale) : GameObject(position, texture, scale) {

}

pair<bool, int> Ground::collide(const SDL_Rect& onGround) {
	const SDL_Rect rect = getRect();
	int y = rect.y;
	bool col = SDL_HasIntersection(&onGround, &rect);
	return make_pair(col, y);
}

#pragma endregion