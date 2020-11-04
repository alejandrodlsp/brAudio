#include "./AudioGroup.h"
#include "./AudioListener.h"

using namespace BreathEngine;

inline AudioGroup::AudioGroup()
{
	BR_FMOD_ASSERT( AudioListener::GetInstance()->mSystem->createChannelGroup(0, &mChannelGroup) )
	SetMasterGroup();
}

inline AudioGroup::AudioGroup(AudioGroup& group)
{
	BR_FMOD_ASSERT( AudioListener::GetInstance()->mSystem->createChannelGroup(0, &mChannelGroup) )
	SetAudioGroup(group);
}

inline AudioGroup::~AudioGroup()
{
	BR_FMOD_ASSERT(mChannelGroup->release());
}

inline void AudioGroup::SetVolume(float volume)
{
	BR_FMOD_ASSERT(mChannelGroup->setVolume(volume));
}

inline void AudioGroup::SetPitch(float pitch)
{
	BR_FMOD_ASSERT(mChannelGroup->setPitch(pitch));
}

inline void AudioGroup::Mute(bool mute)
{
	BR_FMOD_ASSERT(mChannelGroup->setMute(mute));
}

inline void AudioGroup::SetAudioGroup(AudioGroup& group)
{
	BR_FMOD_ASSERT(group.mChannelGroup->addGroup(mChannelGroup));
}

inline void AudioGroup::SetMasterGroup()
{
	FMOD::ChannelGroup* masterGroup;
	BR_FMOD_ASSERT( AudioListener::GetInstance()->mSystem->getMasterChannelGroup(&masterGroup) );
	BR_FMOD_ASSERT( masterGroup->addGroup(mChannelGroup) );
}
