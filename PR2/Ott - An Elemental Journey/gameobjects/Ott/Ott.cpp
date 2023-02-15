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
		if (event.key.keysym.sym == SDLK_LEFT) {
			left = true;
			//dir = Vector2D(-1, 0);
			ismoving = true;
			//attack = false;
			lookingFront = false;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			ismoving = true;
			right = true;
			//attack = false;
			//dir = Vector2D(1, 0);
			lookingFront = true;
		}
		if (event.key.keysym.sym == SDLK_SPACE) {
			jump();

			ismoving = true;
			up = true;
			//attack = false;
		}
		if (event.key.keysym.sym == SDLK_q && lastSanctuary != nullptr) {
			SDL_Rect sRect = lastSanctuary->getRect();
			SDL_Rect col = getRect();
			if (SDL_HasIntersection(&col, &sRect)) resetLives();
			ismoving = true;
		}
		if (!attack && event.key.keysym.sym == SDLK_e) {
			animState = ATTACK;
			attack = true;
			cout << "ataque" << endl;
			ismoving = true;
			col = 2;
			timer += ANIMATION_FRAME_RATE / 2;
		}
		if (event.key.keysym.sym == SDLK_x) {
			recieveDamage(currentElement);
		}
		cout << animState << endl;
		cout << dir.getX() << endl;
	}
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_LEFT) {
			left = false;
			dir = Vector2D(-1, 0);
			cout << "L_Out" << endl;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			right = false;
			//dir = Vector2D(1, 0);
			cout << "R_Out" << endl;
		}
		if (event.key.keysym.sym == SDLK_SPACE) {
			jump();
			up = false;
		}
		if (event.key.keysym.sym == SDLK_e) {
			/*	attack = false;*/
			cout << "ataqueOut" << endl;
		}
		if (event.key.keysym.sym == SDLK_r) {
			recieveDamage(0);
			
		}
		cout << animState << endl;
		cout << dir.getX() << endl;
	}
	if (!right && !left)
	{
		if (!attack) {
			//cout << "SALII" << endl;
			ismoving = false;
		}
		dir = dir * Vector2D(0, 1);
	}
	//cout << left << " " << right << " " << attack << endl;
}

bool Ott::canJump() {
	return ground;
}

void Ott::jump() {
	if (isGrounded()) { //metodo canjump es lo mismo pero no inline? 
		if (!attack)animState = JUMPING;
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

	if (right) dir = Vector2D(1, 0);
	if (left) dir = Vector2D(-1, 0);
#pragma region ANIMATIONS
	timer++;
	if (timer >= ANIMATION_FRAME_RATE) {
		timer = 0;
		if (animState == IDLE)
		{
			if (ground)dir = Vector2D(0, 0);
			//cout << "IDLE" << endl;
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
		if (animState == ATTACK)
		{
			cout << "anim attack" << endl;
			row = 8;
			if (col < 7) {
				col++;
				timer += ANIMATION_FRAME_RATE / 2;
			}
			else {
				col = 0;
				cout << "GEEEE" << endl;
				attack = false;
			}
		}
		// avanzar framde de animation
	}
	onGround = getRect();
	onGround.y += onGround.h;
	onGround.h = -jumpForce - 1;

	if (speed.getY() > 1.5) {
		if (!attack) {
			animState = FALLING;
			timer = ANIMATION_FRAME_RATE;
		}
	}
	if (speed.getY() < 0.5 && speed.getY() > -0.5 && !ground) {
		if (!attack) {
			animState = PEAK;
			timer = ANIMATION_FRAME_RATE;
		}
	}
#pragma endregion

	if (speed.getY() > 8) { speed = Vector2D(speed.getX(), 8); }

#pragma region Deteccion de suelo??? y colisiones
	SDL_Rect groundCol;
	bool col = false;
	static_cast<PlayState*>(game)->ottCollide(getRect(), onGround, groundCol, col, ground);
	if (ground) {
		if (ismoving)
		{
			if (!attack)animState = WALKING;
		}
		else
		{
			animState = IDLE;
		}
		if (!notGroundedBefore) {
			if (!attack) {
				animState = LAND;
				timer = ANIMATION_FRAME_RATE;
			}
			position = Vector2D(groundCol.x, groundCol.y - height);
			speed = Vector2D(speed.getX(), 0);
		}
		notGroundedBefore = true;
	}
	if (speed.getY() < -1) notGroundedBefore = false;
#pragma endregion
	//timer que comprueba si sigue teniendo una vida debil
	if (weakened && (SDL_GetTicks() - weakTimer) >= timeWeak * 1000) weakened = false;
	if (invincible && (SDL_GetTicks() - invencibilityTimer) > invincibilityTime * 1000) invincible = false;
	//bool si ha habido input
	position = position + speed + dir;
}

void Ott::useGravity() {
	speed = Vector2D(speed.getX(), speed.getY() + static_cast<PlayState*>(game)->Gravity());
}

void Ott::render(const SDL_Rect& Camera) const {
#pragma region CONTROLLER INPUT
	/*
	texture->renderFrame(getRect(), 0, 0, arrowAngle);
	*/
#pragma endregion
	if (invincible && SDL_GetTicks() % 2 == 0) return;
	SDL_Rect ottRect = getRect();
	ottRect.x -= Camera.x;
	ottRect.y -= Camera.y;
	if (!lookingFront) {
		texture->renderFrame(ottRect, row, col, 0, SDL_FLIP_HORIZONTAL);
	}
	else texture->renderFrame(ottRect, row, col);
}
void Ott::recieveDamage(int elem)
{
	if (SDL_GetTicks() - invencibilityTimer <= invincibilityTime * 1000) return;
	cout << "Daño" << endl;
	invencibilityTimer = SDL_GetTicks();
	knockback();
	invincible = true;
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
		PlayState* p = static_cast<PlayState*>(game);
		p->backToMenu();
	}
	else {
		SDL_Rect r = lastSanctuary->getRect();
		Vector2D newPos = { (double)r.x, (double)r.y - 50 };
		position = newPos;
		life = maxLife;
		notGroundedBefore = false;
	}
}
void Ott::knockback() {

	Vector2D knockback = Vector2D{ 0, X_KNOCKBACK_FORCE };

	if (lookingFront)
		knockback = -1*knockback;

	dir = dir + knockback;
}
#pragma endregion