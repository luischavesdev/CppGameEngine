#include <iostream>
#include <iomanip>
#include "GameState.h"

GameState::GameState(float maxScoreRef)
{
	maxScore = maxScoreRef;
	score = 0.0f;
}

void GameState::ChangeScore(float increment)
{
	score = std::max(0.0f, std::min(score + increment, maxScore));
	std::cout << score << "\n";
}

GameState::~GameState()
{

}
