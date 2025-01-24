#include "AIController.h"

#include "Engine/Engine.h"
#include "Engine/Timer.h"

#include "Actor/Character.h"

AIController::AIController()
{
	timer = new Timer((float)(time + 3));
}

AIController::~AIController()
{
	possessedCharacter = nullptr;

	SafeDelete(timer);
}

void AIController::Update(float deltaTime)
{
	static bool bPlayAIContoller = false;

	// Tab 키로 ai 활성화, 비활성화.
	if (Engine::Get().GetKeyDown(VK_TAB))
	{
		bPlayAIContoller = !bPlayAIContoller;
	}

	if (bPlayAIContoller == false)
	{
		return;
	}

	if (possessedCharacter == nullptr)
	{
		return;
	}

	if (timer != nullptr)
	{
		timer->Update(deltaTime);
		if (timer->IsTimeOut())
		{
			// 다음 이동모드로 변경.
			++moveMode;

			// 4방향이므로 나머지 연산.
			moveMode %= 4;

			// 위 아래 이동과 왼쪽 오른쪽 이동 속도, 이동 시간 구분위한 time변수.
			++time;
			time %= 2;
			timer->Reset();

			// 왼쪽 오른쪽은 4초, 위 아래는 3초 이동.
			timer->SetTime((float)(time + 3));

			if (time & 1)
			{
				possessedCharacter->SetMoveSpeed(120.f);
			}
			else
			{
				possessedCharacter->SetMoveSpeed(90.f);
			}
		}
	}

	switch (moveMode)
	{
	case 0:
		possessedCharacter->Move(Vector2(1, 0));
		break;
	case 1:
		possessedCharacter->Move(Vector2(0, 1));
		break;
	case 2:
		possessedCharacter->Move(Vector2(-1, 0));
		break;
	case 3:
		possessedCharacter->Move(Vector2(0, -1));
		break;
	default:
		break;
	}
	
}

void AIController::SetPossessedCharacter(Character* inCharacter)
{
	if (inCharacter != nullptr)
	{
		possessedCharacter = inCharacter;
	}
}
