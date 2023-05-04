#include "FinalCreditsState.h"
#include"../game/Game.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/TextComponent.h"
#include "../components/PhysicsComponent.h"
#include "../components/FramedImage.h"
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
						aux = n->addComponent<TextComponent>("Presiona Start para salir al menu principal", sdlutils().fonts().at("press_start16"), white, transparent);
					else
						aux = n->addComponent<TextComponent>("Presiona Espacio para salir al menu principal", sdlutils().fonts().at("press_start16"), white, transparent);
					Vector2D pos = Vector2D(0, 0);
					aux->setPosition(pos);

					ott = mngr_->addEntity(ecs::_grp_UI);
					ott->addComponent<Transform>(Vector2D(sdlutils().width() / 2 - sdlutils().images().at("ott_dark").getFrameWidth() - 50, 3 * sdlutils().height() / 4 - sdlutils().images().at("ott_dark").height() / 2), 200, 240);
					auto img = ott->addComponent<FramedImage>(&sdlutils().images().at("ott_dark"), 9, 8);
					img->setCol(0); img->setRow(0);
					timer = SDL_GetTicks() + FRAME_RATE;
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

	endText = nullptr;
	ott = nullptr;
	speed = Vector2D(0, 1);
	createNextName();
}

void FinalCreditsState::update()
{
	GameState::update();
	if (names.size() > 0 && lastName->getComponent<TextComponent>()->getPosition().getY() >= sdlutils().height() / 4) {
		createNextName();
	}
	else if (endText == nullptr && names.size() == 0 && lastName->getComponent<TextComponent>()->getPosition().getY() >= sdlutils().height()) {
		endText = mngr_->addEntity(ecs::_grp_UI);
		auto txt = endText->addComponent<TextComponent>("FIN?", sdlutils().fonts().at("press_start16"), white, transparent);
		Vector2D pos = Vector2D((sdlutils().width() / 2) - (txt->getWidth() / 2), -txt->getHeight());
		txt->setPosition(pos);
	}
	if(!end)
		namesManager();
	else {
		if (SDL_GetTicks() >= timer) {
			timer = SDL_GetTicks() + FRAME_RATE;
			ott->getComponent<FramedImage>()->setCol((ott->getComponent<FramedImage>()->getCurrentCol() + 1) % 2);
		}
	}
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
