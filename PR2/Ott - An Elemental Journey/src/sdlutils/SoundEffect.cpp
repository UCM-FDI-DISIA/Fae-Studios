// This file is part of the course TPV2@UCM - Samir Genaim

#include "SoundEffect.h"
#include "../game/ecs.h"

int SoundEffect::channels_ = 0;

std::unordered_map<int, int> SoundEffect::volumesOfChannels = { {ecs::_channel_UI, SDL_MIX_MAXVOLUME} };
