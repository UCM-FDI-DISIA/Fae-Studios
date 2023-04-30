#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/Button.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/TextComponent.h"
#include "../components/ElementObject.h"
#include "../components/LampAnimationComponent.h"
#include "../components/GrassAnimationComponent.h"
#include "../components/Slider.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h";
#include "../components/PhysicsComponent.h";
#include "../components/CameraComponent.h";
#include "../components/PlayerInput.h";
#include "../components/MapComponent.h"
#include "../game/Elements.h"
#include "../components/Health.h"
#include "../components/LampComponent.h"
#include "../components/InteractionComponent.h"
#include "../components/AddVine.h"
#include "../components/PlayerAttack.h"
#include "../states/PlayState.h"
#include "../components/EnemyAttack.h"
#include "../components/EnemyMovement.h"
#include "../components/EnemyMeleeAttack.h"
#include "../components/EnemyShootingAttack.h"
#include "../components/EnemyAnimationController.h"
#include "../components/LifeAnimationComponent.h"
#include "../components/Generations.h"
#include "../components/SlimeStates.h"
#include "../components/EnterBossRoom.h"
#include "../components/Trigger.h"
#include "../states/GameStateMachine.h"
#include "../components/VineManager.h"
#include "../components/EnemyContactDamage.h"
#include "../components/WaterBossAttack.h"
#include "../states/GameStateMachine.h"
#include "../components/FirePillarComponent.h"
#include "../components/FireBossComponent.h"
#include "../components/Bullet.h"
#include "../components/WaterContainerComponent.h"
#include "../components/WaterVineComponent.h"
#include "../components/FireBossAnimation.h"
#include "../components/AttackCharger.h"
#include "../components/FadeOutAnimationComponent.h"
#include "../components/DamageArea.h"
#include "../components/EarthBossManager.h"
#include "../components/Destruction.h"
#include "../components/Pivot.h"
#include "../components/Acceleration.h"
#include "../components/WaterBossAnimationComponent.h"
#include "../components/ShieldComponent.h"
#include "../components/ChargedAttackBar.h"
#include "../components/GeneralAnimationController.h"
#include "../components/PlatformMovementY.h"
#include "../components/PlatformMovementX.h"
#include "../components/FireBossRoom.h"
#include <string>
#include <iostream>
#include <functional>
#include <cstdlib>s
#include <SDL.h>


const SDL_Color transparente{ 255,255,255,1 };
const SDL_Color blanco{ 255,255,255 };

namespace constructors {
	//static inline Entity* damageArea(Manager* mngr_, std::string imageKey, ecs::elements el, int x, int y, int w, int h)
	//{
	//	auto a = mngr_->addEntity(ecs::_grp_GENERAL); //crear grupo
	//	a->addComponent<Transform>(x, y, w, h);
	//	a->addComponent<Image>(&sdlutils().images().at(imageKey));
	//	a->addComponent<DamageArea>(el);

	//	return a;
	//}
	//static inline Entity* eRanged(Manager* mngr_, std::string imageKey, int x, int y, float scale, ecs::elements el) {
	static inline Entity* eRanged(Manager* mngr_, std::string imageKey, int x, int y, float scale, ecs::elements el, bool lookingRight) {

		// Asi se a�ade enemigo rango
		auto enemy2 = mngr_->addEntity(ecs::_grp_CHARACTERS);
		auto ph2 = enemy2->addComponent<PhysicsComponent>(colliders::RANGE);
		enemy2->addComponent<Transform>(x, y, 110 * scale, 110 * scale); // 1700 1800 pos para pruebas
		ph2->createCollider();
		auto fi = enemy2->addComponent<FramedImage>(&sdlutils().images().at(imageKey), 2, 22);
		fi->flipTexture(!lookingRight);
		enemy2->addComponent<Health>(5, el, false);
		ph2->setVelocity({ 0,0 });
		ph2->lookDirection(lookingRight);
		auto eAttack_2 = enemy2->addComponent<EnemyAttack>(1200, 400);
		auto eAnim_2 = enemy2->addComponent<EnemyAnimationComponent>(anims::RANGE_ANIM);
		auto attack_2 = enemy2->addComponent<EnemyShootingAttack>();
		enemy2->addComponent<EnemyContactDamage>();
		eAttack_2->SetRefs(eAnim_2, attack_2, nullptr);

		return enemy2;
	}

