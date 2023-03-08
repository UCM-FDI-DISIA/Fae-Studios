#pragma once
#include "Component.h"
#include "../dependencies/Texture.h"
#include "Transform.h"
#include "../Src/Entity.h"
#include "PlayerAnimationComponent.h"
#include "EnemyAnimationController.h"
#include <SDL.h>

class FramedImageOtt : public Component
{
public:
	FramedImageOtt();
	virtual ~FramedImageOtt();
	void initComponent() override;
	void render() override;
	void update() override;
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

class FramedImageEnemy : public Component
{
public:
	FramedImageEnemy(Texture* text);
	virtual ~FramedImageEnemy() {};
	void initComponent() override;
	virtual void render();
	virtual void update();
	inline int getCurCol() { return col; }
	inline int getCurRow() { return row; }
	inline void setRow(int r) { row = r; }
	inline void setCol(int c) { col = c; }
	constexpr static cmpId_type id = ecs::_FRAMEDIMAGE;
private:
	// MeleeAnimationComponent* pAnim_;
	Transform* tr_;
	Texture* tex_;
	EnemyAnimationComponent* eAnim_;
	int numRows_, numCols_;
	int row = 0, col = 0;
	int tPerFrame;
	bool isShielded = false;
};