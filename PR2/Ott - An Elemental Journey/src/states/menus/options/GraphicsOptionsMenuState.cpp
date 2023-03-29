#include "GraphicsOptionsMenuState.h"
#include "../../../utils/checkML.h"
#include "../../GameStateMachine.h"
#include "../../../game/Constructors.h"
#include "../../../components/FadeTransitionComponent.h"
#include "../../../components/TextComponent.h"

const SDL_Color rojo{ 255,0,0 };
const SDL_Color verde{ 0,255,0 };

GraphicOptionsMenuState::GraphicOptionsMenuState() : MenuState() {
	Vector2D pos;
	std::string txt;
	SDL_Color c;
	constructors::background(mngr_, &sdlutils().images().at("playbackground"));

	fade = mngr_->addEntity(ecs::_grp_FADEOUT);
	fade->addComponent<FadeTransitionComponent>(true);

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 2 * sdlutils().getWindowDimensions().getY() / 7);
	constructors::button(mngr_, pos, "Pantalla completa", sdlutils().fonts().at("vcr_osd16"), [this]() {
		sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
		if (s == SDLUtils::WINDOWED) s = SDLUtils::FULLSCREEN;
		else if (s == SDLUtils::FULLSCREEN) s = SDLUtils::WINDOWED;
		sdlutils().toggleFullScreen(s);
		fwNeedChange = true;
        stateMachine().resChanged();
        changeResolution();
	});

	fsTextPos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 2 * sdlutils().getWindowDimensions().getY() / 7 + 60);
	switch (sdlutils().getCurrentScreenMode()) {
		case (SDLUtils::WINDOWED): txt = "Desactivada"; c = rojo; break;
		case (SDLUtils::FULLSCREEN): txt = "Activada"; c = verde; break;
	}
	fsText = constructors::normalText(mngr_, txt, fsTextPos, sdlutils().fonts().at("vcr_osd24"), c);

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 6 * sdlutils().getWindowDimensions().getY() / 7);
	constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), [this]() {
		sdlutils().soundEffects().at("button_back").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->popState(); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	});

	fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
}

void GraphicOptionsMenuState::update() {
	MenuState::update();
	
	if (fwNeedChange) {
		if (s == SDLUtils::WINDOWED) {
			fsText->getComponent<TextComponent>()->changeText("Desactivada");
			fsText->getComponent<TextComponent>()->changeColor(rojo);
			Vector2D textPos = Vector2D(fsTextPos.getX() - fsText->getComponent<TextComponent>()->getWidth() / 2, fsTextPos.getY());
			fsText->getComponent<TextComponent>()->setPosition(textPos);
		}
		else if (s == SDLUtils::FULLSCREEN) {
			fsText->getComponent<TextComponent>()->changeText("Activada");
			fsText->getComponent<TextComponent>()->changeColor(verde);
			Vector2D textPos = Vector2D(fsTextPos.getX() - fsText->getComponent<TextComponent>()->getWidth() / 2, fsTextPos.getY());
			fsText->getComponent<TextComponent>()->setPosition(textPos);
		}
		fwNeedChange = false;
	}
}

void GraphicOptionsMenuState::changeResolution() {
    for(int i = 0; i < ecs::maxGroupId; ++i) {
        auto ents = mngr_->getEntities(i);
        for(auto e : ents) e->setAlive(false);
    }

    Vector2D pos;
    std::string txt;
    SDL_Color c;
    constructors::background(mngr_, &sdlutils().images().at("playbackground"));

    fade = mngr_->addEntity(ecs::_grp_FADEOUT);
    fade->addComponent<FadeTransitionComponent>(true);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 2 * sdlutils().getWindowDimensions().getY() / 7);
    constructors::button(mngr_, pos, "Pantalla completa", sdlutils().fonts().at("vcr_osd16"), [this]() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        if (s == SDLUtils::WINDOWED) s = SDLUtils::FULLSCREEN;
        else if (s == SDLUtils::FULLSCREEN) s = SDLUtils::WINDOWED;
        sdlutils().toggleFullScreen(s);
        fwNeedChange = true;
    });

    fsTextPos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 2 * sdlutils().getWindowDimensions().getY() / 7 + 60);
    switch (sdlutils().getCurrentScreenMode()) {
        case (SDLUtils::WINDOWED): txt = "Desactivada"; c = rojo; break;
        case (SDLUtils::FULLSCREEN): txt = "Activada"; c = verde; break;
    }
    fsText = constructors::normalText(mngr_, txt, fsTextPos, sdlutils().fonts().at("vcr_osd24"), c);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 6 * sdlutils().getWindowDimensions().getY() / 7);
    constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), [this]() {
        sdlutils().soundEffects().at("button_back").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->popState(); });
        fade->getComponent<FadeTransitionComponent>()->revert();
    });

    fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
}
