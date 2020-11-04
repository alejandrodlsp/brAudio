#pragma once

namespace BreathEngine 
{
	float ChangeSemitone(float frequency, float variation) {
		static float semitone_ratio = pow(2.0f, 1.0f / 12.0f);
		return frequency * pow(semitone_ratio, variation);
	}

	float RandomBetween(float a, float b)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
}