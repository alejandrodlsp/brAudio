#pragma once
#include <fmod.hpp>

namespace BreathEngine 
{
	class AudioGroup
	{
	public:
		AudioGroup();
		AudioGroup(AudioGroup& group);
		~AudioGroup();

		inline void SetVolume(float volume);
		inline void SetPitch(float pitch);
		inline void Mute(bool mute);

		inline void SetAudioGroup(AudioGroup& group);
		inline void SetMasterGroup();
	private:
		friend class AudioSource;
		FMOD::ChannelGroup* mChannelGroup;
	};
}

