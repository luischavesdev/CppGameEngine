#pragma once
#include <iostream>
#include <vector>
//#include <SDL_mixer.h>

class AudioManager
{
private:

	const char* musicFileReference = NULL;
	class Mix_Chunk* file;

	float numberOfChannels;

	std::vector<class Mix_Chunk*> files{};
	std::vector<const char*> cfiles{};



public:
	AudioManager(int numberOfChannels);

	void SetChannelVolume(int channel, int volume);
	void PauseChannel(int channel);
	void ResumeChannel(int channel);

	void PlaySound(int loops, const char* soundFile, int volume);
	void PlaySoundOnReservedChannel(int channel, int loops, const char* soundFile, int volume);

	void PrintChannels();

	~AudioManager();
};