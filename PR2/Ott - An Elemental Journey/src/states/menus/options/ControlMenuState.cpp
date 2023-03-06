#include "ControlMenuState.h"
#include "../../../utils/checkML.h"
#include "../../GameStateMachine.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../components/Transform.h"
#include "../../../components/Image.h"
#include "../../../components/Text.h"
#include "../../../components/FramedImage.h"
#include "../../../components/Button.h"

ControlMenuState::ControlMenuState() : MenuState() {
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
        auto controlsImage = mngr_->addEntity(ecs::_grp_UI);
        controlsImage->addComponent<Transform>(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2), Vector2D(0,0), 3 * sdlutils().width() / 5, 4 * sdlutils().height() / 7);
        controlsImage->addComponent<Image>(&sdlutils().images().at("whitebackground"));
        controlsImage->getComponent<Transform>()->setPosition(controlsImage->getComponent<Transform>()->getPosition() - Vector2D(controlsImage->getComponent<Image>()->getWidth() / 2, controlsImage->getComponent<Image>()->getHeight() / 2));
    }
    {
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

void ControlMenuState::back() {
	GameStateMachine::instance()->popState();
}


