#include "LoreTextAnims.h"
#include "../sdlutils/InputHandler.h"
#include "../game/Game.h"

LoreTextAnims::LoreTextAnims(std::string id, anims::Entities e, Entity* e1):ID_(id) {
	eAnims = e;
	image = e1->getComponent<FramedImage>();
}

void LoreTextAnims::update() {
	auto input = InputHandler::instance();
	if(end) mngr_->getPlayer()->getComponent<PhysicsComponent>()->Resume();
	if (startAnimation) {
		timer_++;
		if (closeText) {
			if (row == ANIMROWS -1) {
				if (col < ANIMCOLS) {
					open();
					++col;
				}
				else if(col == ANIMCOLS) {
					end = true;
					startAnimation = false;
					startInput = false;
				}
			}
			else row = (timer_ / getTPerFrame()) % getNFrames()+1;
		}
		else if (openText) {
			if (row == 1) {
				startAnimation = false;
				startInput = true;
			}
			else {
				row = (ANIMROWS -1) - (timer_ / getTPerFrame()) % getNFrames();
			}
		}
		image->setCol(col); image->setRow(row);
		
	}
	if (startInput) {
		if (input->keyDownEvent() || game().getIsJoystick()) {
			close();
			startInput = false;
			startAnimation = true;
		}
	}
	

}