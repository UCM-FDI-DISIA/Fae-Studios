#include "Transform.h"
#include "../Src/Entity.h"
Transform::Transform()
{
}

Transform::Transform(Vector2D pos, float w, float h) : position_(pos), width_(w), height_(h)
{
	
}

Transform::Transform(float x, float y, float w, float h) : position_(Vector2D(x,y)), width_(w), height_(h)
{
}

Transform::Transform(const Vector2D& position, Texture* texture, const Vector2D& scale) : position_(position)
{
	width_ = texture->getW() / texture->getNumCols() * scale.getX();
	height_ = texture->getH() / texture->getNumRows() * scale.getY();
}


void Transform::initComponent()
{
}

void Transform::update()
{
	if (ent_->hasComponent<PhysicsComponent>()) {

		Vector2D vel = ent_->getComponent<PhysicsComponent>()->getVelocity();
		position_ = position_ + vel;
	}
}

void Transform::render()
{
}

Transform::~Transform()
{

}