	static inline Entity* eMelee(Manager* mngr_, std::string imageKey, int x, int y, float scale, ecs::elements el, bool lookingRight) {


		// Asi se a�ade enemigo melee

		auto enemy3 = mngr_->addEntity(ecs::_grp_CHARACTERS);
		auto ph3 = enemy3->addComponent<PhysicsComponent>(colliders::MELEE);
		enemy3->addComponent<Transform>(x, y, 230 * scale, 130 * scale);  // 2400 1800 pos para pruebas
		ph3->createCollider();
		auto fi = enemy3->addComponent<FramedImage>(&sdlutils().images().at(imageKey), 2, 21);
		fi->flipTexture(!lookingRight);
		enemy3->addComponent<Health>(5, el, false);
		float dir = 0;
		if (lookingRight) dir = 1;
		else dir = -1;
		ph3->setVelocity({ dir,0 });
		ph3->lookDirection(lookingRight);
		auto eAttack_3 = enemy3->addComponent<EnemyAttack>(1200);
		enemy3->addComponent<EnemyMovement>();
		auto eAnim_3 = enemy3->addComponent<EnemyAnimationComponent>(anims::MELEE_ANIM);
		auto meleeAttack_3 = enemy3->addComponent<EnemyMeleeAttack>();
		enemy3->addComponent<EnemyContactDamage>();
		eAttack_3->SetRefs(eAnim_3, nullptr, meleeAttack_3);

		return enemy3;
	}

	static inline void firePillar(Manager* mngr_, std::string imageKey, int x, int y, float scale) {
		// Asi se a�ade pilar de fuego
		auto pilar = mngr_->addEntity(ecs::_grp_VINE);
		pilar->addComponent<Transform>(x, y, 200 * scale, 80 * scale, 90);  // 2400 1800 pos para pruebas
		pilar->addComponent<FramedImage>(&sdlutils().images().at(imageKey), 1, 60);
		pilar->addComponent<FirePillarComponent>();
		
	}
	static inline void bullet(Manager* mngr_, std::string imageKey, int x, int y, int dim, Vector2D dir, Entity* instigator, ecs::elements elem, float scale) {
		auto attack = mngr_->addEntity(ecs::_grp_PROYECTILES);
		Vector2D shootPos = Vector2D(x, y);
		attack->addComponent<PhysicsComponent>(dir);
		attack->addComponent<Transform>(shootPos, dim * scale, dim * scale);
		attack->addComponent<Image>(&sdlutils().images().at(imageKey));
		attack->addComponent<Bullet>(elem, instigator);
	}


	static inline Entity* eSlime(Manager* mngr_, std::string imageKey, int x, int y, float scale, ecs::elements el, bool lookingRight, int room) {

		// Asi se a�ade enemigo slime

		auto enemy = mngr_->addEntity(ecs::_grp_CHARACTERS);
		auto ph = enemy->addComponent<PhysicsComponent>(colliders::SLIME);
		auto tr = enemy->addComponent<Transform>(Vector2D(x, y), 360 * scale, 210 * scale); // 600 950 pos para pruebas
		ph->createCollider();
		auto fi = enemy->addComponent<FramedImage>(&sdlutils().images().at(imageKey), 2, 21);
		fi->flipTexture(!lookingRight);
		enemy->addComponent<Health>(5, el, false);
		float dir = 0;
		if (lookingRight) dir = 1;
		else dir = -1;
		ph->setVelocity({ dir,0 });
		ph->lookDirection(lookingRight);
		auto eAttack_ = enemy->addComponent<EnemyAttack>(1200);
		enemy->addComponent<EnemyMovement>();
		auto eAnim_ = enemy->addComponent<EnemyAnimationComponent>(anims::SLIME_ANIM);
		auto meleeAttack_ = enemy->addComponent<EnemyMeleeAttack>();
		enemy->addComponent<Generations>(Generations::getMaxGeneration(), room);
		enemy->addComponent<SlimeStates>();
		enemy->addComponent<EnemyContactDamage>();
		eAttack_->SetRefs(eAnim_, nullptr, meleeAttack_);

		return enemy;
	}
	static inline pair<Entity*, Entity*> waterContainer(Manager* mngr_, int x, int y,int w, int h, float scale) {
		auto waterC = mngr_->addEntity(ecs::_grp_MAP);
		waterC->addComponent<Transform>(Vector2D(x,y), w, h);
		waterC->addComponent<Image>(&sdlutils().images().at("water"));
		waterC->addComponent<WaterContainerComponent>();

		auto waterVine = mngr_->addEntity(ecs::_grp_MAP);
		waterVine->addComponent<Transform>(Vector2D(0, 0), 30 * scale, 300 * scale);
		waterVine->addComponent<Image>(&sdlutils().images().at("enredadera"));
		waterVine->addComponent<WaterVineComponent>(waterC);

		return { waterC, waterVine };
	}
	static inline Entity* fireBossRoom(Manager* mngr_, int x, int y, int w, int h) {
		auto triggerBoss = mngr_->addEntity(ecs::_grp_MAP);
		triggerBoss->addComponent<Transform>(Vector2D(x, y), w, h);
		triggerBoss->addComponent<FireBossRoom>();
		return triggerBoss;
	}

