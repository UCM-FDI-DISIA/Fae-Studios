#include "PlayerAnimationComponent.h"
#include "PhysicsComponent.h"
#include "Health.h"
#include "../ecs/Entity.h"
#include "FramedImage.h"
#include "../states/PlayState.h"
#include "../states/MapState.h"
#include "../states/GameStateMachine.h"

#pragma once
PlayerAnimationComponent::PlayerAnimationComponent(anims::Entities e)
{
	eAnims = e;
}

void PlayerAnimationComponent::initComponent() {
	image = ent_->getComponent<FramedImageOtt>();
	health = ent_->getComponent<Health>();
	tr_ = ent_->getComponent<Transform>();
	if (health != nullptr) elemToChange = health->getElement();
}

void PlayerAnimationComponent::setState(int newState)
{
	if (state_ != newState) { state_ = newState; image->setCol(getColNum(state_)); timer_ = 0;}
}

void PlayerAnimationComponent::update()
{
	if (!changingElem && !tp) timer_++; // controla el frame que se debe mostrar de la animaci�n actual
	else timer_--;
	int col = image->getCurCol();

	if (state_ == CLOSE_MAP) {
		if(col != 0)
			col = getColNum(state_) - (timer_ / getTPerFrame(state_)) % getNFrames(state_);
	}
	else if (col != getNFrames(state_) + getColNum(state_) - 1 || (changingElem && state_ == VANISH && timer_ < (getTPerFrame(state_) * getNFrames(state_)))) // si no es la �ltima columna de la animaci�n actual, se actualiza
	{
		col = (timer_ / getTPerFrame(state_)) % getNFrames(state_) + getColNum(state_);
	}
	else if (state_ == LOOKDOWN) {
		if (col != getNFrames(state_)-1)
			col = getColNum(state_) - (timer_ / getTPerFrame(state_)) % getNFrames(state_);
	}

	image->setCol(col); // se settea la nueva columna
	image->setRow(getRowNum(state_)); // se settea la fila 
	if ((!changingElem && timer_ > (getTPerFrame(state_) * getNFrames(state_)) + 1)) {// si el timer ha superado al tiempo de cada frame * los frames 
		endAnim();													// que tiene la animaci�n actual, se llama a endAnim();
	}
	else if ((changingElem || tp) && timer_ <= 0) {
		endAnim();
		changingElem = false;
		tp = false;
	}
	if (health->getElement() != elemToChange) {
		setState(VANISH);
	}
	else if(!health->isDead()) {
		if (state_ == ATTACK || state_ == VANISH || state_ == DIE || state_ == LAND || state_ == OPEN_MAP || state_ == CLOSE_MAP || state_ == LOOKDOWN || state_ == LOOKUP) return; // estas animaciones se superponen a todas las dem�s
		auto physics = ent_->getComponent<PhysicsComponent>();
		Vector2D vel = physics->getVelocity(); // velocidad
		if (vel.getY() == 0 && physics->isGrounded()) {
			if (state_ == FALL) setState(LAND); // si se est� cayendo el wach�n y acaba de aterrizar, se pone en su estado LAND
			else if (vel.getX() != 0) setState(RUN); // estado correr
			else setState(IDLE); // idle
		}
		else if (physics->isClimbing())  state_ = CLIMB;
		else if ((vel.getY() <0.15&&vel.getY()>-0.15) && !physics->isGrounded()){	setState(PEAK); } // si no se mueve en la Y y no est� en suelo, se pone PEAK
		else if (vel.getY() < 0) { setState(JUMP_UP);} // salto 
		else { setState(FALL); } // ca�da
		if (invincible && SDL_GetTicks() - damageTimer >= invencibilityTime * 1000) invincible = false; // invencibilidad. CAMBIAR
	}
}

void PlayerAnimationComponent::endAnim()
{
	if ((!changingElem || !tp) && state_ == VANISH) {
		health->setElement(elemToChange);
		image->changeElement(elemToChange);
		changingElem = true;
		tp = true;
		if (canTp) {
			if (tpPos.getX() != 0) tr_->setPosition(tpPos);
			canTp = false;
		}
	}
	else {
		if (state_ == DIE) {
			health->recall(); // volver al �ltimo santuario 
		}
		if (state_ == IDLE) image->setCol(0); // reiniciar estado IDLE
		else if (state_ == OPEN_MAP) {
			GameStateMachine::instance()->pushState(new MapState(static_cast<PlayState*> (GameStateMachine::instance()->getPlayState())));
		}
		else if (state_ == LOOKDOWN) return;
		else setState(IDLE); // poner estado idle 
		if(state_ != DIE) timer_ = 0; // reiniciar el timer
	}
}

PlayerAnimationComponent::~PlayerAnimationComponent()
{
}