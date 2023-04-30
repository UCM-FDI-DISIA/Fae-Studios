#include "PlayerInput.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/ecs.h"
#include "../game/Game.h"

PlayerInput::PlayerInput()
{
	earth = false;
	water = false;
	fire = false;
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
	tr_ = ent_->getComponent<Transform>();
}

void PlayerInput::update()
{
	if (!stopped) {
		SDL_JoystickUpdate();
		if (stunned) {
			if (SDL_GetTicks() - timerStunned >= stunnedTime * 1000) stunned = false;
			else return;
		}

		if (!physics_->isStopped()) {
			Vector2D& playerV = physics_->getVelocity();
			auto input = InputHandler::instance();
			auto state = anim_->getState();
			if (input->keyDownEvent() && state != DIE && !openingMap) {
				if (input->isKeyDown(SDLK_LEFT) || (game().getIsJoystick() && (SDL_JoystickGetAxis(game().getJoystick(), 0) < -1000  || SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_DPAD_LEFT)))) {
					//Moviento Izquierda 
					playerV = Vector2D(-horizontalSpeed, playerV.getY());
					physics_->lookDirection(false);
					if(physics_->isGrounded() && !physics_->isClimbing() && abs(physics_->getVelocity().getX()) > 0) sdlutils().soundEffects().at("ott_step").playFor(1000,0, ecs::_channel_PLAYER);
				}
				if (input->isKeyDown(SDLK_RIGHT) || (game().getIsJoystick() && (SDL_JoystickGetAxis(game().getJoystick(), 0) > 1000 || SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_DPAD_RIGHT))))
				{
					//Movimiento derecha
					playerV = Vector2D(horizontalSpeed, playerV.getY());
					physics_->lookDirection(true);
					if(physics_->isGrounded() && !physics_->isClimbing() && abs(physics_->getVelocity().getX()) > 0) sdlutils().soundEffects().at("ott_step").playFor(1000, 0, ecs::_channel_PLAYER);
				}

				if (input->isKeyDown(SDLK_SPACE) || (game().getIsJoystick() && SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_A))) {
					//Salto
					if (!game().getIsJoystick())
						physics_->jump();
					else if (SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_B) == 0)
						physics_->jump();
				}
				if (input->isKeyDown(SDLK_q)) {
					ent_->getComponent<AttackCharger>()->addCharge(8);
				}
				if (canInteract && (input->isKeyDown(SDLK_f) || (game().getIsJoystick() && SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_Y)))) {
					//Recuperar vidas
					static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->interact();
				}
				if (input->isKeyDown(SDLK_TAB) || (game().getIsJoystick() && SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_BACK))) {
					if (anim_->getState() != OPEN_MAP && anim_->getState() != CLOSE_MAP && physics_->isGrounded()) {
						anim_->setState(OPEN_MAP);
						sdlutils().soundEffects().at("map").play (0, ecs::_channel_PLAYER);
					}
					
					openingMap = true;
					physics_->setVelocity(Vector2D(0, physics_->getVelocity().getY()));
				}
				if (state != VANISH) {
					if (input->isKeyDown(SDLK_z) || (game().getIsJoystick() && SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_B)))
					{
						//Defensa
						//image_->shielded(true);
						//physics_->slowed();
						shield_->takeShield();
					}
					if ((input->isKeyJustDown(SDLK_e) || (game().getIsJoystick() && SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_X))) && anim_->getState() != ATTACK && !attack && !shield_->hasShield()) {
						//Ataque
						attack = true;
						attackTimer = SDL_GetTicks();
					}
					if ((input->isKeyDown(SDLK_a) || (game().getIsJoystick() && SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))) && earth && !selectedEarth) {
						//Cambio elemento
						anim_->changeElem(ecs::Earth);
						anim_->setState(VANISH);
						selectedEarth = true;
						selectedWater = false;
						selectedFire = false;
						selectedLight = false;
						sdlutils().soundEffects().at("elem_changed").play(0, ecs::_channel_ALERTS);
						if (game().getIsJoystick() && SDL_JoystickHasLED(game().getJoystick())) {
							SDL_JoystickSetLED(game().getJoystick(), 0, UINT8_MAX, 0);
						}
					}
					if ((input->isKeyDown(SDLK_d) || (game().getIsJoystick() && SDL_JoystickGetAxis(game().getJoystick(), SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 100)) && water && !selectedWater) {
						anim_->changeElem(ecs::Water);
						anim_->setState(VANISH);
						selectedEarth = false;
						selectedWater = true;
						selectedFire = false;
						selectedLight = false;
						sdlutils().soundEffects().at("elem_changed").play(0, ecs::_channel_ALERTS);

						if (game().getIsJoystick() && SDL_JoystickHasLED(game().getJoystick())) {
							SDL_JoystickSetLED(game().getJoystick(), 0, 0, UINT8_MAX);
						}
					}
					if ((input->isKeyDown(SDLK_w) || (game().getIsJoystick() && SDL_JoystickGetAxis(game().getJoystick(), SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 100)) && fire && !selectedFire) {
						anim_->changeElem(ecs::Fire);
						anim_->setState(VANISH);
						selectedEarth = false;
						selectedWater = false;
						selectedFire = true;
						selectedLight = false;
						sdlutils().soundEffects().at("elem_changed").play(0, ecs::_channel_ALERTS);

						if (game().getIsJoystick() && SDL_JoystickHasLED(game().getJoystick())) {
							SDL_JoystickSetLED(game().getJoystick(), UINT8_MAX, 0, 0);
						}
					}
					if ((input->isKeyDown(SDLK_s) || (game().getIsJoystick() && SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_LEFTSHOULDER))) && !selectedLight) {
						anim_->changeElem(ecs::Light);
						anim_->setState(VANISH);
						selectedEarth = false;
						selectedWater = false;
						selectedFire = false;
						selectedLight = true;
						sdlutils().soundEffects().at("elem_changed").play(0, ecs::_channel_ALERTS);

						if (game().getIsJoystick() && SDL_JoystickHasLED(game().getJoystick())) {
							SDL_JoystickSetLED(game().getJoystick(), UINT8_MAX, UINT8_MAX, UINT8_MAX);
						}
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
					if ((input->isKeyJustUp(SDLK_e) || (game().getIsJoystick() && SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_X))) && attack) {
						attack = false;
						AttackCharger* pChargedAttackComp = ent_->getComponent<AttackCharger>();
						bool canChargeAttack = pChargedAttackComp->hasChargedAttack();
						bool isCharged = (canChargeAttack && SDL_GetTicks() - attackTimer >= chargedAttackTime * 1000);
						anim_->setState(ATTACK);
						attack_->startAttack(isCharged);
						if (isCharged) {
							int& numCharges = pChargedAttackComp->getCharge(); numCharges = 0;
							pChargedAttackComp->resetCharges();
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
				if ((input->isKeyDown(SDLK_UP) || (game().getIsJoystick() && (SDL_JoystickGetAxis(game().getJoystick(), 1) < -100 || SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_DPAD_UP)))) && vineCol.second) {
					physics_->setClimbing(true, -speed);
					anim_->setState(CLIMB);
					if(!SoundEffect::isSoundBeingPlayed(ecs::_channel_AMBIENTAL)) sdlutils().soundEffects().at("vine_climb").play(0, ecs::_channel_AMBIENTAL);
				}
				else if (input->isKeyDown(SDLK_DOWN) || (game().getIsJoystick() && (SDL_JoystickGetAxis(game().getJoystick(), 1) > 100 || SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_DPAD_DOWN)))) {
					physics_->setClimbing(true, speed);
					anim_->setState(CLIMB);
					if(!SoundEffect::isSoundBeingPlayed(ecs::_channel_AMBIENTAL)) sdlutils().soundEffects().at("vine_climb").play(0, ecs::_channel_AMBIENTAL);
				}
				else physics_->setClimbing(true, 0);
			}
			else physics_->setClimbing(false, 0);
		}
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

