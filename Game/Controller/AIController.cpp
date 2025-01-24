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

	// Tab Ű�� ai Ȱ��ȭ, ��Ȱ��ȭ.
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
			// ���� �̵����� ����.
			++moveMode;

			// 4�����̹Ƿ� ������ ����.
			moveMode %= 4;

			// �� �Ʒ� �̵��� ���� ������ �̵� �ӵ�, �̵� �ð� �������� time����.
			++time;
			time %= 2;
			timer->Reset();

			// ���� �������� 4��, �� �Ʒ��� 3�� �̵�.
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
