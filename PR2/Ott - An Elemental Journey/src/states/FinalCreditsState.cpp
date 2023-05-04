#include "FinalCreditsState.h"
#include"../game/Game.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/TextComponent.h"
#include "../components/PhysicsComponent.h"
#include "../sdlutils/InputHandler.h"
#include "GameStateMachine.h"

void FinalCreditsState::createNextName()
{
	lastName = mngr_->addEntity(ecs::_grp_UI);
	auto txt = lastName->addComponent<TextComponent>(names.top(), sdlutils().fonts().at("press_start16"), white, transparent);
	Vector2D pos = Vector2D((sdlutils().width() / 2) - (txt->getWidth() / 2), -txt->getHeight());
	txt->setPosition(pos);
	names.pop();
}

void FinalCreditsState::namesManager()
{
	for (Entity* t : mngr_->getEntities(ecs::_grp_UI)) {
			TextComponent* txt = t->getComponent<TextComponent>();
			if (t != endText && txt->getPosition().getY() >= sdlutils().height())
				t->setAlive(false);
			else if (t == endText) {
				if (txt->getPosition().getY() + txt->getHeight() / 2 >= sdlutils().height() / 2) {
					speed = Vector2D(0, 0);
					end = true;

					Entity* n = mngr_->addEntity(ecs::_grp_UI);
					TextComponent* aux;
					if(game().getIsJoystick())
						aux = n->addComponent<TextComponent>("Presiona Start para salir al menú principal", sdlutils().fonts().at("press_start16"), white, transparent);
					else
						aux = n->addComponent<TextComponent>("Presiona Espacio para salir al menú principal", sdlutils().fonts().at("press_start16"), white, transparent);
					Vector2D pos = Vector2D(0, 0);
					aux->setPosition(pos);
				}
			}

			Vector2D pos = Vector2D(txt->getPosition() + speed);
			txt->setPosition(pos);
	}
}

FinalCreditsState::FinalCreditsState() : GameState(ecs::_state_CREDITS)
{
	names.push("CLAUDIA ZARZUELA AMOR");
	names.push("ANDREA VEGA SAUGAR");
	names.push("PABLO SANCHEZ MARTIN");
	names.push("DAVID RIVERA MARTINEZ");
	names.push("MIGUEL RAMIREZ CASTRILLO");
	names.push("ROI QUINTAS DIZ");
	names.push("RAUL PEREZ COGOLLUDO");
	names.push("ALEJANDRO MASSO MARTINEZ");
	names.push("PAULA LOPEZ ROMAN");
	names.push("NAHIA IGLESIAS CALVO");
	names.push("EVA FELIU AREJOLA");

	timer = SDL_GetTicks() + NEXT_NAME;
	endText = nullptr;
	speed = Vector2D(0, 1);
	createNextName();
}

void FinalCreditsState::update()
{
	GameState::update();
	if (names.size() > 0 && /*SDL_GetTicks() > timer*/ lastName->getComponent<TextComponent>()->getPosition().getY() >= sdlutils().height() / 4) {
		createNextName();
		timer = SDL_GetTicks() + NEXT_NAME;
	}
	else if (endText == nullptr && names.size() == 0 && /*SDL_GetTicks() > timer*/lastName->getComponent<TextComponent>()->getPosition().getY() >= sdlutils().height()) {
		endText = mngr_->addEntity(ecs::_grp_UI);
		auto txt = endText->addComponent<TextComponent>("GRACIAS POR JUGAR!", sdlutils().fonts().at("press_start16"), white, transparent);
		Vector2D pos = Vector2D((sdlutils().width() / 2) - (txt->getWidth() / 2), -txt->getHeight());
		txt->setPosition(pos);
	}
	if(!end)
		namesManager();
}

void FinalCreditsState::handleInput()
{
	if (!end) {
		SDL_GameControllerUpdate();
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE) || (game().getIsJoystick() && SDL_GameControllerGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_A))) {
			for (Entity* t : mngr_->getEntities(ecs::_grp_UI)) {
				TextComponent* txt = t->getComponent<TextComponent>();
				speed = Vector2D(0, 3);
			}
		}
		else {
			for (Entity* t : mngr_->getEntities(ecs::_grp_UI)) {
				speed = Vector2D(0, 1);
			}
		}
	}
	else {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE) || (game().getIsJoystick() && SDL_GameControllerGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_START))) {
			GameStateMachine::instance()->resetStack();
		}
	}
}
