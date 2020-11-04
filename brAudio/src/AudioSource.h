#pragma once

#include <string>
#include <fmod.hpp>

namespace BreathEngine
{
	class AudioGroup;
	class Sound;

	struct RandomPlaySettings
	{
		float volumeMin;
		float volumeMax;
		float pitchMin;
		float pitchMax;
		RandomPlaySettings(float vMin, float vMax, float pMin, float pMax)
			: volumeMin(vMin), volumeMax(vMax), pitchMin(pMin), pitchMax(pMax)
		{
		}
	};

	class AudioSource
	{
	public:
		AudioSource(float mVolume = 1.0f, float mPitch = 1.0f, bool loop = false);
		AudioSource(Sound* sound, float mVolume = 1.0f, float mPitch = 1.0f, bool loop = false);

		void SetActiveSound(Sound* sound);

		inline void Pause();
		inline void Resume();
		inline void Mute(bool mute);

		void Play();
		void Play(RandomPlaySettings& playSettings);

		inline void SetLoop(int loopCount = -1);
		inline void SetLoop(bool loop);

		inline void SetVolume(float volume);
		void SetPitch(float pitch);

		void Set3D(FMOD_VECTOR pos, FMOD_VECTOR vel, float rolloffMin, float rolloffMax);
		void Set3DPosition(FMOD_VECTOR pos);
		void Set3DVelocity(FMOD_VECTOR vel);

		inline void SetAudioGroup(AudioGroup* group);
	private:
		Sound* mActiveSound;
		FMOD::Channel* mActiveChannel;
		AudioGroup* mActiveAudioGroup;

		bool IsActiveChannel();

		FMOD_VECTOR mPosition;
		FMOD_VECTOR mVelocity;
		float mRolloffMin;
		float mRolloffMax;

		float mVolume;
		float mPitch;
		int mLoop;
	};

}