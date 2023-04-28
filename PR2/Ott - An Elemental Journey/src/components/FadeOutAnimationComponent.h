#pragma once
#include "../ecs/Component.h"
#include "FramedImage.h"
#include "PhysicsComponent.h"
#include "CameraComponent.h"
#include "Transform.h"

class MapComponent;

class FadeOutMapComponent : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_FADEOUTANIM;
	FadeOutMapComponent() = default;
	virtual ~FadeOutMapComponent() = default;
	void initComponent();
	inline void startFadeOut(Vector2D newPos, int newRoom, bool verticalTrigger = false)
	{
		fadeOut = true; playerPs_->Stop(); fadeIn = false; col = 0; newPlayerPos = newPos; 
		newMapRoom = newRoom;
		resumeSpeed = verticalTrigger;
		roomChange = true;
	};
	inline void startFadeOut(int newMapEnum, std::string newMapKey, int newPosIndex)
	{
		fadeOut = true; playerPs_->Stop(); fadeIn = false; col = 0; 
		newMapPlayerPos = newPosIndex;
		this->newMapKey = newMapKey;
		this->newMapEnum = newMapEnum;
		mapChange = true;
		roomChange = false;
	};
	inline void startFadeOut()
	{
		fadeOut = true; fadeIn = false; col = 0;
		roomChange = false;
	};
	virtual void update();
	inline bool onAnim() { return onAnimPlaying; }
	inline void setMap(Entity* map) { map_ = map->getComponent<MapComponent>(); }
private:
	void startFadeIn();
	PhysicsComponent* playerPs_;
	FramedImage* image_;
	CameraComponent* cam_;
	Transform* tr_;
	Vector2D newPlayerPos = {0,0};
	int newMapRoom = 0;
	MapComponent* map_;
	int col = 0;
	const int timeBetweenFrames = 6;
	int timer_ = 0;
	const int MAX_COL = 10;
	bool fadeIn = false, fadeOut = false, onAnimPlaying = false, roomChange = true, mapChange = false;
	bool resumeSpeed = false;

	int newMapPlayerPos, newMapEnum;
	std::string newMapKey;
};