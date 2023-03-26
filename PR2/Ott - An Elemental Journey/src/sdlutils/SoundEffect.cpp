// This file is part of the course TPV2@UCM - Samir Genaim

#include "SoundEffect.h"
#include "../game/ecs.h"

int SoundEffect::channels_ = 0;
int SoundEffect::generalSoundsVolume = SDL_MIX_MAXVOLUME;

std::unordered_map<int, int> SoundEffect::volumesOfChannels = { 
	{ecs::_channel_UI, SDL_MIX_MAXVOLUME}, 
	{ecs::_channel_PLAYER_ATTACK, SDL_MIX_MAXVOLUME},
	{ecs::_channel_PLAYER_MOVEMENT, SDL_MIX_MAXVOLUME},
	{ecs::_channel_AMBIENTAL, SDL_MIX_MAXVOLUME},
	{ecs::_channel_ALERTS, SDL_MIX_MAXVOLUME},
	{ecs::_channel_ENEMY_ATTACK, SDL_MIX_MAXVOLUME},
	{ecs::_channel_ENEMY_MOVEMENT, SDL_MIX_MAXVOLUME}
};
