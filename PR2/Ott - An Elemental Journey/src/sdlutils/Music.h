// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <string>
#include <SDL_mixer.h>
#include <assert.h>

class Music {
public:

	// cannot copy objects of this type!
	Music& operator=(Music &other) = delete;
	Music(const Music&) = delete;

	Music(const std::string &fileName) {
		music_ = Mix_LoadMUS(fileName.c_str());
		assert(music_ != nullptr);
	}

	Music(Music &&other) noexcept {
		music_ = other.music_;
		other.music_ = nullptr;
	}

	Music& operator=(Music &&other) noexcept {
		this->~Music();
		music_ = other.music_;
		other.music_ = nullptr;
		return *this;
	}

	virtual ~Music() {
		if (music_ != nullptr)
			Mix_FreeMusic(music_);
	}

	inline void play(int loops = -1) const {
		assert(loops >= -1 && music_ != nullptr);
		Mix_PlayMusic(music_, loops);
	}

	inline static int setMusicVolume(int volume) {
		float v = convertVolumeToSDLMixerValue(volume);
		assert(v >= 0 && v <= 128);
		vol = v;
		return Mix_VolumeMusic(v);
	}

	inline static int getMusicVolume() {
		return convertSDLMixerValueToVolume(vol);
	}

	inline static void haltMusic() {
		Mix_HaltMusic();
	}

	inline static void pauseMusic() {
		Mix_PauseMusic();
	}

	inline static void resumeMusic() {
		Mix_ResumeMusic();
	}

	inline static void fadeOutMusic(int miliseconds) {
		Mix_FadeOutMusic(miliseconds);
	}

	inline void fadeInMusic(int miliseconds, int loops = -1) {
		assert(loops >= -1 && music_ != nullptr);
		Mix_FadeInMusic(music_, loops, miliseconds);
	}

	inline static float convertVolumeToSDLMixerValue(int volume) {
		return ((SDL_MIX_MAXVOLUME * volume) / 100);
	}

	inline static float convertSDLMixerValueToVolume(int SDLVolume) {
		return ((SDLVolume * 100) / SDL_MIX_MAXVOLUME);
	}


private:
	static int vol;
	Mix_Music *music_;
};

