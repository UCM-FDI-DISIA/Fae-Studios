#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/Button.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/TextComponent.h"
#include "../components/Slider.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h";
#include "../components/PhysicsComponent.h";
#include "../components/CameraComponent.h";
#include "../components/PlayerInput.h";
#include "../components/MapComponent.h"
#include "../game/Elements.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"
#include "../components/LampComponent.h"
#include "../components/InteractionComponent.h"
#include "../components/AddVine.h"
#include <string>
#include <iostream>


const SDL_Color transparente{ 255,255,255,1 };
const SDL_Color blanco{ 255,255,255 };

namespace constructors {

	static inline void button(Manager* mngr_, Vector2D& position, std::string text, Font& f, Callback* callback) {
		auto b = mngr_->addEntity(ecs::_grp_UI);
		b->addComponent<Transform>(position, 50, 50);
		b->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
		b->addComponent<TextComponent>(text, f, blanco, transparente);
		b->addComponent<Button>(callback);
		b->getComponent<Transform>()->setWidth(b->getComponent<FramedImage>()->getFrameWidth());
		b->getComponent<Transform>()->setHeight(b->getComponent<FramedImage>()->getFrameHeight());
		b->getComponent<Transform>()->setPosition(b->getComponent<Transform>()->getPosition() - Vector2D(b->getComponent<FramedImage>()->getFrameWidth() / 2, b->getComponent<FramedImage>()->getFrameHeight() / 2));
	}

