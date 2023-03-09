#include "ControlMenuState.h"
#include "../../../utils/checkML.h"
#include "../../GameStateMachine.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../components/Transform.h"
#include "../../../components/Image.h"
#include "../../../components/FramedImage.h"
#include "../../../components/Button.h"
#include "../../../game/Constructors.h"

ControlMenuState::ControlMenuState() : MenuState() {
    Vector2D pos;
    Vector2D size;
    constructors::background(mngr_, &sdlutils().images().at("playbackground"));

    pos = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2);
    size = Vector2D(3 * sdlutils().width() / 5, 4 * sdlutils().height() / 7);
    constructors::image(mngr_, pos, size, &sdlutils().images().at("whitebackground"));
    
    pos = Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 7);
    constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), back);
}

void ControlMenuState::back() {
	GameStateMachine::instance()->popState();
}


