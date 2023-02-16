#include "Ott.h"
#include "../../utils/InputHandler.h"

Ott::Ott(const Vector2D& position, Texture* texture, PlayState* game, const Scale& scale) : Entity(position, texture, Vector2D(0, 0), 5, game, scale) {
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
	else if (newState == PEAK) {
		row = 5;
		col = 3;
	}
	else if (newState == FALLING) {
		row = 5;
		col = 4;
	}
	else if (newState == LAND) {
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
			cout << "atacando" << endl;
			col++;
			timer = ANIMATION_FRAME_RATE / 2;
		}
		else {
			col = 0;
			attack = false;
		}
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
		if (!attack && input->isKeyDown(SDLK_e)) {
			attack = true;
			ismoving = true;
		}
		if (input->isKeyDown(SDLK_x)) {
			recieveDamage(currentElement);
		}
		if (climb && input->isKeyDown(SDLK_UP)) {
			upC = true;
		}
		if (input->isKeyDown(SDLK_DOWN)) {
			down = true;
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

	//hacer bool/cambiar si solo se podia mover una vez en el salto creo recordar
	/*if (event.type == SDL_KEYDOWN) {
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
		if (!attack&& event.key.keysym.sym == SDLK_e) {
			animState = ATTACK;
			attack = true;
			//cout << "ataque" << endl;
			ismoving = true;
			col = 2;
			timer += ANIMATION_FRAME_RATE / 2;
		}
		if (event.key.keysym.sym == SDLK_x) {
			recieveDamage(currentElement);
		}
		if (climb && event.key.keysym.sym == SDLK_UP) {
			upC = true;
			down = false;
		}
		if (climb && event.key.keysym.sym == SDLK_DOWN) {
			down = true;
			upC = false;
		}
		//cout << animState << endl;
		//cout << dir.getX() << endl;
	}
	*/
	/*if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_LEFT) {
			left = false;
			dir = Vector2D(-1, 0);
			//cout << "L_Out" << endl;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			right = false;
			//dir = Vector2D(1, 0);
			//cout << "R_Out" << endl;
		}
		if (event.key.keysym.sym == SDLK_SPACE) {
			jump();
			up = false;
		}
		if (event.key.keysym.sym == SDLK_e) {
		/*	attack = false;*/
			//cout << "ataqueOut" << endl;
		//}
		/*if (event.key.keysym.sym == SDLK_UP) {
			upC = false;
		}
		if (event.key.keysym.sym == SDLK_DOWN) {
			down = false;
			
		}
		//cout << animState << endl;
		//cout << dir.getX() << endl;
	}*/
}

bool Ott::canJump() {
	return ground;
}

void Ott::jump() {
	if (isGrounded()) { //metodo canjump es lo mismo pero no inline? 
		if (!attack) { setAnimState(JUMPING); }
		speed = Vector2D(speed.getX(), jumpForce);
	}
}

void Ott::setSpeed() {
	if (right) speed = Vector2D(horizontalSpeed, speed.getY());
	else if (left) speed = Vector2D(-horizontalSpeed, speed.getY());
	else speed = Vector2D(0, speed.getY());
	if (upC) speed = Vector2D(speed.getX(), -climbForce);
	if (down) speed = Vector2D(speed.getX(), climbForce);
}

// Método usado para comprobar en qué animación estamos
// Si se usa animState = 'ESTADO', es para que cambie en el siguiente FRAME de animación
// Si se usa setAnimState, es para que cambie sin esperar a ningún frame, que lo haga directamente
void Ott::updateAnimState() {
	ANIM_STATE previous = animState;
	if (attack) { // animación de ataque
		if (previous != ATTACK) { // si se estaba atacando antes, no hace falta volver a poner la animación de ataque
			col = 2;
			setAnimState(ATTACK);
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

void Ott::update() {
#pragma region CONTROLLER INPUT
	/*
	// C�lculo de �ngulo para mostar direcci�n en la que apunta el Joystick
	arrowAngle = atan2((double)yDir, (double)xDir) * (180 / M_PI);
	if (xDir == 0 && yDir == 0) arrowAngle = 0;
	*/
#pragma endregion
	if (!right && !left)
	{
		if (!attack) {
			//cout << "SALII" << endl;
			ismoving = false;
		}
		speed =  Vector2D(0, speed.getY());
	}
	if (right)speed = Vector2D(1, speed.getY());
	if (left) speed = Vector2D(-1, speed.getY());
	if (upC && climb) {  speed = Vector2D(speed.getX(), climbForce); notGroundedBefore = false; }
	if (!ground&&down && climb) { speed = Vector2D(speed.getX(), -climbForce); notGroundedBefore = false;}
 	if ( climb && !upC && !down) { speed = Vector2D(speed.getX(), 0); notGroundedBefore = false; }
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
	onGround.h = -jumpForce - 1;

	if (!tp) { // Si ott no se está teletransportando, puede moverse y hacer las comprobaciones pertinentes
		updateAnimState();
		if (speed.getY() > MAX_VERTICAL_SPEED) { speed = Vector2D(speed.getX(), MAX_VERTICAL_SPEED); } // si la velocidad vertical supera un máximo, se fixea a ese máximo

#pragma region COLISIONES (HIPER MEGA PROVISIONAL. MUY PROVISIONAL)
		SDL_Rect groundCol; // recoge el rectángulo de colisión entre ott y el objeto físico contra el que colisione
		bool col = false; // booleano que recoge si ha chocado o no. No se usa para nada de momento porque no hay implementadas colisiones
						  // con paredes, solo con suelo
		game->ottCollide(getRect(), onGround, groundCol, col, ground); // se llama a la función collide del playState
		if (ground) { // si se ha chocado con el suelo...
			if (!notGroundedBefore) { // y no se le ha fixeado la posición y la velocidad. En caso de que ya se le haya fixeado ya, no se entra aquí
				position = Vector2D(groundCol.x, groundCol.y - height);
				speed = Vector2D(speed.getX(), 0);
				if (!attack) setAnimState(LAND);
			}
			isJumping = false;
			notGroundedBefore = true;
		}
		else notGroundedBefore = false; // en caso de no estar en el suelo, habrá que fixear la posición cuando choque contra algún suelo

		//timer que comprueba si sigue teniendo una vida debil
		if (weakened && (SDL_GetTicks() - weakTimer) >= timeWeak * 1000) weakened = false;
		
		// mover al personaje
		position = position + speed;
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
		texture->renderFrame(ottRect, row, col,0,SDL_FLIP_HORIZONTAL);
	}
	else texture->renderFrame(ottRect, row, col);
}

// Método para recibir daño
void Ott::recieveDamage(int elem)
{
	if (elementsInfo[elem][currentElement] == 0) { // comprobación para ver cuánto daño se recibe en función del elemento que tengas
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
	}
	else {
		SDL_Rect r = lastSanctuary->getRect();
		Vector2D newPos = { (double)r.x, (double)r.y - 50 };
		position = newPos;
		life = maxLife;
		notGroundedBefore = false;
	}
}

// método para settear el punto de teletransporte. no se teletransporte directamente porque se tiene que hacer una pequeña animación
void Ott::setTpPoint(const Vector2D& newPos) {
	tpPosition = newPos;
	notGroundedBefore = false;
	speed = Vector2D(speed.getX(), speed.getY());
}
#pragma endregion