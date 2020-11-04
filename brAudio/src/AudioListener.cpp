#include "./AudioListener.h"

using namespace BreathEngine;

AudioListener* AudioListener::mInstance = nullptr;

AudioListener *AudioListener::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new AudioListener();
	}
	return mInstance;
}

AudioListener::AudioListener()
{
	FMOD::System_Create(&mSystem);
	BR_FMOD_ASSERT( mSystem->init(AUDIO_CHANNEL_MAX, FMOD_INIT_NORMAL, 0) );

	FMOD_VECTOR pos = { 0.0f ,0.0f ,0.0f };
	FMOD_VECTOR vel = { 0.0f ,0.0f ,0.0f };
	FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };
	Set3DPosition(pos, vel, forward, up);

	mLoadedSamples = {};
	mLoadedStreams = {};
}

void AudioListener::ReleaseSystem()
{
	SoundMap::iterator iter;
	for (iter = mLoadedSamples.begin(); iter != mLoadedSamples.end(); ++iter)
		iter->second->release();
	for (iter = mLoadedStreams.begin(); iter != mLoadedStreams.end(); ++iter)
		iter->second->release();

	mLoadedSamples.clear();
	mLoadedStreams.clear();

	BR_FMOD_ASSERT( mSystem->release() );
	mSystem = nullptr;
}
FMOD::Sound* AudioListener::LoadSound(const std::string&path, bool streaming)
{
	SoundMap map = (streaming) ? mLoadedStreams : mLoadedSamples;
	if (map.find(path) != map.end()) return 0;

	FMOD_MODE mode = FMOD_DEFAULT | FMOD_LOOP_NORMAL | FMOD_3D;
	if (streaming) mode |= FMOD_CREATESTREAM;
	else mode |= FMOD_CREATESAMPLE;

	FMOD::Sound* fsound;
	BR_FMOD_ASSERT( mSystem->createSound(path.c_str(), mode, 0, &fsound) );

	map.insert(std::make_pair(path, fsound));

	return fsound;
}

void AudioListener::ReleaseSound(const std::string& path, bool streaming)
{
	SoundMap map = (streaming) ? mLoadedStreams : mLoadedSamples;

	if (map.find(path) != map.end()) return;
	map.find(path)->second->release();
	map.erase(path);
}

void AudioListener::Set3DPosition(FMOD_VECTOR& pos, FMOD_VECTOR& vel, FMOD_VECTOR& forward, FMOD_VECTOR& up)
{
	BR_FMOD_ASSERT( mSystem->set3DListenerAttributes(0, &pos, &vel, &forward, &up) );
}

void AudioListener::Set3DPosition(AudioListenerTransform& transform)
{
	BR_FMOD_ASSERT( mSystem->set3DListenerAttributes(0, &transform.pos, &transform.vel, &transform.forward, &transform.up) );
}

void AudioListener::Update(float elapsed)
{
	BR_FMOD_ASSERT( mSystem->update() );
}