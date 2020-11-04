#pragma once

#include <fmod.hpp>
#include <string>

namespace BreathEngine
{
	class Sound
	{
	public:
		Sound(const std::string& path, bool streaming = false);
		~Sound();

		FMOD::Sound* mSound;

		bool IsStreaming();
		std::string GetPath();
	private:
		bool mStreaming;
		std::string mPath;
	};
}

