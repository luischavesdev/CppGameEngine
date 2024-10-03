#pragma once

class GameState 
{
private:
	float score;
	float maxScore;

public:
	GameState(float maxScoreRef);

	inline float GetScore() { return score; };

	void ChangeScore(float increment);

	~GameState();
};