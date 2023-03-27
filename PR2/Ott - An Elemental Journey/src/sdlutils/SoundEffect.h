// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <string>
#include <SDL_mixer.h>
#include <cassert>
#include <unordered_map>
#include "../game/ecs.h"

#define _CHECK_CHANNEL_(channel) \
	assert(channel >= -1 && channel < static_cast<int>(channels_));

class SoundEffect {
public:

	// cannot copy objects of this type!
	SoundEffect& operator=(SoundEffect &other) = delete;
	SoundEffect(const SoundEffect&) = delete;

	SoundEffect(const std::string &fileName) {
		chunk_ = Mix_LoadWAV(fileName.c_str());
		assert(chunk_ != nullptr);
	}

	SoundEffect(SoundEffect &&other) noexcept {
		chunk_ = other.chunk_;
		other.chunk_ = nullptr;
	}

	SoundEffect& operator=(SoundEffect &&other) noexcept {
		this->~SoundEffect();
		chunk_ = other.chunk_;
		other.chunk_ = nullptr;
		return *this;
	}

	virtual ~SoundEffect() {
		if (chunk_ != nullptr)
			Mix_FreeChunk(chunk_);
	}

	inline static void groupChannels() {
		int firstChannel = 0, lastChannel = 31;
		for (int i = 0; i < ecs::maxChannelId; ++i) {
			Mix_GroupChannels(firstChannel, lastChannel, i);
			firstChannel += 32; lastChannel += 32;
		}
	}

	inline static int returnFreeChannel(int channelGrp) {
		assert(channelGrp >= 0 && channelGrp < ecs::maxChannelId);
		return Mix_GroupAvailable(channelGrp);
	}

	inline int play(int loops = 0, int group = -1) const {
		int channel = returnFreeChannel(group);
		_CHECK_CHANNEL_(channel);
		assert(loops >= -1);
		if (Mix_GetChunk(Mix_GroupNewer(group)) == chunk_ || Mix_GetChunk(Mix_GroupOldest(group)) == chunk_) return -1;
		else return Mix_PlayChannel(channel, chunk_, loops);
	}

	inline int playFor(int miliseconds, int loops = 0, int group = -1) const {
		int channel = returnFreeChannel(group);
		_CHECK_CHANNEL_(channel);
		assert(loops >= -1);
		if (Mix_GetChunk(Mix_GroupNewer(group)) == chunk_ || Mix_GetChunk(Mix_GroupOldest(group)) == chunk_) return -1;
		return Mix_PlayChannelTimed(channel, chunk_, loops, miliseconds);
	}

	inline int setVolume(int volume) {
		assert(volume >= 0 && volume <= 128);
		return Mix_VolumeChunk(chunk_, volume);
	}

	// static methods for sound effects
	//
	inline static void pauseChannel(int channel = -1) {
		_CHECK_CHANNEL_(channel);
		Mix_Pause(channel);
	}

	inline static void resumeChannel(int channel = -1) {
		_CHECK_CHANNEL_(channel);
		Mix_Resume(channel);
	}

	inline static void haltChannel(int channel = -1) {
		_CHECK_CHANNEL_(channel);
		Mix_HaltChannel(channel);
	}

	inline static void fadeOutChannel(int miliseconds, int channel = -1) {
		_CHECK_CHANNEL_(channel);
		Mix_FadeOutChannel(channel, miliseconds);
	}

	inline static int setChannelVolume(int volume, int group = -1) {
		float v = convertVolumeToSDLMixerValue(volume);
		assert(v >= 0 && v <= 128);
		volumesOfChannels[group] = v;
		for (int i = (group * 32); i < (group + 1) * 32; ++i) {
			_CHECK_CHANNEL_(i);
			return Mix_Volume(i, v);
		}
	}

	inline static int setMasterVolume(int volume) {
		float v = convertVolumeToSDLMixerValue(volume);
		assert(v >= 0 && v <= 128);
		masterVolume = v;
		return Mix_MasterVolume(v);
	}

    inline static bool isSoundBeingPlayed(int channel = -1) {
        _CHECK_CHANNEL_(channel);
        return Mix_Playing(channel);
    }

	inline static float getChannelVolume(int channel = -1) {
		_CHECK_CHANNEL_(channel);
		return convertSDLMixerValueToVolume(volumesOfChannels[channel]);
	}

	inline static int getMasterVolume() {
		return convertSDLMixerValueToVolume(masterVolume);
	}

	inline static float getGeneralSoundsVolume() {
		return convertSDLMixerValueToVolume(generalSoundsVolume);
	}

	inline static void setGeneralSoundsVolume(int volume) {
		float v = convertVolumeToSDLMixerValue(volume);
		assert(v >= 0 && v <= 128);
		generalSoundsVolume = v;
	}

	inline static int setNumberofChannels(int n) {
		assert(n > 0);
		return channels_ = Mix_AllocateChannels(n);

	}

	inline static int getNumberOfChannels() {
		return channels_;
	}

	inline static float convertVolumeToSDLMixerValue(int volume) {
		return ((SDL_MIX_MAXVOLUME * volume) / 100);
	}

	inline static float convertSDLMixerValueToVolume(int SDLVolume) {
		return ((SDLVolume * 100) / SDL_MIX_MAXVOLUME);
	}

private:

	inline static void checkChannel(int channel) {
		assert(channel >= -1 && channel < static_cast<int>(channels_));
	}

	Mix_Chunk *chunk_;
	static int channels_; // initialized in cpp

	static std::unordered_map<int, int> volumesOfChannels;
	static int generalSoundsVolume;
	static int masterVolume;
};

