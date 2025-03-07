#include "SDL_mixer.h"

#include "AudioManager.h"
#include "Logger.h"

AudioManager::AudioManager(int numberOfChannelsSet)
{
	singleChunk = nullptr;
	numberOfChannels = numberOfChannelsSet;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, numberOfChannels, 2048) < 0)
	{
		CUSTOM_LOGGER("ERROR: Audio mixer creation");
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

bool AudioManager::LoadSound(std::string soundPath)
{
	int counter = 0;
	bool found = false;

	for (std::string i : soundPaths)
	{
		if (i == soundPath)
		{
			found = true;
			break;
		}
		counter++;
	}

	if (!found)
	{
		singleChunk = Mix_LoadWAV(soundPath.data());
		chunks.push_back(singleChunk);
		soundPaths.push_back(soundPath);
	}
	else
	{
		singleChunk = chunks[counter];
	}

	if (singleChunk == nullptr)
	{
		CUSTOM_LOGGER("ERROR: Failed to Load Audio file");
		return false;
	}
	else
	{
		return true;
	}

}

void AudioManager::PlaySound(int loops, std::string soundFile, int volume)
{
	if (LoadSound(soundFile))
	{
		int i = 0;
		while (i < numberOfChannels)
		{
			if (Mix_Playing(i) == 0)
			{
				Mix_PlayChannel(i, singleChunk, loops);
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

void AudioManager::PlaySoundOnReservedChannel(int channel, int loops, std::string soundFile, int volume)
{
	if (LoadSound(soundFile))
	{
		Mix_PlayChannel(channel, singleChunk, loops);
		Mix_Volume(channel, volume);
	}
}

AudioManager::~AudioManager()
{
	for (Mix_Chunk* i : chunks)
	{
		Mix_FreeChunk(i);
		i = nullptr;
	}

	Mix_FreeChunk(singleChunk);
	singleChunk = nullptr;

	Mix_Quit();
}
