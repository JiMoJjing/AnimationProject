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

	// ���� �Լ�.
	void SetPossessedCharacter(Character* inCharacter);

private:
	// ������ ĳ����.
	Character* possessedCharacter = nullptr;

	// Ÿ�̸�.
	Timer* timer = nullptr;

	// time.
	int time = 1;

	// Move Mode.
	int moveMode = 0;
};