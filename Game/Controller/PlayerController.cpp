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

	// 입력 방향에 따른 캐릭터 Move 함수 호출.
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