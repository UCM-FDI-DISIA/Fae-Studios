#include "ControlMenuState.h"
#include "../../../utils/checkML.h"
#include "../../GameStateMachine.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../components/Transform.h"
#include "../../../components/Image.h"
#include "../../../components/FramedImage.h"
#include "../../../components/Button.h"
#include "../../../game/Constructors.h"
#include "../../../components/FadeTransitionComponent.h"

ControlMenuState::ControlMenuState() : MenuState() {
    Vector2D pos;
    Vector2D size;
    constructors::background(mngr_, &sdlutils().images().at("playbackground"));

    fade = mngr_->addEntity(ecs::_grp_FADEOUT);
    fade->addComponent<FadeTransitionComponent>(true);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 2*sdlutils().getWindowDimensions().getY() / 5);
    size = Vector2D(3 * sdlutils().getWindowDimensions().getX() / 5, 4 * sdlutils().getWindowDimensions().getY() / 7);
    auto img = constructors::image(mngr_, pos, size, &sdlutils().images().at("controls"));
    Vector2D npos = pos - size / 2;
    img->getComponent<Transform>()->setPosition(npos);
    
    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 6 * sdlutils().getWindowDimensions().getY() / 7);
    constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), [this]() {
        sdlutils().soundEffects().at("button_back").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->popState(); });
        fade->getComponent<FadeTransitionComponent>()->revert();
    });

    fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
}

