#pragma once
#include "Component.h"
#include "../dependencies/Texture.h"
#include "Transform.h"
#include "../Src/Entity.h"
#include <SDL.h>

class FramedImageOtt : public Component
{
public:
	FramedImageOtt();
	//Constructor exclusivo para Ott 
	virtual ~FramedImageOtt();
	void initComponent() override;
	void render() override;
	void elementChanged(int newElem);
	inline void shielded(bool b) { isShielded = b; }
	constexpr static cmpId_type id = ecs::_FRAMEDIMAGE;
private:
	Transform* tr_;
	Texture* tex_;
	PlayerAnimationComponent* pAnim_;
	Texture* shieldTex_;
	int numRows_, numCols_;
	int row = 0, col = 0;
	int tPerFrame;
	bool isShielded = false;
};

class FramedImageMelee : public Component
{
public:
	FramedImageMelee(Texture* text, int r, int c);
	FramedImageMelee(Texture* text, int r, int c, int f);
	//Constructor exclusivo para Ott 
	FramedImageMelee();
	virtual ~FramedImageMelee();
	void initComponent() override;
	inline void damageStart() { row = 1; };
	inline void damageStop() { row = 0; };
	virtual void render();
	constexpr static cmpId_type id = ecs::_FRAMEDIMAGE;
private:
	// MeleeAnimationComponent* pAnim_;
	Transform* tr_;
	Texture* tex_;
	Texture* shieldTex_;
	int numRows_, numCols_;
	int row = 0, col = 0;
	int tPerFrame;
	bool isShielded = false;
};