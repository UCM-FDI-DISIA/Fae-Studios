#include "ShowAtOpposideSide.h"
#include "../ecs/Entity.h"

void ShowAtOpposideSide::update()
{
	if (transform->getPosition().getX() < -transform->getWidth()) //Se compara la posición con el ancho de la textura para que no de la sensación de que se teletransporta
		transform->setPosition(Vector2D(SDLUtils::instance()->width() - 1, transform->getPosition().getY())); //Si se va por la izquierda de la pantalla aparece en la derecha
	else if (transform->getPosition().getX() > SDLUtils::instance()->width()) 
		transform->setPosition(Vector2D(-transform->getWidth() + 1, transform->getPosition().getY())); //Si se va por la derecha de la pantalla aparece en la izquierda

	if (transform->getPosition().getY() < -transform->getHeight())
		transform->setPosition(Vector2D(transform->getPosition().getX(), SDLUtils::instance()->height() - 1)); //Si se va por arriba aparece por abajo
	else if (transform->getPosition().getY() > SDLUtils::instance()->height())
		transform->setPosition(Vector2D(transform->getPosition().getX(), -transform->getHeight() + 1)); //Si se va por abajo aparece por arriba
}

void ShowAtOpposideSide::initComponent() {
	transform = ent_->getComponent<Transform>();
	assert(transform != nullptr);
}
