#include "../src/brAudio.h"

#include <chrono>

using namespace BreathEngine;

int main()
{
	// Load background sound (As stream)
	Sound backgroundSound("res/sound/birds.ogg", true);
	AudioSource* backgroundSource = new AudioSource(&backgroundSound, 1.0f, 1.0f, true);
	backgroundSource->Play();

	// Load left sound
	Sound leftSound("res/sound/dog.ogg");
	AudioSource* leftSource = new AudioSource(&leftSound, 1.0f, 1.0f, false);
	leftSource->Set3DPosition({ -1.0, 0.0, 1.0 });

	// Load right sound
	Sound rightSound("res/sound/dog.ogg");
	AudioSource* rightSource = new AudioSource(&rightSound, 1.0f, 1.0f, false);
	rightSource->Set3DPosition({ 1.0, 0.0, 1.0 });

	// Load moving sound
	Sound movingSound("res/sound/cat.ogg");
	AudioSource* movingSource = new AudioSource(&movingSound, 1.0f, 1.0f, false);
	

	// Random play settings (minVol, maxVol, minPitch, maxPitch)
	RandomPlaySettings playSettings{ 0.3f, 0.8f, -1.0f, 1.0f };

	auto lastTime = std::chrono::high_resolution_clock::now();

	float xpos = 0.0f;
	float xspeed = 1.0f;
	bool dir = false;

	float soundTimer = 5.0f;
	int soundIndex = 0;

	while (true)
	{
		// Calculate delta time
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = currentTime - lastTime;
		lastTime = currentTime;
		
		movingSource->Set3D({ xpos, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, 10000.0f);
		xpos += dir ? (xspeed * elapsed.count()) : -(xspeed * elapsed.count());

		// Handling moving source
		if (xpos < -1.0f) {
			dir = true;
			xpos = -1.0f;
		}
		else if (xpos > 1.0f)
		{
			dir = false;
			xpos = 1.0f;
		}
		soundTimer += elapsed.count();
		
		if (soundTimer > 7.0f) {
			soundTimer = 0.0f;
			switch (soundIndex)
			{
			case 0: movingSource->Play(); break;
			case 1: leftSource->Play(); break;
			case 2: rightSource->Play(); break;
			}	
			soundIndex++;
			soundIndex = soundIndex % 3;
		}

		// Update brAudio
		AudioListener::GetInstance()->Update(elapsed.count());
	}

	// brAudio cleanup
	AudioListener::GetInstance()->ReleaseSystem();
}