	static inline void exitButton(Manager* mngr_, Vector2D& position, Callback* callback) {
		auto quitButton = mngr_->addEntity(ecs::_grp_UI);
		quitButton->addComponent<Transform>(position, 50, 50);
		quitButton->addComponent<FramedImage>(&sdlutils().images().at("quitbutton"), 1, 3);
		quitButton->addComponent<TextComponent>("X", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
		quitButton->addComponent<Button>(callback);
		quitButton->getComponent<Transform>()->setWidth(quitButton->getComponent<FramedImage>()->getFrameWidth());
		quitButton->getComponent<Transform>()->setHeight(quitButton->getComponent<FramedImage>()->getFrameHeight());
		quitButton->getComponent<Transform>()->setPosition(quitButton->getComponent<Transform>()->getPosition() - Vector2D(quitButton->getComponent<FramedImage>()->getFrameWidth() / 2, quitButton->getComponent<FramedImage>()->getFrameHeight() / 2));
	}

	static inline void slider(Manager* mngr_, Vector2D& position, std::string title, float minValue, float maxValue, float currentValue, SliderCallback* callback) {
		auto s = mngr_->addEntity(ecs::_grp_UI);
		s->addComponent<Transform>(position, 50, 50);
		s->addComponent<FramedImage>(&sdlutils().images().at("slider"), 3, 1);
		s->getComponent<Transform>()->setWidth(s->getComponent<FramedImage>()->getFrameWidth());
		s->getComponent<Transform>()->setHeight(s->getComponent<FramedImage>()->getFrameHeight());
		s->getComponent<Transform>()->setPosition(s->getComponent<Transform>()->getPosition() - Vector2D(s->getComponent<FramedImage>()->getFrameWidth() / 2, s->getComponent<FramedImage>()->getFrameHeight() / 2));
		s->addComponent<TextComponent>(title, sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
		std::string valueText = std::to_string((int)std::ceil(currentValue)) + "%";
		s->addComponent<SliderPercentage>(valueText, sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
		s->addComponent<Slider>(maxValue, minValue, currentValue, callback);

		auto needle = mngr_->addEntity(ecs::_grp_UI);
		needle->addComponent<Transform>(Vector2D(0, 0), 50, 50);
		needle->addComponent<FramedImage>(&sdlutils().images().at("needle"), 1, 3);
		needle->getComponent<Transform>()->setWidth(needle->getComponent<FramedImage>()->getFrameWidth() / 2.5f);
		needle->getComponent<Transform>()->setHeight(needle->getComponent<FramedImage>()->getFrameHeight() / 2.5f);
		needle->addComponent<SliderNeedle>();

		s->getComponent<Slider>()->setNeedle(needle);
	}

	static inline void background(Manager* mngr_, Texture* t) {
		auto b = mngr_->addEntity(ecs::_grp_UI);
		b->addComponent<Transform>(Vector2D(0, 0), sdlutils().width(), sdlutils().height());
		b->addComponent<Image>(t);
	}

	static inline void image(Manager* mngr_, Vector2D& position, Vector2D& size, Texture* t) {
		auto i = mngr_->addEntity(ecs::_grp_UI);
		i->addComponent<Transform>(position, size.getX(), size.getY());
		i->addComponent<Image>(t);
		i->getComponent<Transform>()->setPosition(i->getComponent<Transform>()->getPosition() - Vector2D(i->getComponent<Image>()->getWidth() / 2, i->getComponent<Image>()->getHeight() / 2));
	}

	static inline void normalText(Manager* mngr_, std::string text, Vector2D& position, Font& f, SDL_Color textColor = blanco, SDL_Color bgColor = transparente) {
		auto t = mngr_->addEntity(ecs::_grp_UI);
		t->addComponent<TextComponent>(text, f, textColor, bgColor);
		Vector2D textPos = Vector2D(position.getX() - t->getComponent<TextComponent>()->getWidth() / 2, position.getY());
		t->getComponent<TextComponent>()->setPosition(textPos);
	}

	static inline void boldText(Manager* mngr_, std::string text, Vector2D& position, Font& f, int displacement, SDL_Color textColor = blanco, SDL_Color bgColor = transparente) {
		Vector2D backPos = position - Vector2D(displacement, 0);
		SDL_Color backCol = { textColor.r - 50, textColor.g - 50, textColor.b - 50 };
		normalText(mngr_, text, backPos, f, backCol, bgColor);
		normalText(mngr_, text, position, f, textColor, transparente);
	}

	static inline Entity* player(Manager* mngr_, int x, int y, int w, int h) {
		auto player = mngr_->addEntity(ecs::_grp_CHARACTERS);
		player->addComponent<Transform>(x, y, w, h);
		player->addComponent<PhysicsComponent>();
		player->addComponent<PlayerAnimationComponent>(anims::OTT_ANIM);
		player->addComponent<PlayerInput>();
		player->addComponent<Health>(5, ecs::Light);
		player->addComponent<FramedImageOtt>();

		return player;
	}

	static inline Entity* camera(Manager* mngr_, int x, int y, int w, int h) {
		auto camera = mngr_->addEntity(ecs::_grp_GENERAL);
		camera->addComponent<Transform>(x, y, w, h);
		camera->addComponent<CameraComponent>();

		return camera;
	}

	static inline void grass(Manager* mngr_, Vector2D position, int width = 60, int height = 60) {
		auto grass = mngr_->addEntity(ecs::_grp_INTERACTION);
		grass->addComponent<Transform>(position.getX(), position.getY(), width, height);
		grass->addComponent<Image>(&sdlutils().images().at("grass"));
		grass->addComponent<InteractionComponent>(mngr_->AddEnredadera);
		grass->addComponent<AddVine>(false);
	}

	static inline void lamp(Manager* mngr_, int x1, int y1, int x2, int y2) {
		auto lamp = mngr_->addEntity(ecs::_grp_INTERACTION);
		auto lamp2 = mngr_->addEntity(ecs::_grp_INTERACTION);

		lamp->addComponent<Transform>(x1, y1, 50, 130);
		lamp2->addComponent<Transform>(x2, y2, 50, 130);
		lamp2->addComponent<Image>(&sdlutils().images().at("lamp"));
		lamp2->addComponent<LampComponent>(lamp);
		lamp2->addComponent<InteractionComponent>(mngr_->Teleport);
	}

	static inline void sanctuary(Manager* mngr_, Vector2D position, int width = 100, int height = 130) {
		auto sanc = mngr_->addEntity(ecs::_grp_INTERACTION);
		sanc->addComponent<Transform>(position.getX(), position.getY(), width, height);
		sanc->addComponent<Image>(&sdlutils().images().at("sanctuary"));
		sanc->addComponent<InteractionComponent>(mngr_->Save);
	}

	static inline void map(Manager* mngr_) {
		auto bgrd = mngr_->addEntity(ecs::_grp_MAP);
		auto e = mngr_->addEntity(ecs::_grp_MAP);
		e->addComponent<MapComponent>(LEVEL1);
		auto scale = e->getComponent<MapComponent>()->tileScale();
		//bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), &sdlutils().images().at("level1bg"), scale, scale);
		lamp(mngr_, 550, 1370, 750, 1370);
		//bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), game->getTexture("level1bg", PLAY_STATE), scale, scale);
		grass(mngr_, Vector2D(200, 1450));

		auto a = e->getComponent<MapComponent>()->getObjects();
		for (auto it : a) {
			//unordered_map<string, TP_Lamp*> lamps;
			for (auto ot : it) {
				float x_ = ot.getAABB().left;
				float y_ = ot.getAABB().top;
				float w_ = ot.getAABB().width;
				float h_ = ot.getAABB().height;
				elementsInfo::elements elem;
				std::string path = "";
				if (ot.getName() == "1") { elem = elementsInfo::Earth; path = "earth"; }
				if (ot.getName() == "2") { elem = elementsInfo::Water; path = "water"; }
				if (ot.getName() == "3") { elem = elementsInfo::Fire; path = "fire"; }
				if (ot.getName() == "4") { elem = elementsInfo::Dark; path = "dark"; }
				if (ot.getClass() == "Ground") {
					//Ground* grT = new Ground(Vector2D(x_ * scale, y_ * scale), app->getTexture("pixel", PLAY_STATE), Scale(w_ * scale, h_ * scale));
					//gameObjects.push_back(grT);
					auto e = mngr_->addEntity(ecs::_grp_GROUND);
					//int width = game->getTexture("pixel", PLAY_STATE)->getW() / game->getTexture("pixel", PLAY_STATE)->getNumCols() * (w_*scale);
					//int height = game->getTexture("pixel", PLAY_STATE)->getH() / game->getTexture("pixel", PLAY_STATE)->getNumRows() * (h_*scale);
					std::cout << "Ground detected " << x_ * scale << " " << y_ * scale << std::endl;
					e->addComponent<Transform>(Vector2D(x_ * scale, y_ * scale), &sdlutils().images().at("pixel"), Vector2D(w_ * scale, h_ * scale));
					e->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
				}
				else if (ot.getClass() == "Grass") {

					//Grass* g1 = new Grass(Vector2D(x_ * scale, y_ * scale - app->getTexture("grass", PLAY_STATE)->getH()), app->getTexture("grass", PLAY_STATE), this);
					//gameObjects.push_back(g1);
					grass(mngr_, Vector2D(x_ * scale, y_ * scale - (&sdlutils().images().at("grass"))->height()));
				}
				else if (ot.getClass() == "Lamp") {
					//createLamp(Vector2D(x_ * scale, y_ * scale - game->getTexture("lamp", PLAY_STATE)->getH() * 2));
					/*TP_Lamp* l1 = new TP_Lamp(Vector2D(x_ * scale, y_ * scale - app->getTexture("lamp", PLAY_STATE)->getH() * 2), app->getTexture("lamp", PLAY_STATE), this, Scale(2, 2), LAMP);

					string lampName = ot.getName();
					auto at = lamps.find(lampName);
					if (at != lamps.end()) {
						l1->SetLamp((*at).second);
						(*at).second->SetLamp(l1);
					}
					else {
						lamps.insert({ ot.getName(), l1 });
					}

					gameObjects.push_back(l1);*/
				}
				else if (ot.getClass() == "Sanctuary") {
					sanctuary(mngr_, Vector2D(x_ * scale - (&sdlutils().images().at("sanctuary"))->width() * 1.5, y_ * scale - (&sdlutils().images().at("sanctuary"))->height() * 3.5));
				}
				else if (ot.getClass() == "Ott") {

				}
				else if (ot.getClass() == "Mushroom") {

				}
				else if (ot.getClass() == "Melee") {
				}
				else if (ot.getClass() == "Slime") {

				}
			}
		}

		//bgrd->addComponent<Image>(game->getTexture("level1bg", PLAY_STATE));
		/*currentMap = new Mapa(app, LEVEL1);
		auto scale = currentMap->tileScale();
		gameObjects.push_back(new CollisionObject(Vector2D(0, 300), app->getTexture("level1bg", PLAY_STATE), Scale(scale, scale)));
		gameObjects.push_back(currentMap);

		auto a = currentMap->getObjects();
		for (auto it : a) {
			unordered_map<string, TP_Lamp*> lamps;
			for (auto ot : it) {
				float x_ = ot.getAABB().left;
				float y_ = ot.getAABB().top;
				float w_= ot.getAABB().width;
				float h_ = ot.getAABB().height;
				elementsInfo::elements elem;
				string path = "";
				if (ot.getName() == "1") { elem = elementsInfo::Earth; path = "earth"; }
				if (ot.getName() == "2") { elem = elementsInfo::Water; path = "water";}
				if (ot.getName() == "3") { elem = elementsInfo::Fire; path = "fire";}
				if (ot.getName() == "4") { elem = elementsInfo::Dark; path = "dark";}
				if (ot.getClass() == "Ground") {
					Ground* grT = new Ground(Vector2D(x_ * scale, y_ * scale), app->getTexture("pixel", PLAY_STATE), Scale(w_ * scale, h_ * scale));

					gameObjects.push_back(grT);
				}
				else if (ot.getClass() == "Grass") {
					Grass* g1 = new Grass(Vector2D(x_ *scale, y_ * scale - app->getTexture("grass", PLAY_STATE)->getH()), app->getTexture("grass", PLAY_STATE), this);
					gameObjects.push_back(g1);

				}
				else if (ot.getClass() == "Lamp") {
					TP_Lamp* l1 = new TP_Lamp(Vector2D(x_ * scale, y_ * scale - app->getTexture("lamp", PLAY_STATE)->getH()*2), app->getTexture("lamp", PLAY_STATE), this, Scale(2, 2), LAMP);

					string lampName = ot.getName();
					auto at = lamps.find(lampName);
					if (at != lamps.end()) {
						l1->SetLamp((*at).second);
						(*at).second->SetLamp(l1);
					}
					else {
						lamps.insert({ ot.getName(), l1 });
					}

					gameObjects.push_back(l1);
				}
				else if (ot.getClass() == "Sanctuary") {
					Sanctuary* s1 = new Sanctuary(Vector2D(x_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getW() * 1.5, y_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getH() * 3.5), app->getTexture("sanctuary", PLAY_STATE), Scale(3.5, 3.5));
					gameObjects.push_back(s1);
				}
				else if (ot.getClass() == "Ott") {

				}
				else if (ot.getClass() == "Mushroom") {

				}
				else if (ot.getClass() == "Melee") {
				}
				else if (ot.getClass() == "Slime") {

				}
			}
		}

		//healthBar = new HealthBar(Vector2D(30, 100), app->getTexture("hearts", PLAY_STATE), Scale(10.0f, 10.0f));
		//gameObjects.push_back(healthBar);
		//ChargedAttackBar* bar = new ChargedAttackBar(healthBar->lastHeartPosition() + Vector2D(100, -10), app->getTexture("chargebar", getStateID()), Scale(1.5f, 1.5f));
		//screenDarkener = new ScreenDarkener(app);
		//gameObjects.push_back(screenDarkener);
		camera = { 0,0,WINDOW_WIDTH, WINDOW_HEIGHT };
		*/
	}

	static inline void vine(Manager* mngr_, Vector2D position, int width, int height) {
		auto vine = mngr_->addEntity(ecs::_grp_VINE);
		vine->addComponent<Transform>(position.getX(), position.getY(), width, height);
		vine->addComponent<Image>(&sdlutils().images().at("enredadera"));
	}
}
