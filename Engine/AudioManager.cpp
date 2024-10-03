#include "AudioManager.h"
#include <SDL_mixer.h>

/* AUDIO MANAGER AND MUSIC */

AudioManager::AudioManager(int numberOfChannelsSet)
{
	file = NULL;
	numberOfChannels = numberOfChannelsSet;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, numberOfChannels, 2048) < 0)
	{
		std::cout << "Mixer Error : %s\n" << SDL_GetError() << "\n";
	}
	else
	{
		std::cout << "Audio Mixer Initialized \n";
	}
}

void AudioManager::PauseChannel(int channel)
{
	Mix_HaltChannel(channel);
}

void AudioManager::ResumeChannel(int channel)
{
	Mix_Resume(channel);
}

void AudioManager::SetChannelVolume(int channel, int volume)
{
	Mix_Volume(channel, volume);
}

void AudioManager::PlaySound(int loops, const char* soundFile, int volume)
{
	int counter = 0;
	bool found = false;
	for (const char* i : cfiles)
	{
		if (soundFile == i)
		{
			found = true;
			break;
		}
		counter++;
	}

	if (!found)
	{
		file = Mix_LoadWAV(soundFile);
		files.push_back(file);
		cfiles.push_back(soundFile);
	}
	else
	{
		file = files[counter];
	}

	if (file == NULL)
	{
		std::cout << "Failed to Load Audio file" << Mix_GetError() << "\n";
	}
	else
	{
		int i = 0;
		while (i < numberOfChannels)
		{
			if (Mix_Playing(i) == 0)
			{
				Mix_PlayChannel(i, file, loops);
				Mix_Volume(i, volume);
				i = numberOfChannels;
				break;
			}
			else
			{
				i++;
			}
		}
	}
}

void AudioManager::PlaySoundOnReservedChannel(int channel, int loops, const char* soundFile, int volume)
{
	int counter = 0;
	bool found = false;
	for (const char* i : cfiles)
	{
		if (soundFile == i)
		{
			found = true;
			break;
		}
		counter++;
	}

	if (!found)
	{
		file = Mix_LoadWAV(soundFile);
		files.push_back(file);
		cfiles.push_back(soundFile);
	}
	else
	{
		file = files[counter];
	}

	file = Mix_LoadWAV(soundFile);
	if (file == NULL)
	{
		std::cout << "Failed to Load Audio file" << Mix_GetError() << "\n";
	}

	Mix_PlayChannel(channel, file, loops);
	Mix_Volume(channel, volume);
}

//Debug
void AudioManager::PrintChannels()
{
	for (int i = 0; i < numberOfChannels; i++)
	{
		std::cout << "Channel nº" << i << " = " << Mix_Playing(i) << "\n";
	}

	std::cout << "\n\n\n\n\n\n\n\n\n";
}

//Destructor
AudioManager::~AudioManager()
{
	for (Mix_Chunk* i : files)
	{
		Mix_FreeChunk(i);
		i = NULL;
	}

	for (const char* i : cfiles)
	{
		i = NULL;
	}

	Mix_FreeChunk(file);
	file = NULL;
	Mix_Quit();
}
