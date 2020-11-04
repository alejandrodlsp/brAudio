#pragma once

#include <map>
#include <iostream>
#include <fmod.hpp>
#include <fmod_errors.h>

#define AUDIO_CHANNEL_MAX 5
#define BR_FMOD_ASSERT(x) if(x != FMOD_OK && x != FMOD_ERR_INVALID_HANDLE) { std::cout << "FMOD error: " << FMOD_ErrorString(x) << std::endl; }

namespace BreathEngine
{
	struct AudioListenerTransform
	{
		FMOD_VECTOR& pos;
		FMOD_VECTOR& vel;
		FMOD_VECTOR& forward;
		FMOD_VECTOR& up;
	};

	class AudioListener
	{
	public:
		FMOD::System* mSystem;
		void ReleaseSystem();
		void Update(float elapsed);

		FMOD::Sound* LoadSound(const std::string& path, bool streaming);
		void ReleaseSound(const std::string& path, bool streaming);

		inline void Set3DPosition(FMOD_VECTOR& pos, FMOD_VECTOR& vel, FMOD_VECTOR& forward, FMOD_VECTOR& up);
		inline void Set3DPosition(AudioListenerTransform& transform);

		// Singleton pattern
		static AudioListener* GetInstance();
		AudioListener(AudioListener const&) = delete;
		void operator=(AudioListener const&) = delete;

	private:
		typedef std::map<std::string, FMOD::Sound*> SoundMap;
		SoundMap mLoadedSamples;
		SoundMap mLoadedStreams;

	protected:
		AudioListener();
		static AudioListener* mInstance;
	};
}
