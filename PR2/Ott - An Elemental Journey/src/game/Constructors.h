#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/Button.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Text.h"
#include "../components/Slider.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h";


const SDL_Color transparente{ 255,255,255,1 };
const SDL_Color blanco{ 255,255,255 };

namespace constructors {

	static inline void button(Manager* mngr_, Vector2D& position, std::string text, Font& f, Callback* callback) {
        auto b = mngr_->addEntity(ecs::_grp_UI);
        b->addComponent<Transform>(position, Vector2D(0, 0), 50, 50);
        b->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
        b->addComponent<Text>(text, f, blanco, transparente);
        b->addComponent<Button>(callback);
        b->getComponent<Transform>()->setWidth(b->getComponent<FramedImage>()->getFrameWidth());
        b->getComponent<Transform>()->setHeight(b->getComponent<FramedImage>()->getFrameHeight());
        b->getComponent<Transform>()->setPosition(b->getComponent<Transform>()->getPosition() - Vector2D(b->getComponent<FramedImage>()->getFrameWidth() / 2, b->getComponent<FramedImage>()->getFrameHeight() / 2));
	}

	static inline void exitButton(Manager* mngr_, Vector2D& position, Callback* callback) {
		auto quitButton = mngr_->addEntity(ecs::_grp_UI);
		quitButton->addComponent<Transform>(position, Vector2D(0, 0), 50, 50);
		quitButton->addComponent<FramedImage>(&sdlutils().images().at("quitbutton"), 1, 3);
		quitButton->addComponent<Text>("X", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
		quitButton->addComponent<Button>(callback);
		quitButton->getComponent<Transform>()->setWidth(quitButton->getComponent<FramedImage>()->getFrameWidth());
		quitButton->getComponent<Transform>()->setHeight(quitButton->getComponent<FramedImage>()->getFrameHeight());
		quitButton->getComponent<Transform>()->setPosition(quitButton->getComponent<Transform>()->getPosition() - Vector2D(quitButton->getComponent<FramedImage>()->getFrameWidth() / 2, quitButton->getComponent<FramedImage>()->getFrameHeight() / 2));
	}

    static inline void slider(Manager* mngr_, Vector2D& position, std::string title, float minValue, float maxValue, float currentValue, SliderCallback* callback) {
		auto s = mngr_->addEntity(ecs::_grp_UI);
		s->addComponent<Transform>(position, Vector2D(0, 0), 50, 50);
		s->addComponent<FramedImage>(&sdlutils().images().at("slider"), 3, 1);
		s->getComponent<Transform>()->setWidth(s->getComponent<FramedImage>()->getFrameWidth());
		s->getComponent<Transform>()->setHeight(s->getComponent<FramedImage>()->getFrameHeight());
		s->getComponent<Transform>()->setPosition(s->getComponent<Transform>()->getPosition() - Vector2D(s->getComponent<FramedImage>()->getFrameWidth() / 2, s->getComponent<FramedImage>()->getFrameHeight() / 2));
		s->addComponent<Text>(title, sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
		std::string valueText = std::to_string((int)std::ceil(currentValue)) + "%";
		s->addComponent<SliderPercentage>(valueText, sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
		s->addComponent<Slider>(maxValue, minValue, currentValue, callback);

		auto needle = mngr_->addEntity(ecs::_grp_UI);
		needle->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 50, 50);
		needle->addComponent<FramedImage>(&sdlutils().images().at("needle"), 1, 3);
		needle->getComponent<Transform>()->setWidth(needle->getComponent<FramedImage>()->getFrameWidth() / 2.5f);
		needle->getComponent<Transform>()->setHeight(needle->getComponent<FramedImage>()->getFrameHeight() / 2.5f);
		needle->addComponent<SliderNeedle>();

		s->getComponent<Slider>()->setNeedle(needle);
    }

	static inline void background(Manager* mngr_, Texture* t) {
		auto b = mngr_->addEntity(ecs::_grp_UI);
		b->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), sdlutils().width(), sdlutils().height());
		b->addComponent<Image>(t);
	}

	static inline void image(Manager* mngr_, Vector2D& position, Vector2D& size, Texture* t) {
		auto i = mngr_->addEntity(ecs::_grp_UI);
		i->addComponent<Transform>(position, Vector2D(0, 0), size.getX(), size.getY());
		i->addComponent<Image>(t);
		i->getComponent<Transform>()->setPosition(i->getComponent<Transform>()->getPosition() - Vector2D(i->getComponent<Image>()->getWidth() / 2, i->getComponent<Image>()->getHeight() / 2));
	}

	static inline void normalText(Manager* mngr_, std::string text, Vector2D& position, Font& f, SDL_Color textColor = blanco, SDL_Color bgColor = transparente) {
		auto t = mngr_->addEntity(ecs::_grp_UI);
		t->addComponent<Text>(text, f, textColor, bgColor);
		Vector2D textPos = Vector2D(position.getX() - t->getComponent<Text>()->getWidth() / 2, position.getY());
		t->getComponent<Text>()->setPosition(textPos);
	}

	static inline void boldText(Manager* mngr_, std::string text, Vector2D& position, Font& f, int displacement, SDL_Color textColor = blanco, SDL_Color bgColor = transparente) {
		Vector2D backPos = position - Vector2D(displacement,0);
		SDL_Color backCol = { textColor.r - 50, textColor.g - 50, textColor.b - 50 };
		normalText(mngr_, text, backPos, f, backCol, bgColor);
		normalText(mngr_, text, position, f, textColor, transparente);
	}
}