	static inline Entity* eSlime(Manager* mngr_, Texture* tex, int x, int y, float scale, int gens, int lives, ecs::elements el, bool lookingRight, int room) {
		// Asi se a�ade enemigo slime

		auto enemy = mngr_->addEntity(ecs::_grp_CHARACTERS);
		auto ph = enemy->addComponent<PhysicsComponent>(colliders::SLIME);
		auto tr = enemy->addComponent<Transform>(Vector2D(x, y), 360 * scale, 210 * scale); // 600 950 pos para pruebas
		ph->createCollider();
		auto fi = enemy->addComponent<FramedImage>(tex, 2, 21);
		fi->flipTexture(!lookingRight);
		enemy->addComponent<Health>(lives, el, false);
		float dir = 0;
		if (lookingRight) dir = 1;
		else dir = -1;
		ph->setVelocity({ dir,0 });
		ph->lookDirection(lookingRight);
		auto eAttack_ = enemy->addComponent<EnemyAttack>(1200);
		enemy->addComponent<EnemyMovement>();
		auto eAnim_ = enemy->addComponent<EnemyAnimationComponent>(anims::SLIME_ANIM);
		auto meleeAttack_ = enemy->addComponent<EnemyMeleeAttack>();
		enemy->addComponent<Generations>(gens, room);
		enemy->addComponent<SlimeStates>();
		enemy->addComponent<EnemyContactDamage>();
		eAttack_->SetRefs(eAnim_, nullptr, meleeAttack_);

		return enemy;
	}

	static inline auto button(Manager* mngr_, Vector2D& position, std::string text, Font& f, std::function<void()> const& callback) {
		auto b = mngr_->addEntity(ecs::_grp_UI);
		b->addComponent<Transform>(position, 50, 50);
		b->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
		b->addComponent<TextComponent>(text, f, blanco, transparente);
		b->addComponent<Button>(callback);
		b->getComponent<Transform>()->setWidth(b->getComponent<FramedImage>()->getFrameWidth());
		b->getComponent<Transform>()->setHeight(b->getComponent<FramedImage>()->getFrameHeight());
		b->getComponent<Transform>()->setPosition(b->getComponent<Transform>()->getPosition() - Vector2D(b->getComponent<FramedImage>()->getFrameWidth() / 2, b->getComponent<FramedImage>()->getFrameHeight() / 2));
		
		if (game().getIsJoystick()) {
			auto ned = mngr_->addEntity(ecs::_grp_UI);
			ned->addComponent<Transform>(Vector2D(0,0), 50, 50);
			ned->addComponent<Image>(&sdlutils().images().at("button_needle"));
			ned->getComponent<Transform>()->setWidth(ned->getComponent<Image>()->getWidth() / 2.5f);
			ned->getComponent<Transform>()->setHeight(ned->getComponent<Image>()->getHeight() / 2.5f);
			ned->addComponent<ButtonNeedle>();
			b->getComponent<Button>()->setNeedle(ned);
		}
		
		return b;
	}

