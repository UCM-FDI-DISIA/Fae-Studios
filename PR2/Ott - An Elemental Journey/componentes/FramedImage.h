#pragma once
#include "Component.h"
#include "../dependencies/Texture.h"
#include "Transform.h"
#include "../Src/Entity.h"
#include "EnemyAnimationController.h"
#include <SDL.h>

class FramedImageOtt : public Component
{
public:
	FramedImageOtt();
	virtual ~FramedImageOtt();
	void initComponent() override;
	void render() override;
	inline int getCurCol() { return col; }
	inline int getCurRow() { return row; }
	inline void setRow(int r) { row = r; }
	inline void setCol(int c) { col = c; }
	void changeElement(ecs::elements newElem);
	inline void shielded(bool b) { isShielded = b; }
	constexpr static cmpId_type id = ecs::_FRAMEDIMAGEOTT;
	inline void setLookingRight(bool l) { lookingRight = l; }
private:
	Transform* tr_;
	Texture* tex_;
	Texture* shieldTex_;
	int numRows_, numCols_;
	int row = 0, col = 0;
	int tPerFrame;
	bool isShielded = false, lookingRight = true;;
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
	inline void setLookingRight(bool l) { lookingRight = l; }
	constexpr static cmpId_type id = ecs::_FRAMEDIMAGEENEMY;
private:
	// MeleeAnimationComponent* pAnim_;
	Transform* tr_;
	Texture* tex_;
	int numRows_, numCols_;
	int row = 0, col = 0;
	int tPerFrame;
	bool isShielded = false, lookingRight = true;
};