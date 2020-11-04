#include "./Sound.h"
#include "./AudioListener.h"

using namespace BreathEngine;

Sound::Sound(const std::string& path, bool streaming)
	: mPath(path), mStreaming(streaming)
{
	mSound = AudioListener::GetInstance()->LoadSound(mPath, mStreaming);
}

Sound::~Sound()
{
	mSound = 0;
	AudioListener::GetInstance()->ReleaseSound(mPath, mStreaming);
}

bool Sound::IsStreaming()
{
	return mStreaming;
}

std::string Sound::GetPath()
{
	return mPath;
}
