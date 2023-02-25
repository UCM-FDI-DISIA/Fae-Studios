#include "PlayerInput.h"

PlayerInput::PlayerInput()
{
}

void PlayerInput::initComponent()
{
	physics_ = ent_->getComponent<PhysicsComponent>();
}

void PlayerInput::update()
{
	Vector2D& playerV = physics_->getVelocity();
	auto input = InputHandler::instance();
	if (input->keyDownEvent()) {
		cout << "Tecla pulsada" << endl;
		if (input->isKeyDown(SDLK_z))
		{
			//Defensa
		}
		if (input->isKeyDown(SDLK_LEFT)) {
			//Moviento Izquierda 
			playerV = Vector2D(-1, playerV.getY());
		}
		else if (input->isKeyDown(SDLK_RIGHT))
		{
			//Movimiento derecha
			playerV = Vector2D(1, playerV.getY());
		}

		if (input->isKeyJustDown(SDLK_SPACE)) {
			//Salto
		}
		if (input->isKeyDown(SDLK_q)) {
			//Recuperar vidas
		}
		if (input->isKeyDown(SDLK_e)) {
			//Ataque
		}
		if (input->isKeyDown(SDLK_a)) {
			//Cambio elemento
		}
		if (input->isKeyDown(SDLK_d)) {
			//Cambio elemento
		}
		if (input->isKeyDown(SDLK_w)) {
			//Cambio elemento
		}
		if (input->isKeyDown(SDLK_s)) {
			//Cambio elemento
		}
		if (input->isKeyDown(SDLK_UP)) {
			//Trepar
		}
		if (input->isKeyDown(SDLK_DOWN)) {
			//Agacharse?
		}
	} 
	if (input->keyUpEvent()) {
		cout << "No hay tecla" << endl;
		//playerV = (0, 1);
		if (input->isKeyJustUp(SDLK_LEFT)) {
			//left = false;
		}
		if (input->isKeyJustUp(SDLK_RIGHT))
		{
			//if (left) lookingFront = false;
			//right = false;
		}
		if (input->isKeyUp(SDLK_RIGHT) && input->isKeyUp(SDLK_LEFT)) {
			//ismoving = false;
		}
		if (input->isKeyJustUp(SDLK_SPACE)) {
			//up = false;
		}
		if (input->isKeyJustUp(SDLK_UP)) {
			//upC = false;
		}
		if (input->isKeyJustUp(SDLK_DOWN)) {
			//down = false;
		}
		if (input->isKeyJustUp(SDLK_z)) {
			//defend = false;
		}
	}
}

PlayerInput::~PlayerInput()
{

}

