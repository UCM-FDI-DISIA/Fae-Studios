#include "InteractionComponent.h"

InteractionComponent::InteractionComponent(void (*callback)()) : m_callback(callback)
{
}



void InteractionComponent::interact()
{
	m_callback();
}



InteractionComponent::~InteractionComponent()
{
}
