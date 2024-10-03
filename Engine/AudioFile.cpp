/* AUDIO FILES */
#include "AudioFile.h"
#include <SDL_mixer.h>

AudioFile::AudioFile(const char* fileRef)
{
	file = Mix_LoadWAV(fileRef);
	if (file == NULL)
	{
		std::cout << "Failed to Load Audio file" << Mix_GetError() << "\n";
	}
}

void AudioFile::playAudio(int channel, int loops)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Mixer Error : %s\n" << SDL_GetError() << "\n";
	}
	else
	{
		std::cout << "Audio Mixer Initialized \n";
	}

	Mix_PlayChannel(channel, file, loops);
}

AudioFile::~AudioFile()
{
	Mix_FreeChunk(file);
	file = NULL;
}