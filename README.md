# Breath Audio

brAudio is a lightweight audio library I wrote for my game engine (In progress). It is built on top of [FMOD audio](https://www.fmod.com/resources/documentation-api?version=2.1&page=welcome.html). This is my first time writting an audio engine, this is not a finished robust product.

## Support
- Sound loading and streaming
- Audio sources with media control
- 3D audio
- Audio groups
- Pitch and volume control

## TODO
- Sound effects
- Reverb zones
- Premake support for project generation
- Multiple audio listener support
- Integrate with [brMath](https://github.com/alejandrodlsp/brMath)

## Examples
Load sounds
```cpp
// Load sound as a stream
Sound streamedSound("res/sound/birds.mp3", true);
// Load sound 
Sound loadedSound("res/sound/birds.mp3", false);
```

Creating an Audio Source
```cpp
// Create audio source (sound, volume, pitch, looping)
AudioSource* backgroundSource = new AudioSource(&streamedSound, 1.0f, 1.0f, true);
```

Manage an audio source
```cpp
// Play audio source
backgroundSource->Play();

// Control audio source
backgroundSource->Pause();
backgroundSource->Mute(true);
backgroundSource->Resume();

// Set audio source parameters
backgroundSource->Set3DPosition({ 1.0, 0.0, 1.0 });
backgroundSource->SetPitch(0.5f);
backgroundSource->SetVolume(0.5f);

// Change source's sound
backgroundSource->SetActiveSound(&loadedSound);
```

Create and assign an Audio Group
```cpp
AudioGroup masterGroup;
AudioGroup sfxGroup(masterGroup);
backgroundSource->SetAudioGroup(sfxGroup);
```

Manage an audio group
```cpp
sfxGroup->SetVolume(0.5f);
sfxGroup->SetPitch(0.5f);
sfxGroup->Mute(true);
```

Update audio listener every frame, and cleanup afterwards
```cpp
while(true)
{
    float elapsed = 0;
    AudioListener::GetInstance()->Update(elapsed);
}

// Clean-up
AudioListener::GetInstance()->ReleaseSystem();
```