	static inline auto exitButton(Manager* mngr_, Vector2D& position, std::function<void()> const& callback) {
		auto quitButton = mngr_->addEntity(ecs::_grp_UI);
		quitButton->addComponent<Transform>(position, 50, 50);
		quitButton->addComponent<FramedImage>(&sdlutils().images().at("quitbutton"), 1, 3);
		quitButton->addComponent<TextComponent>("X", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
		quitButton->addComponent<Button>(callback);
		quitButton->getComponent<Transform>()->setWidth(quitButton->getComponent<FramedImage>()->getFrameWidth());
		quitButton->getComponent<Transform>()->setHeight(quitButton->getComponent<FramedImage>()->getFrameHeight());
		quitButton->getComponent<Transform>()->setPosition(quitButton->getComponent<Transform>()->getPosition() - Vector2D(quitButton->getComponent<FramedImage>()->getFrameWidth() / 2, quitButton->getComponent<FramedImage>()->getFrameHeight() / 2));
		
		if (game().getIsJoystick()) {
			auto ned = mngr_->addEntity(ecs::_grp_UI);
			ned->addComponent<Transform>(Vector2D(0, 0), 50, 50);
			ned->addComponent<Image>(&sdlutils().images().at("button_needle"));
			ned->getComponent<Transform>()->setWidth(ned->getComponent<Image>()->getWidth() / 2.5f);
			ned->getComponent<Transform>()->setHeight(ned->getComponent<Image>()->getHeight() / 2.5f);
			ned->addComponent<ButtonNeedle>();
			quitButton->getComponent<Button>()->setNeedle(ned);
		}
		
		return quitButton;
	}
	

	static inline void slider(Manager* mngr_, Vector2D& position, std::string title, float minValue, float maxValue, float currentValue, std::function<void(int)> const& callback) {
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

	static inline auto background(Manager* mngr_, Texture* t) {
		auto b = mngr_->addEntity(ecs::_grp_UI);
		b->addComponent<Transform>(Vector2D(0, 0), sdlutils().getWindowDimensions().getX(), sdlutils().getWindowDimensions().getY());
		b->addComponent<Image>(t);
		return b;
	}

	static inline auto image(Manager* mngr_, Vector2D& position, Vector2D& size, Texture* t) {
		auto i = mngr_->addEntity(ecs::_grp_UI);
		i->addComponent<Transform>(position, size.getX(), size.getY());
		i->addComponent<Image>(t);
		i->getComponent<Transform>()->setPosition(i->getComponent<Transform>()->getPosition() - Vector2D(i->getComponent<Image>()->getWidth() / 2, i->getComponent<Image>()->getHeight() / 2));
		return i;
	}

	static inline auto normalText(Manager* mngr_, std::string text, Vector2D& position, Font& f, SDL_Color textColor = blanco, SDL_Color bgColor = transparente) {
		auto t = mngr_->addEntity(ecs::_grp_UI);
		t->addComponent<TextComponent>(text, f, textColor, bgColor);
		Vector2D textPos = Vector2D(position.getX() - t->getComponent<TextComponent>()->getWidth() / 2, position.getY());
		t->getComponent<TextComponent>()->setPosition(textPos);
		return t;
	}

	static inline void boldText(Manager* mngr_, std::string text, Vector2D& position, Font& f, int displacement, SDL_Color textColor = blanco, SDL_Color bgColor = transparente) {
		Vector2D backPos = position - Vector2D(displacement, 0);
		SDL_Color backCol = { (Uint8)(textColor.r - 50), (Uint8)(textColor.g - 50), (Uint8)(textColor.b - 50) };
		normalText(mngr_, text, backPos, f, backCol, bgColor);
		normalText(mngr_, text, position, f, textColor, transparente);
	}
		
	static inline Entity* player(Manager* mngr_, int x, int y, int w, int h) {

		auto healthUI = mngr_->addEntity(ecs::_grp_UI);
		auto lamp_w = 150;
		SDL_Rect rect = { 20,20,(int)(0.56*lamp_w),lamp_w };
		auto healthImage = healthUI->addComponent<HealthImage>(&sdlutils().images().at("lamps"), 5, rect);

		auto player = mngr_->addEntity(ecs::_grp_CHARACTERS);
		auto ph = player->addComponent<PhysicsComponent>(colliders::OTT);
		player->addComponent<Transform>(Vector2D(x, y), w, h);
		player->addComponent<HealthImage>(&sdlutils().images().at("lamps"), 5, rect);
		player->addComponent<FramedImageOtt>(&sdlutils().images().at("ott_luz"));
		player->addComponent<ChargedAttackBar>(&sdlutils().images().at("chargebar"));
		auto pAnim = player->addComponent<PlayerAnimationComponent>(anims::OTT_ANIM);
		auto health = player->addComponent<Health>(5, ecs::Light, healthImage);
		player->addComponent<PlayerAttack>();
		player->addComponent<AttackCharger>(8);
		player->addComponent<PlayerInput>();
		player->addComponent<ShieldComponent>();
		pAnim->initComponent();
		health->initComponent();
		ph->createCollider();	
		return player;
	}

	static inline Entity* camera(Manager* mngr_, int x, int y, int w, int h) {
		auto camera = mngr_->addEntity(ecs::_grp_GENERAL);
		camera->addComponent<Transform>(Vector2D(x, y), w, h);
		camera->addComponent<CameraComponent>();

		return camera;
	}

	static inline Entity* grass(Manager* mngr_, Vector2D position, int widthVine, int heightVine, Vector2D posiniVine, Vector2D posfinVine, int ID, int room, int width = 60, int height = 60) {
		auto grass = mngr_->addEntity(ecs::_grp_INTERACTION);
		grass->addComponent<Transform>(position, width, height);
		grass->addComponent<FramedImage>(&sdlutils().images().at("grass"), 1, 4);
		grass->addComponent<VineManager>(NORMAL, posiniVine, posfinVine, -1, 0, widthVine, heightVine, 2);
		grass->getComponent<VineManager>()->createVine();
		auto cb = []() {
			static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->AddEnredadera();
		};
		grass->addComponent<InteractionComponent>(cb, GRASS_IT, ID, room);
		grass->addComponent<GrassAnimationComponent>();
		return grass;
	}

	static inline Entity* LifeShard(Manager* mngr_, int x, int y, int w, int h, int ID, int room) {
		auto shard = mngr_->addEntity(ecs::_grp_INTERACTION);
		shard->addComponent<Transform>(Vector2D(x, y), w, h);
		shard->addComponent<FramedImage>(&sdlutils().images().at("lifeshard"), 1, 10);
		shard->addComponent<LifeAnimationComponent>();
		auto cb = [ID]() {
			static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->AddLifeShard(ID);
		};
		shard->addComponent<InteractionComponent>(cb, LIFESHARD_IT, ID, room, true);

		return shard;
	}

	static inline Entity* ElementEntity(Manager* mngr_, int x, int y, int w, int h, ecs::elements elem, int room) {
		auto element = mngr_->addEntity(ecs::_grp_INTERACTION);
		element->addComponent<Transform>(Vector2D(x, y), w, h);
		std::string key;
		switch (elem) {
		case ecs::Earth:
			key = "earth_elem";
			break;
		case ecs::Water:
			key = "water_elem";
			break;
		case ecs::Fire:
			key = "fire_elem";
			break;
		}
		element->addComponent<FramedImage>(&sdlutils().images().at(key), 1, 10);
		element->addComponent<LifeAnimationComponent>();
		element->addComponent<ElementObject>(elem);
		auto cb = [elem]() {
			static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->UnlockElement(elem);
		};
		element->addComponent<InteractionComponent>(cb, ELEMENT_IT, elem, room, true);

		return element;
	}


	static inline std::pair<Entity*, Entity*> lamp(Manager* mngr_, int x1, int y1, int w1, int h1, int room1, int x2, int y2, int w2, int h2, int room2, int ID1, int ID2) {
		auto lamp = mngr_->addEntity(ecs::_grp_INTERACTION);
		auto lamp2 = mngr_->addEntity(ecs::_grp_INTERACTION);

		Texture* t_ = &sdlutils().images().at("lamp");
		lamp->addComponent<Transform>(Vector2D(x1, y1 - h1), w1, h1);
		lamp->addComponent<FramedImage>(t_, 1, 5);
		lamp->addComponent<LampComponent>(lamp2, room1);
		auto cb = []() {
			static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->Teleport();
		};

		lamp->addComponent<InteractionComponent>(cb, LAMP_IT, ID1, room1);
		lamp->addComponent<LampAnimationComponent>();

		lamp2->addComponent<Transform>(Vector2D(x2, y2 - h2), w2, h2);
		lamp2->addComponent<FramedImage>(t_, 1, 5);
		lamp2->addComponent<LampComponent>(lamp, room2);
		lamp2->addComponent<InteractionComponent>(cb, LAMP_IT, ID2, room2);
		lamp2->addComponent<LampAnimationComponent>();
		return std::make_pair(lamp, lamp2);
	}

	static inline Entity* sanctuary(Manager* mngr_, Vector2D position, int ID, int room, int width = 100, int height = 130) {

		auto sanc = mngr_->addEntity(ecs::_grp_INTERACTION);
		sanc->addComponent<Transform>(position, width, height);
		sanc->addComponent<Image>(&sdlutils().images().at("sanctuaryOff"));
		auto cb = []() {
			static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->Save();

		};
		sanc->addComponent<InteractionComponent>(cb, SANCTUARY_IT, ID, room);
		return sanc;
	}
	static inline Entity* FireBoss(Manager* mngr_, int x, int y) {
		auto boss = mngr_->addEntity(ecs::_grp_CHARACTERS);
		boss->addComponent<Transform>(Vector2D(x, y),400, 400);
		boss->addComponent<FireBossComponent>();
		boss->addComponent<PhysicsComponent>(colliders::OTT);
		boss->getComponent<PhysicsComponent>()->createCollider();
		boss->addComponent<FramedImage>(&sdlutils().images().at("fireBoss"), 5, 13);
		
		auto anim=boss->addComponent<FireBossAnimation>(anims::FIREBOSS_ANIM);
		boss->getComponent<FireBossComponent>()->setAnimComponent(anim);
		boss->addComponent<Health>(25, ecs::Fire, false);
		return boss;
	}

	static inline Entity* DestructibleTile(Manager* mngr_, int x, int y, int w, int h, std::string room, int index, MapComponent* map) {
		auto waterObj = mngr_->addEntity(ecs::_grp_GROUND);
		waterObj->addComponent<Transform>(Vector2D(x,y), w, h);
		waterObj->addComponent<Image>(&sdlutils().images().at("box"));
		waterObj->addComponent<Destruction>(room, index, map);
		return waterObj;
	}

	static inline Entity* WaterBoss(Manager* mngr_, int x, int y, int w, int h) {
		auto waterBoss = mngr_->addEntity(ecs::_grp_CHARACTERS);
		auto WbTransform = waterBoss->addComponent<Transform>(x, y, w, h);
		auto waterPh = waterBoss->addComponent<PhysicsComponent>(colliders::WATERBOSS);
		waterPh->setGravity(false);
		waterPh->lookDirection(false);
		waterPh->createCollider();
		waterBoss->addComponent<FramedImage>(&sdlutils().images().at("water_boss"), 4, 8);
		waterBoss->addComponent<Acceleration>();
		waterBoss->addComponent<Health>(6, ecs::Dark, false);
		waterBoss->addComponent<WaterBossAnimationComponent>(anims::WATERBOSS_ANIM);
		waterBoss->addComponent<WaterBossAttack>();
		waterBoss->reinitCmpts();

		//CAMBIAR A QUE SE LEA DE MAPA CUANDO FUNCIONE TODO

		auto box0 = mngr_->addEntity(ecs::_grp_GENERAL);
		x += 3000;
		box0->addComponent<Transform>(x, y + 100, 100, 100);
		//box0->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
		box0->addComponent<Pivot>(waterBoss, 0);

		box0 = mngr_->addEntity(ecs::_grp_GENERAL);
		y += 2000;
		box0->addComponent<Transform>(x, y, 100, 100);
		//box0->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
		box0->addComponent<Pivot>(waterBoss, 1);

		box0 = mngr_->addEntity(ecs::_grp_GENERAL);
		x += 1600;
		box0->addComponent<Transform>(x, y, 100, 100);
		//box0->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
		box0->addComponent<Pivot>(waterBoss, 2);

		box0 = mngr_->addEntity(ecs::_grp_GENERAL);
		y -= 1600;
		box0->addComponent<Transform>(x, y, 100, 100);
		//box0->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
		box0->addComponent<Pivot>(waterBoss, 1);

		box0 = mngr_->addEntity(ecs::_grp_GENERAL);
		x += 1000;
		box0->addComponent<Transform>(x, y, 100, 100);
		//box0->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
		box0->addComponent<Pivot>(waterBoss, 3);

		box0 = mngr_->addEntity(ecs::_grp_GENERAL);
		y -= 550;
		box0->addComponent<Transform>(x, y, 100, 100);
		//box0->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
		box0->addComponent<Pivot>(waterBoss, 4);

		return waterBoss;
	}

	static inline Entity* map(Manager* mngr_, PlayState* game, int currentMap) {
		// auto bgrd = mngr_->addEntity(ecs::_grp_MAP);
		auto e = mngr_->addEntity(ecs::_grp_MAP);
		auto fadeOut = mngr_->addEntity(ecs::_grp_FADEOUT);
		fadeOut->addComponent<Transform>(0, 0, sdlutils().width() * 1.5, sdlutils().height() * 1.5);
		fadeOut->addComponent<FramedImage>(&sdlutils().images().at("fadeOut"), 5, 5);
		fadeOut->addComponent<FadeOutMapComponent>();
		fadeOut->setActive(true);
		e->addComponent<MapComponent>(fadeOut, game, currentMap);
		auto scale = e->getComponent<MapComponent>()->tileScale();
		//bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), &sdlutils().images().at("level1bg"), scale, scale);
		//bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), game->getTexture("level1bg", PLAY_STATE), scale, scale);
		auto a = e->getComponent<MapComponent>()->getObjects();
		return e;
		//bgrd->addComponent<Image>(game->getTexture("level1bg", PLAY_STATE));
	}

	static inline Entity* map(Manager* mngr_, PlayState* game, int level, std::ifstream& fileName) {
		// auto bgrd = mngr_->addEntity(ecs::_grp_MAP);
		auto e = mngr_->addEntity(ecs::_grp_MAP);
		auto fadeOut = mngr_->addEntity(ecs::_grp_FADEOUT);
		fadeOut->addComponent<Transform>(0,0,sdlutils().width()*1.5, sdlutils().height()*1.5);
		fadeOut->addComponent<FramedImage>(&sdlutils().images().at("fadeOut"), 5, 5);
		fadeOut->addComponent<FadeOutMapComponent>();
		fadeOut->setActive(true);
		e->addComponent<MapComponent>(fadeOut, game, level, fileName);
		auto scale = e->getComponent<MapComponent>()->tileScale();
		//bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), &sdlutils().images().at("level1bg"), scale, scale);
		//bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), game->getTexture("level1bg", PLAY_STATE), scale, scale);
		auto a = e->getComponent<MapComponent>()->getObjects();
		return e;
		//bgrd->addComponent<Image>(game->getTexture("level1bg", PLAY_STATE));
	}

	static inline Entity* Water(Manager* mngr_, int x, int y, int w, int h, std::string clase)
	{
		Entity* wObject = mngr_->addEntity(ecs::_grp_WATER);
		wObject->addComponent<Transform>(x, y, w, h);
		wObject->addComponent<Image>(&sdlutils().images().at("water"));
		bool active = (clase == "Activo");
		wObject->addComponent<ActiveWater>(active);

		return wObject;
	}

	static inline Entity* Platform(Manager* mngr_, int x, int y, int w, int h, int a, int t, std::string axis, float room) 
	{
		Entity* pObject = mngr_->addEntity(ecs::_grp_MOVING_PLATFORMS);
		auto ph = pObject->addComponent<PhysicsComponent>(false);
		pObject->addComponent<Transform>(x, y, w, h);
		pObject->addComponent<Image>(&sdlutils().images().at("platform"));
		ph->setGravity(false);
		if (axis == "X")
			pObject->addComponent<PlatformMovementX>(a, t);
		else
			pObject->addComponent<PlatformMovementY>(a, t, room);

		return pObject;
	}
	/*static inline void vine(Manager* mngr_, Vector2D position, int width, int height, Texture* t) {
		auto vine = mngr_->addEntity(ecs::_grp_VINE);
		vine->addComponent<Transform>(position.getX(), position.getY(), width, height);
		vine->addComponent<Image>(&sdlutils().images().at("enredadera"));
	}*/

	static inline Entity* Cartel(Manager* mngr_, int x, int y, int w, int h, std::string numCartel) {
		Entity* cartelObject = mngr_->addEntity(ecs::_grp_CARTEL);
		cartelObject->addComponent<Transform>(x, y, w, h);
		int row = sdlutils().images().at(numCartel).getNumRows(), col = sdlutils().images().at(numCartel).getNumCols();
		anims::Entities type;
		if (numCartel == "movimientoCartel") {
			type = anims::CARTELMOVIMIENTO;
		}
		else if (numCartel == "lamparaCartel") {
			type = anims::CARTELLAMPARA;
		}
		else if (numCartel == "enredaderaCartel") {
			type = anims::CARTELENREDADERA;
		}
		else if (numCartel == "elementoCartel") {
			type = anims::CARTELELEMENTO;
		}
		cartelObject->addComponent<FramedImage>(&sdlutils().images().at(numCartel), row, col);
			//cartelObject->addComponent< GeneralAnimationController>(type,cartelObject);
		return cartelObject;
	}
}

