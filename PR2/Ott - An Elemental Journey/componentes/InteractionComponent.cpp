#include "InteractionComponent.h"

InteractionComponent::InteractionComponent(void (*callback)(Manager* m)) : m_callback(callback)
{
}

void InteractionComponent::interact()
{
	m_callback(mngr_);
}



InteractionComponent::~InteractionComponent()
{
}
