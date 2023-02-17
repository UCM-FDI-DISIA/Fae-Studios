﻿#include "Ott.h"
#include "../../utils/InputHandler.h"

Ott::Ott(const Vector2D& position, Texture* texture, Texture* tree, Texture* water, Texture* fire, PlayState* game, const Scale& scale) : Entity(position, texture, Vector2D(0, 0), 5, game, scale) {

	textures.push_back(texture);
	textures.push_back(tree);
	textures.push_back(water);
	textures.push_back(fire);
}

void Ott::setAnimState(ANIM_STATE newState) {
	timer = 0;
	if (newState == TP_IN) {
		tp = true;
		row = 6;
		if (animState != newState) col = 0;
		else col = (col + 1) % 4;
		if (animState == newState && col == 0) { newState = TP_OUT; col = 3; }
	}
	else if (newState == TP_OUT) {
		tp = true;
		row = 6;
		col--;
		if (col == 0) { newState = IDLE; tp = false; }
	}

	if (newState == IDLE)
	{
		row = 0;
		if (animState != newState) col = 0;
		else col = (col + 1) % 2;
	}
	else if (newState == JUMPING)
	{
		row = 5;
		col = 2;
	}
	else if (newState == PEAK && !climb) {
		row = 5;
		col = 3;
	}
	else if (newState == FALLING && !climb) {
		row = 5;
		col = 4;
	}
	else if (newState == LAND && !climb) {
		row = 5;
		col = 5;
		timer = 0.5 * ANIMATION_FRAME_RATE;
	}
	else if (newState == WALKING) {
		row = 2;
		if (animState != newState) col = 0;
		else col = (col + 1) % 4;
	}
	else if (newState == ATTACK)
	{
		row = 8;
		if (col < 6) {
			col++;
			timer = ANIMATION_FRAME_RATE / 2;
		}
		else {
			col = 0;
			attack = false;
		}
	}
	else if (newState == CHANGE)
	{
		row = 6;
		if (nextElement != currentElement) {
			if (col < 2)
			{
				col++;
				timer = ANIMATION_FRAME_RATE * 3 / 4;
			}
			else currentElement = nextElement;
		}
		else {
			if (col > 0) {
				col--;
				timer = ANIMATION_FRAME_RATE * 3 / 4;
			}
			else change = false;
		}
	}
	else if(newState == DIE)
	{
		row = 7;
		if (col < 7)col++;
		else die();
	}

	animState = newState;
}

void Ott::handleEvents() {
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
	auto input = InputHandler::instance();
	if (input->keyDownEvent()) {
		if (!dieAnim) {
			if (input->isKeyDown(SDLK_LEFT)) {
				left = true;
				right = false;
				ismoving = true;
				lookingFront = false;
			}
			else if (input->isKeyDown(SDLK_RIGHT))
			{
				ismoving = true;
				left = false;
				right = true;
				lookingFront = true;
			}

			if (input->isKeyJustDown(SDLK_SPACE)) {
				jump();
				ismoving = true;
				up = true;
			}
			if (input->isKeyDown(SDLK_q) && lastSanctuary != nullptr) {
				SDL_Rect sRect = lastSanctuary->getRect();
				SDL_Rect col = getRect();
				if (SDL_HasIntersection(&col, &sRect)) resetLives();
				ismoving = true;
			}
			if (!attack && !change && input->isKeyDown(SDLK_e)) {
				attack = true;
				ismoving = true;
			}
			if (!change && input->isKeyDown(SDLK_a)) {
				change = true;
				ismoving = true;
				nextElement = 1;
			}
			if (!change && input->isKeyDown(SDLK_d)) {
				change = true;
				ismoving = true;
				nextElement = 2;
			}
			if (!change && input->isKeyDown(SDLK_w)) {
				change = true;
				ismoving = true;
				nextElement = 3;
			}
			if (!change && input->isKeyDown(SDLK_s)) {
				change = true;
				ismoving = true;
				nextElement = 0;
			}
			if (input->isKeyDown(SDLK_x)) {
				recieveDamage(currentElement);
			}
			if (input->isKeyDown(SDLK_k)) {
				dieAnim = true;
				col = 2;
				setAnimState(DIE);
			}
			//PRUEBA CORAZON ALEX
			/*if (input->isKeyDown(SDLK_r)) {
				weakened = true;
			}*/
			if (climb && input->isKeyDown(SDLK_UP)) {
				upC = true;
				down = false;
			}
			if (input->isKeyDown(SDLK_DOWN)) {
				down = true;
				upC = false;
			}
		}
		else {
			if (input->isKeyDown(SDLK_k)) {
				dieAnim = false;
			}
		}
	}
	if (input->keyUpEvent()) {
		if (input->isKeyJustUp(SDLK_LEFT)) {
			left = false;
		}
		if (input->isKeyJustUp(SDLK_RIGHT))
		{
			right = false;
		}
		if (input->isKeyUp(SDLK_RIGHT) && input->isKeyUp(SDLK_LEFT)) {
			ismoving = false;
		}
		if (input->isKeyJustUp(SDLK_SPACE)) {
			up = false;
		}
		if (input->isKeyJustUp(SDLK_UP)) {
			upC = false;
		}
		if (input->isKeyJustUp(SDLK_DOWN)) {
			down = false;
		}
	}
}

