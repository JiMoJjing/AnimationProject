#pragma once
#include "Core.h"

class Character;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void Update(float deltaTime);

	// ���� �Լ�.
	void SetPossessedCharacter(Character* inCharacter);

private:
	// ������ ĳ����.
	Character* possessedCharacter = nullptr;
};