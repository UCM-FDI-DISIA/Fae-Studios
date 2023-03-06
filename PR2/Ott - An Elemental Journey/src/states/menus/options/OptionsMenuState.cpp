#include "../../../utils/checkML.h"
#include "OptionsMenuState.h"
#include "../../GameStateMachine.h"
#include "MusicOptionsMenuState.h"
#include "ControlMenuState.h"
#include <iostream>
#include "../../../sdlutils/SDLUtils.h"
#include "../../../components/Transform.h"
#include "../../../components/Image.h"
#include "../../../components/Text.h"
#include "../../../components/FramedImage.h"
#include "../../../components/Button.h"

OptionsMenuState::OptionsMenuState() : MenuState() {
	SDL_Color transparente{ 255,255,255,1 };
	SDL_Color darkYellow{ 194,147,42 };
	SDL_Color yellow{ 255,217,102 };
	SDL_Color blanco{ 255,255,255 };
	Vector2D textPos;
	{
		auto background = mngr_->addEntity(ecs::_grp_UI);
		background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), sdlutils().width(), sdlutils().height());
		background->addComponent<Image>(&sdlutils().images().at("playbackground"));
	}
	{
		{
			auto titleBack = mngr_->addEntity(ecs::_grp_UI);
			titleBack->addComponent<Text>("Opciones", sdlutils().fonts().at("press_start48"), darkYellow, transparente);
			textPos = Vector2D((sdlutils().width() - titleBack->getComponent<Text>()->getWidth()) / 2 - 5, 100);
			titleBack->getComponent<Text>()->setPosition(textPos);
		}
		{
			auto titleFront = mngr_->addEntity(ecs::_grp_UI);
			titleFront->addComponent<Text>("Opciones", sdlutils().fonts().at("press_start48"), yellow, transparente);
			textPos = Vector2D((sdlutils().width() - titleFront->getComponent<Text>()->getWidth()) / 2, 100);
			titleFront->getComponent<Text>()->setPosition(textPos);
		}
	}
	{
		{
			auto graphics = mngr_->addEntity(ecs::_grp_UI);
			graphics->addComponent<Transform>(Vector2D(sdlutils().width() / 2, 3 * sdlutils().height() / 7), Vector2D(0, 0), 50, 50);
			graphics->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
			graphics->addComponent<Text>("Gráficos", sdlutils().fonts().at("vcr_osd24"), blanco, transparente);
			graphics->addComponent<Button>(graphicOptions);
			graphics->getComponent<Transform>()->setWidth(graphics->getComponent<FramedImage>()->getFrameWidth());
			graphics->getComponent<Transform>()->setHeight(graphics->getComponent<FramedImage>()->getFrameHeight());
            graphics->getComponent<Transform>()->setPosition(graphics->getComponent<Transform>()->getPosition() - Vector2D(graphics->getComponent<FramedImage>()->getFrameWidth() / 2, graphics->getComponent<FramedImage>()->getFrameHeight() / 2));
		}
		{
			auto music = mngr_->addEntity(ecs::_grp_UI);
			music->addComponent<Transform>(Vector2D(sdlutils().width() / 2, 4 * sdlutils().height() / 7), Vector2D(0, 0), 50, 50);
			music->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
			music->addComponent<Text>("Música y sonidos", sdlutils().fonts().at("vcr_osd16"), blanco, transparente);
			music->addComponent<Button>(musicOptions);
			music->getComponent<Transform>()->setWidth(music->getComponent<FramedImage>()->getFrameWidth());
			music->getComponent<Transform>()->setHeight(music->getComponent<FramedImage>()->getFrameHeight());
            music->getComponent<Transform>()->setPosition(music->getComponent<Transform>()->getPosition() - Vector2D(music->getComponent<FramedImage>()->getFrameWidth() / 2, music->getComponent<FramedImage>()->getFrameHeight() / 2));
		}
		{
			auto controlsButton = mngr_->addEntity(ecs::_grp_UI);
			controlsButton->addComponent<Transform>(Vector2D(sdlutils().width() / 2, 5 * sdlutils().height() / 7), Vector2D(0, 0), 50, 50);
			controlsButton->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
			controlsButton->addComponent<Text>("Controles", sdlutils().fonts().at("vcr_osd24"), blanco, transparente);
			controlsButton->addComponent<Button>(controls);
			controlsButton->getComponent<Transform>()->setWidth(controlsButton->getComponent<FramedImage>()->getFrameWidth());
			controlsButton->getComponent<Transform>()->setHeight(controlsButton->getComponent<FramedImage>()->getFrameHeight());
            controlsButton->getComponent<Transform>()->setPosition(controlsButton->getComponent<Transform>()->getPosition() - Vector2D(controlsButton->getComponent<FramedImage>()->getFrameWidth() / 2, controlsButton->getComponent<FramedImage>()->getFrameHeight() / 2));
		}
		{
			auto returnBack = mngr_->addEntity(ecs::_grp_UI);
			returnBack->addComponent<Transform>(Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 7), Vector2D(0, 0), 50, 50);
			returnBack->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
			returnBack->addComponent<Text>("Volver", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
			returnBack->addComponent<Button>(back);
			returnBack->getComponent<Transform>()->setWidth(returnBack->getComponent<FramedImage>()->getFrameWidth());
			returnBack->getComponent<Transform>()->setHeight(returnBack->getComponent<FramedImage>()->getFrameHeight());
            returnBack->getComponent<Transform>()->setPosition(returnBack->getComponent<Transform>()->getPosition() - Vector2D(returnBack->getComponent<FramedImage>()->getFrameWidth() / 2, returnBack->getComponent<FramedImage>()->getFrameHeight() / 2));
		}
	}
}

void OptionsMenuState::graphicOptions() {
	std::cout << "opciones graficas" << std::endl;
}

void OptionsMenuState::musicOptions() {
	GameStateMachine::instance()->pushState(new MusicOptionsMenuState());
}

void OptionsMenuState::back() {
	GameStateMachine::instance()->popState();
}

void OptionsMenuState::controls() {
	GameStateMachine::instance()->pushState(new ControlMenuState());
}