bool Ott::canJump() {
	return ground;
}

void Ott::jump() {
	if (isGrounded()) { //metodo canjump es lo mismo pero no inline? 
		if (!attack && !change) { setAnimState(JUMPING); }
		speed = Vector2D(speed.getX(), jumpForce);
	}
}

void Ott::setSpeed() {
	if (right) speed = Vector2D(horizontalSpeed, speed.getY());
	else if (left) speed = Vector2D(-horizontalSpeed, speed.getY());
	else speed = Vector2D(0, speed.getY());
	if (upC && climb) { speed = Vector2D(speed.getX(), climbForce); notGroundedBefore = true; }
	if (!ground && down && climb) { speed = Vector2D(speed.getX(), -climbForce); notGroundedBefore = false; }
	if (climb && !upC && !down) { speed = Vector2D(speed.getX(), 0); notGroundedBefore = false; }
}

// Método usado para comprobar en qué animación estamos
// Si se usa animState = 'ESTADO', es para que cambie en el siguiente FRAME de animación
// Si se usa setAnimState, es para que cambie sin esperar a ningún frame, que lo haga directamente
void Ott::updateAnimState() {
	ANIM_STATE previous = animState;
	if (!dieAnim) {
		if (attack) { // animación de ataque
			if (previous != ATTACK) { // si se estaba atacando antes, no hace falta volver a poner la animación de ataque
				col = 2;
				setAnimState(ATTACK);
			}
		}
		else if (change) { // animación de ataque
			if (previous != CHANGE) { // si se estaba atacando antes, no hace falta volver a poner la animación de ataque
				col = 0;
				setAnimState(CHANGE);
			}
		}
		else if (!ismoving && ground) { animState = IDLE; } // personaje quieto
		else if (ismoving && ground) { animState = WALKING; } // personaje caminando
		else if (speed.getY() < 0.5 && speed.getY() > -0.5 && !ground) { // personaje alcanza el punto máximo de la caída
			setAnimState(PEAK);
		}
		else if (speed.getY() >= 1.5) { // personaje cae en picado
			setAnimState(FALLING);
		}
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

	setSpeed(); // ver qué velocidad debería tener Ott ahora en función del input

	// AVANZAR / CAMBIAR DE ANIMACIÓN SEGÚN ANIMATION_FRAME_RATE
	timer++; // aumentar timer
	if (timer >= ANIMATION_FRAME_RATE) { // comprobar si hay que cambiar/avanzar la animacións
		timer = 0;
		setAnimState(animState); // cambio/avance de animación
	}

	// Ajustamos el rectángulo que comprueba la colisión con el suelo
	onGround = getRect();
	onGround.y += onGround.h;
	onGround.h = MAX_VERTICAL_SPEED - 1;
	onGround.w /= 2;
	onGround.x += onGround.w / 2;
	if (!tp) { // Si ott no se está teletransportando, puede moverse y hacer las comprobaciones pertinentes
		updateAnimState();
		if (speed.getY() > MAX_VERTICAL_SPEED) { speed = Vector2D(speed.getX(), MAX_VERTICAL_SPEED); } // si la velocidad vertical supera un máximo, se fixea a ese máximo

		#pragma region COLISIONES (HIPER MEGA PROVISIONAL. MUY PROVISIONAL)
		position = position + speed;

		SDL_Rect groundCol, colRect; // recoge el rectángulo de colisión entre ott y el objeto físico contra el que colisione
		SDL_Rect thisRect = getRect();

		game->ottCollide(thisRect, onGround, groundCol, colRect, ground, speed); // se llama a la función collide del playState

		if (ground) { // si se ha chocado con el suelo...
			if (!(speed.getY() < 0) && !notGroundedBefore) { // y no se le ha fixeado la posición y la velocidad. En caso de que ya se le haya fixeado ya, no se entra aquí
				position = Vector2D(position.getX(), groundCol.y - height);
				speed = Vector2D(speed.getX(), 0);
				if (!attack &&!change) setAnimState(LAND);
			}

			notGroundedBefore = true;
		}
		else { 
			notGroundedBefore = false; 
			
		}// en caso de no estar en el suelo, habrá que fixear la posición cuando choque contra algún suelo

		//timer que comprueba si sigue teniendo una vida debil
		if (weakened && (SDL_GetTicks() - weakTimer) >= timeWeak * 1000) { 
			weakened = false; 
			game->getHealthBar()->changeHealth(UNWEAKEN_CONTAINER);
		}
		
		// mover al personaje
		#pragma endregion
	}
	else if (animState == TP_OUT) position = tpPosition; // en caso de estarse teletransportando entre lámparas, se fixea su posición
														 // a la de la lámpara objetivo
}

// renderizado de Ott
void Ott::render(const SDL_Rect& Camera) const {
#pragma region CONTROLLER INPUT
	/*
	texture->renderFrame(getRect(), 0, 0, arrowAngle);
	*/
#pragma endregion

	// se fija su posición en funciónd de la cámara.
	SDL_Rect ottRect = getRect();
	ottRect.x -= Camera.x;
	ottRect.y -= Camera.y;
	if (!lookingFront) { // si no estamos mirando al frente, debemos poner que su sprite está girado
		textures[currentElement]->renderFrame(ottRect, row, col, 0, SDL_FLIP_HORIZONTAL);
	}
	else textures[currentElement]->renderFrame(ottRect, row, col);
}

// Método para recibir daño
void Ott::recieveDamage(int elem)
{
	if (SDL_GetTicks() - invencibilityTimer <= invincibilityTime * 1000) return;
	invencibilityTimer = SDL_GetTicks();
	if (elementsInfo[elem][currentElement] == 0) {
		if (!weakened) {
			weakened = true;
			game->getHealthBar()->changeHealth(WEAKEN_CONTAINER);
			weakTimer = SDL_GetTicks();
		}
		else {
			weakened = false;
			life--;
			game->getHealthBar()->changeHealth(UNFULL_WEAKENED_CONTAINER);
			Entity::recieveDamage(elem);
		}
	}
	else {
		Entity::recieveDamage(elem);
		game->getHealthBar()->changeHealth(UNFULL_FULL_CONTAINER);
	}
}

bool Ott::collide(const SDL_Rect& obj, SDL_Rect& result) // qué es esto gente
{
	return false;
}

// colisión de Ott con el entorno
bool Ott::collide(GameObject* c)
{
	if (Sanctuary* o = dynamic_cast<Sanctuary*> (c)) { // en caso de que colisione con un santuario...
		SDL_Rect col = getRect();
		SDL_Rect sactRect = o->getRect();
		if (SDL_HasIntersection(&sactRect, &col)) { 
			if (lastSanctuary != o) {
				cout << "Toca sanctuario" << endl; // se pone su último santuario tocado a este.
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
		game->getHealthBar()->changeHealth(FULL_ALL_CONTAINERS);
		notGroundedBefore = false;
	}
}

// método para settear el punto de teletransporte. no se teletransporte directamente porque se tiene que hacer una pequeña animación
void Ott::setTpPoint(const Vector2D& newPos) {
	tpPosition = newPos;
	notGroundedBefore = false;

	// Aquí me gustaría poner la velocidad en la Y a 0, pero la gravedad sigue afectando cuando estás en el aire, y 
	// en las pruebas que se han hecho de momento con las lámparas Ott aparece en el aire. David amigo no te entiende ni cristo
	// con este comentario, pero bueno. preguntadme si no entendéis que es esto.
	// speed = Vector2D(speed.getX(), speed.getY());
}

void Ott::setPos(const Vector2D& newPos ) {
	position = newPos;
}
#pragma endregion