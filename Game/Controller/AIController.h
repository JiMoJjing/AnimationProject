#pragma once
#include "Core.h"

class Character;
class Timer;

class AIController
{
public:
	AIController();
	~AIController();

	void Update(float deltaTime);

	// 빙의 함수.
	void SetPossessedCharacter(Character* inCharacter);

private:
	// 빙의한 캐릭터.
	Character* possessedCharacter = nullptr;

	// 타이머.
	Timer* timer = nullptr;

	// time.
	int time = 1;

	// Move Mode.
	int moveMode = 0;
};