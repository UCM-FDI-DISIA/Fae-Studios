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

	//hacer bool/cambiar si solo se podia mover una vez en el salto creo recordar
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_a) {
			dir = Vector2D(-1, 0);
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			dir = Vector2D(1, 0);
		}
		if (event.key.keysym.sym == SDLK_SPACE) {
			jump();
		}
		if (event.key.keysym.sym == SDLK_e && lastSanctuary != nullptr) {
			SDL_Rect sRect = lastSanctuary->getRect();
			SDL_Rect col = getRect();
			if (SDL_HasIntersection(&col, &sRect)) resetLives();
		}
		ismoving = true;
	}
	else
	{
		ismoving = false;
	}
	
	
}

bool Ott::canJump() {
	return ground;
}

void Ott::jump() {
	if (isGrounded()) { //metodo canjump es lo mismo pero no inline? 
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
			dir = Vector2D(0, 0);
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
		if (animState == WALKING) {
			row = 2;
			col = (col + 1) % 4;
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
	
 position = position +speed+ dir; 
#pragma region Deteccion de suelo??? y colisiones
	SDL_Rect groundCol;
	bool col = false;
	static_cast<PlayState*>(game)->ottCollide(getRect(), onGround, groundCol, col, ground);
	if (ground) {
		if (ismoving) 
		{ 
			animState = WALKING; 
		}
		else
		{
			animState = IDLE;
		}
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

	//timer que comprueba si sigue teniendo una vida debil
	if (weakened && (SDL_GetTicks() - weakTimer) >= timeWeak * 1000) weakened = false;
	//bool si ha habido input
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
void Ott::recieveDamage(int elem)
{
	if (elementsInfo[elem][currentElement] == 0) {
		if (!weakened) {
			weakened = true;
			weakTimer = SDL_GetTicks();
		}
		else {
			weakened = false;
			life--;
			Entity::recieveDamage(elem);
		}
	}
	else Entity::recieveDamage(elem);
}
bool Ott::collide(const SDL_Rect& obj, SDL_Rect& result)
{
	return false;
}
bool Ott::collide(GameObject* c)
{
	
	if (Sanctuary* o = dynamic_cast<Sanctuary*> (c)) {
		SDL_Rect col = getRect();
		SDL_Rect sactRect = o->getRect();
		if (SDL_HasIntersection(&sactRect, &col)) {
			if (lastSanctuary != o) {
				cout << "Toca sanctuario" << endl;
				saveSactuary(o);
			}
			return true;
		}
	}
	return false;
}
void Ott::die()
{
	cout << "He muerto " << endl;
	if (lastSanctuary == nullptr) {
		cout << "No hay sanctuarios recientes... Muerte inminente" << endl;
	}
	else {
		SDL_Rect r = lastSanctuary->getRect();
		Vector2D newPos = { (double)r.x, (double)r.y };
		position = newPos;
		life = maxLife;
	}
}
#pragma endregion