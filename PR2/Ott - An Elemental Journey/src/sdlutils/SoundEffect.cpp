// This file is part of the course TPV2@UCM - Samir Genaim

#include "SoundEffect.h"

int SoundEffect::channels_ = 0;

std::unordered_map<int, int> SoundEffect::volumesOfChannels;
