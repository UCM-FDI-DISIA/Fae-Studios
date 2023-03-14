#include "Acceleration.h"
#include "../sdlutils/InputHandler.h"

void Acceleration:: initComponent(){
	player = mngr_->getPlayer();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	playerTransform = player->getComponent<Transform>();
}
void Acceleration ::update()
{
	Vector2D distance = playerTransform->getPosition() - transform->getPosition();
	float aux= distance.magnitude();
	auto input = InputHandler::instance();
	
	
	Vector2D vecAux;
	//derecha
	if (physics->getVelocity().getX() > 0.0f)vecAux = { aux/250,0};
	//izquierda
	else if (physics->getVelocity().getX() < 0.0f)vecAux = { -aux / 250,0 };
	//arriba
	else if (physics->getVelocity().getY() < 0.0f)vecAux = {0,-aux/250 };
	//abajo
	else vecAux = { 0,aux / 250 };
	physics->setVelocity(vecAux);


	/*std::cout << "Vel DIS: " << distance << std::endl;
	std::cout << "Vel PLAY: " << playerTransform->getPosition() << std::endl;
	std::cout << "Vel POS: " << transform->getPosition() << std::endl;
	std::cout << "Vel AUX: " << aux / 250 << std::endl;*/


	//limites velocidad
	if (std::abs(physics->getVelocity().getX()) > 3)
	{
		Vector2D temp;
		if(physics->getVelocity().getX()>0) temp = { 3,0 };
		else  temp = { -3,0 };
		physics->setVelocity(temp);
	}
	if (std::abs(physics->getVelocity().getY()) > 3)
	{
		Vector2D temp;
		if (physics->getVelocity().getY() > 0) temp = { 0,3 };
		else  temp = { 0,-3 };
		physics->setVelocity(temp);
	}
}
