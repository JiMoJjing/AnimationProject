#include "PlayerController.h"
#include "Engine/Engine.h"
#include "Actor/Character.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
	possessedCharacter = nullptr;
}

void PlayerController::Update(float deltaTime)
{
	if (possessedCharacter == nullptr)
	{
		return;
	}

	// �Է� ���⿡ ���� ĳ���� Move �Լ� ȣ��.
	if (Engine::Get().GetKey(VK_LEFT))
	{
		possessedCharacter->Move(Vector2(-1, 0));
	}

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		possessedCharacter->Move(Vector2(1, 0));
	}

	if (Engine::Get().GetKey(VK_UP))
	{
		possessedCharacter->Move(Vector2(0, -1));
	}

	if (Engine::Get().GetKey(VK_DOWN))
	{
		possessedCharacter->Move(Vector2(0, 1));
	}
}

void PlayerController::SetPossessedCharacter(Character* inCharacter)
{
	if (inCharacter != nullptr)
	{
		possessedCharacter = inCharacter;
	}
}