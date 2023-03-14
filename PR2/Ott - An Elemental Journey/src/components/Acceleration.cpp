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
	
		std::cout <<std::endl<< "Vel VEL: " << physics->getVelocity() << std::endl;
		Vector2D vecAux;
		if (physics->getVelocity().getX() > 0.0f)vecAux = { aux/250,0};
		else if (physics->getVelocity().getX() < 0.0f)vecAux = { -aux / 250,0 };
		else if (physics->getVelocity().getY() < 0.0f)vecAux = {0,-aux/250 };
		else vecAux = { 0,aux / 250 };
		physics->setVelocity(vecAux);


		std::cout << "Vel DIS: " << distance << std::endl;

		std::cout << "Vel PLAY: " << playerTransform->getPosition() << std::endl;

		std::cout << "Vel POS: " << transform->getPosition() << std::endl;
		std::cout << "Vel AUX: " << aux / 250 << std::endl;


		if (std::abs(physics->getVelocity().getX()) > 2.5)
		{
			Vector2D temp;
			if(physics->getVelocity().getX()>0) temp = { 2.5,0 };
			else  temp = { -2.5,0 };
			physics->setVelocity(temp);
		}
		if (std::abs(physics->getVelocity().getY()) > 2.5)
		{
			Vector2D temp;
			if (physics->getVelocity().getY() > 0) temp = { 0,2.5 };
			else  temp = { 0,-2.5 };
			physics->setVelocity(temp);
		}
	
	if (input->isKeyJustDown(SDLK_o))
	{
		physics->setVelocity({0,0});
	}
	if (input->isKeyJustDown(SDLK_i))
	{
		physics->setVelocity({ 0.5,0 });
	}
}
