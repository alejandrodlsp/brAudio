#include <time.h>

#include "./AudioSource.h"

#include "./Sound.h"
#include "./AudioHelper.h"
#include "./AudioGroup.h"
#include "./AudioListener.h"

using namespace BreathEngine;

AudioSource::AudioSource(float volume, float pitch, bool loop)
	: mLoop(loop?-1:0), mVolume(volume), mPitch(pitch), mActiveAudioGroup(nullptr), mActiveChannel(nullptr), mActiveSound(nullptr)
{
	srand(time(0));
	mRolloffMin = 1.0f;
	mRolloffMax = 10000.0f;
}

AudioSource::AudioSource(Sound* sound, float volume, float pitch, bool loop)
	: AudioSource(volume, pitch, loop)
{
	SetActiveSound(sound);
}

void AudioSource::SetActiveSound(Sound* sound)
{
	if (IsActiveChannel())
		BR_FMOD_ASSERT(mActiveChannel->stop())	
	mActiveSound = sound;
}

void AudioSource::Play()
{
	// If active channel, stop current active channel
	if (mActiveChannel != nullptr) {
		mActiveChannel->stop();
		mActiveChannel = 0;
	}
	
	// Start sound play and pause immediatelly
	BR_FMOD_ASSERT( AudioListener::GetInstance()->mSystem->playSound(mActiveSound->mSound, 0, true, &mActiveChannel) )
	
	// If channel group is specified, set channel group
	if(mActiveAudioGroup != nullptr)
		BR_FMOD_ASSERT( mActiveChannel->setChannelGroup(mActiveAudioGroup->mChannelGroup) )

	// Set 3D channel settings
	BR_FMOD_ASSERT( mActiveChannel->set3DMinMaxDistance(mRolloffMin, mRolloffMax) )
	BR_FMOD_ASSERT( mActiveChannel->set3DAttributes(&mPosition, &mVelocity) )

	// Set channel properties
	BR_FMOD_ASSERT( mActiveChannel->setVolume(mVolume) )
	BR_FMOD_ASSERT( mActiveChannel->setLoopCount(mLoop) )

	float frequency;
	BR_FMOD_ASSERT( mActiveChannel->getFrequency(&frequency) )
	BR_FMOD_ASSERT( mActiveChannel->setFrequency(ChangeSemitone(frequency, mPitch)) )

	// Resume playing
	BR_FMOD_ASSERT( mActiveChannel->setPaused(false) )
}

void AudioSource::Play(RandomPlaySettings& settings)
{
	// Calculate random pitch and volume
	float volume = RandomBetween(settings.volumeMin, settings.volumeMax);
	float pitch = RandomBetween(settings.pitchMin, settings.pitchMax);

	// If active channel, stop current active channel
	if (mActiveChannel != nullptr)
		BR_FMOD_ASSERT( mActiveChannel->stop() );

	// Start sound play and pause immediatelly
	BR_FMOD_ASSERT( AudioListener::GetInstance()->mSystem->playSound(mActiveSound->mSound, 0, true, &mActiveChannel) );

	// If channel group is specified, set channel group
	if (mActiveAudioGroup != nullptr)
		BR_FMOD_ASSERT( mActiveChannel->setChannelGroup(mActiveAudioGroup->mChannelGroup) );

	// Set 3D channel settings
	BR_FMOD_ASSERT( mActiveChannel->set3DMinMaxDistance(mRolloffMin, mRolloffMax) );
	BR_FMOD_ASSERT( mActiveChannel->set3DAttributes(&mPosition, &mVelocity) );

	// Set channel properties
	BR_FMOD_ASSERT( mActiveChannel->setVolume(volume) );
	BR_FMOD_ASSERT( mActiveChannel->setLoopCount(mLoop) );

	float frequency;
	BR_FMOD_ASSERT( mActiveChannel->getFrequency(&frequency) );
	BR_FMOD_ASSERT( mActiveChannel->setFrequency(ChangeSemitone(frequency, pitch)) );

	// Resume playing
	BR_FMOD_ASSERT( mActiveChannel->setPaused(false) );
}

inline void AudioSource::SetLoop(int loopCount)
{
	mLoop = loopCount;
}

inline void AudioSource::SetLoop(bool loop)
{
	mLoop = loop ? -1 : 0;
}

inline void AudioSource::Pause()
{
	if (!IsActiveChannel()) return;
	BR_FMOD_ASSERT( mActiveChannel->setPaused(true) );
}

inline void AudioSource::Resume()
{
	if (!IsActiveChannel()) return;
	BR_FMOD_ASSERT( mActiveChannel->setPaused(false) );
}

inline void AudioSource::Mute(bool mute)
{
	if (!IsActiveChannel()) return;		
	BR_FMOD_ASSERT( mActiveChannel->setMute(mute) );
}

inline void AudioSource::SetVolume(float volume)
{
	mVolume = volume;
	if (!IsActiveChannel()) return;
	BR_FMOD_ASSERT( mActiveChannel->setVolume(volume) );
}

void AudioSource::SetPitch(float pitch)
{
	mPitch = pitch;
	if (!IsActiveChannel()) return;

	float frequency;
	BR_FMOD_ASSERT( mActiveChannel->getFrequency(&frequency) );
	BR_FMOD_ASSERT( mActiveChannel->setFrequency(ChangeSemitone(frequency, mPitch)) );
	BR_FMOD_ASSERT( mActiveChannel->setPaused(false) );
}

inline void AudioSource::SetAudioGroup(AudioGroup* group)
{
	mActiveAudioGroup = group;
	if (!IsActiveChannel()) return;
	BR_FMOD_ASSERT( mActiveChannel->setChannelGroup(mActiveAudioGroup->mChannelGroup) );
}

void AudioSource::Set3D(FMOD_VECTOR pos, FMOD_VECTOR vel, float rolloffMin, float rolloffMax)
{
	Set3DPosition(pos);
	Set3DVelocity(vel);
	
	mRolloffMin = rolloffMin;
	mRolloffMax = rolloffMax;

	if (!IsActiveChannel()) return;
	BR_FMOD_ASSERT( mActiveChannel->set3DMinMaxDistance(mRolloffMin, mRolloffMax) );
}

void AudioSource::Set3DPosition(FMOD_VECTOR pos)
{
	mPosition = pos;
	if (!IsActiveChannel()) return;
	BR_FMOD_ASSERT( mActiveChannel->set3DAttributes(&mPosition, &mVelocity) );
}

void AudioSource::Set3DVelocity(FMOD_VECTOR vel)
{
	mVelocity = vel;
	if (!IsActiveChannel()) return;
	BR_FMOD_ASSERT( mActiveChannel->set3DAttributes(&mPosition, &mVelocity) );
}

bool AudioSource::IsActiveChannel()
{
	if (mActiveChannel == NULL) return false;
	bool playing = false;
	BR_FMOD_ASSERT(mActiveChannel->isPlaying(&playing));
	return playing;
}