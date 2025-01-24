#pragma once
#include "Core.h"

class Character;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void Update(float deltaTime);

	// 빙의 함수.
	void SetPossessedCharacter(Character* inCharacter);

private:
	// 빙의한 캐릭터.
	Character* possessedCharacter = nullptr;
};