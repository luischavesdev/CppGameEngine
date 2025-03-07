#pragma once
#include <vector>
#include <string>

class AudioManager
{
private:
	class Mix_Chunk* singleChunk;
	float numberOfChannels;

	std::vector<Mix_Chunk*> chunks{};
	std::vector<std::string> soundPaths{};

	bool LoadSound(std::string soundPath);


public:
	AudioManager(int numberOfChannels);

	void SetChannelVolume(int channel, int volume);
	void PauseChannel(int channel);
	void ResumeChannel(int channel);

	void PlaySound(int loops, std::string soundFile, int volume);
	void PlaySoundOnReservedChannel(int channel, int loops, std::string soundFile, int volume);

	~AudioManager();
};
