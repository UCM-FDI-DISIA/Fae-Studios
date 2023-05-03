#include "PlayerInput.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/ecs.h"

PlayerInput::PlayerInput()
{
}

void PlayerInput::initComponent()
{
	physics_ = ent_->getComponent<PhysicsComponent>();
	anim_ = ent_->getComponent<PlayerAnimationComponent>();
	attack_ = ent_->getComponent<PlayerAttack>();
	image_ = ent_->getComponent<FramedImageOtt>();
	health_ = ent_->getComponent<Health>();
	shield_ = ent_->getComponent<ShieldComponent>();
	horizontalSpeed = physics_->getHorizontalSpeed();
}

void PlayerInput::update()
{
	if (!physics_->isStopped()) {
		Vector2D& playerV = physics_->getVelocity();
		auto input = InputHandler::instance();
		auto state = anim_->getState();
		if (input->keyDownEvent() && state != DIE && !openingMap) {
			if (input->isKeyDown(SDLK_LEFT)) {
				//Moviento Izquierda 
				playerV = Vector2D(-horizontalSpeed, playerV.getY());
				physics_->lookDirection(false);
                if(physics_->isGrounded() && !physics_->isClimbing() && abs(physics_->getVelocity().getX()) > 0) sdlutils().soundEffects().at("ott_step").playFor(1000,0, ecs::_channel_PLAYER);
			}
			if (input->isKeyDown(SDLK_RIGHT))
			{
				//Movimiento derecha
				playerV = Vector2D(horizontalSpeed, playerV.getY());
				physics_->lookDirection(true);
                if(physics_->isGrounded() && !physics_->isClimbing() && abs(physics_->getVelocity().getX()) > 0) sdlutils().soundEffects().at("ott_step").playFor(1000, 0, ecs::_channel_PLAYER);
			}

			if (input->isKeyDown(SDLK_SPACE)) {
				//Salto
				physics_->jump();
			}
			if (input->isKeyDown(SDLK_q)) {
				ent_->getComponent<AttackCharger>()->addCharge(5);
			}
			if (input->isKeyDown(SDLK_f)) {
				//Recuperar vidas
				static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->checkInteraction();
			}
			if (input->isKeyDown(SDLK_TAB)) {
				if (anim_->getState() != OPEN_MAP && anim_->getState() != CLOSE_MAP && physics_->isGrounded()) {
					anim_->setState(OPEN_MAP);
					sdlutils().soundEffects().at("map").play (0, ecs::_channel_PLAYER);
				}
					
				openingMap = true;
				physics_->setVelocity(Vector2D(0, physics_->getVelocity().getY()));
			}
			if (state != VANISH) {
				if (input->isKeyDown(SDLK_z))
				{
					//Defensa
					//image_->shielded(true);
					//physics_->slowed();
					shield_->takeShield();
				}
				if (input->isKeyJustDown(SDLK_e) && anim_->getState() != ATTACK && !attack && !shield_->hasShield()) {
					//Ataque
					attack = true;
					attackTimer = SDL_GetTicks();

				}
				if (input->isKeyDown(SDLK_a) && earth && !selectedEarth) {
					//Cambio elemento
					anim_->changeElem(ecs::Earth);
					anim_->setState(VANISH);
					selectedEarth = true;
					selectedWater = false;
					selectedFire = false;
					selectedLight = false;
					sdlutils().soundEffects().at("elem_changed").play(0, ecs::_channel_ALERTS);
				}
				if (input->isKeyDown(SDLK_d) && water && !selectedWater) {
					anim_->changeElem(ecs::Water);
					anim_->setState(VANISH);
					selectedEarth = false;
					selectedWater = true;
					selectedFire = false;
					selectedLight = false;
					sdlutils().soundEffects().at("elem_changed").play(0, ecs::_channel_ALERTS);
				}
				if (input->isKeyDown(SDLK_w) && fire && !selectedFire) {
					anim_->changeElem(ecs::Fire);
					anim_->setState(VANISH);
					selectedEarth = false;
					selectedWater = false;
					selectedFire = true;
					selectedLight = false;
					sdlutils().soundEffects().at("elem_changed").play(0, ecs::_channel_ALERTS);
				}
				if (input->isKeyDown(SDLK_s) && !selectedLight) {
					anim_->changeElem(ecs::Light);
					anim_->setState(VANISH);
					selectedEarth = false;
					selectedWater = false;
					selectedFire = false;
					selectedLight = true;
					sdlutils().soundEffects().at("elem_changed").play(0, ecs::_channel_ALERTS);
				}
			}
			if (input->isKeyDown(SDLK_UP)) {
				//Trepar
			}
			if (input->isKeyDown(SDLK_DOWN)) {
				//Agacharse?
			}
		}
		else if (state == DIE) playerV = Vector2D(0, playerV.getY());
		else if (openingMap && state != OPEN_MAP && state != CLOSE_MAP) {
			openingMap = false;
		}
		if (input->isKeyUp(SDLK_LEFT) && input->isKeyUp(SDLK_RIGHT) && !physics_->inKnocback()) {
			playerV = Vector2D(0, playerV.getY());
		}
		if (input->keyUpEvent() && !openingMap) {
			if (state != DIE) {
				if (input->isKeyJustUp(SDLK_RIGHT)) {
					playerV = playerV - Vector2D(horizontalSpeed, 0);
					if (playerV.getX() < -horizontalSpeed) playerV = Vector2D(-horizontalSpeed, playerV.getY());

				}
				if (input->isKeyJustUp(SDLK_LEFT)) {
					playerV = playerV - Vector2D(-horizontalSpeed, 0);
					if (playerV.getX() > horizontalSpeed) playerV = Vector2D(horizontalSpeed, playerV.getY());
				}
				if (input->isKeyJustUp(SDLK_e) && attack) {
					attack = false;
					AttackCharger* pChargedAttackComp = ent_->getComponent<AttackCharger>();
					bool canChargeAttack = pChargedAttackComp->hasChargedAttack();
					bool isCharged = (canChargeAttack && SDL_GetTicks() - attackTimer >= chargedAttackTime * 1000);
					anim_->setState(ATTACK);
					attack_->startAttack(isCharged);
					if (isCharged) {
						int& numCharges = pChargedAttackComp->getCharge(); numCharges = 0;
					}
				}
			}
			if (input->isKeyJustUp(SDLK_z)) {
				//defend = false;
				//image_->shielded(false);
				shield_->guardShield();
			}
		}

		//Interacci�n con una enredadera
		auto vineCol = static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->checkCollisionWithVine();
		int speed = 1;
		if (vineCol.first) {
			if (input->isKeyDown(SDLK_UP) && vineCol.second) {
				physics_->setClimbing(true, -speed);
				anim_->setState(CLIMB);
				if(!SoundEffect::isSoundBeingPlayed(ecs::_channel_AMBIENTAL)) sdlutils().soundEffects().at("vine_climb").play(0, ecs::_channel_AMBIENTAL);
			}
			else if (input->isKeyDown(SDLK_DOWN)) {
				physics_->setClimbing(true, speed);
				anim_->setState(CLIMB);
				if(!SoundEffect::isSoundBeingPlayed(ecs::_channel_AMBIENTAL)) sdlutils().soundEffects().at("vine_climb").play(0, ecs::_channel_AMBIENTAL);
			}
			else physics_->setClimbing(true, 0);
		}
		else physics_->setClimbing(false, 0);
	}
	
}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::loadFromFile(std::ifstream& file) {
	std::string aux;
	file >> aux >> earth >> aux >> water >> aux >> fire;
}


void PlayerInput::saveToFile(std::ofstream& file) {
	file << "earth " << (int)earth << std::endl;
	file << "water " << (int)water << std::endl;
	file << "fire " << (int)fire << std::endl;
}

