#include "TestLevel.h"
#include "Engine/Engine.h"

#include "Actor/Link.h"
#include "Controller/PlayerController.h"
#include "Controller/AIController.h"
#include "Collision/CollisionComponent.h"

TestLevel::TestLevel()
	: Level()
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// �÷��̾� ��ũ ����.
	Link* link = new Link(100, 63);
	AddActor(link);
	link->SetMoveSpeed(200.f);
	collisionComponents.push_back(link->GetCollisionComponent());

	// AI ��ũ ����.
	Link* link2 = new Link(1100, 63);
	AddActor(link2);
	link2->SetMoveSpeed(120.f);
	collisionComponents.push_back(link2->GetCollisionComponent());

	// AI ��ũ ����.
	Link* link3 = new Link(100, 260);
	AddActor(link3);
	link3->SetMoveSpeed(120.f);
	collisionComponents.push_back(link3->GetCollisionComponent());

	// AI ��ũ ����.
	Link* link4 = new Link(1100, 260);
	AddActor(link4);
	link4->SetMoveSpeed(120.f);
	collisionComponents.push_back(link4->GetCollisionComponent());

	// �÷��̾� ��Ʈ�ѷ� ����.
	playerController = new PlayerController();

	// �÷��̾� ���� ĳ���� ����.
	if (playerController != nullptr)
	{
		playerController->SetPossessedCharacter(link);
	}

	// AI ��Ʈ�ѷ� ���� �� ���� ĳ���� ����.
	AIController* aiController2 = new AIController();
	AIController* aiController3 = new AIController();
	AIController* aiController4 = new AIController();
	aiControllers.push_back(aiController2);
	aiControllers.push_back(aiController3);
	aiControllers.push_back(aiController4);

	aiController2->SetPossessedCharacter(link2);
	aiController3->SetPossessedCharacter(link3);
	aiController4->SetPossessedCharacter(link4);
}

TestLevel::~TestLevel()
{
	SafeDelete(playerController);
	for (AIController* controller : aiControllers)
	{
		SafeDelete(controller);
	}
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
		return;
	}

	// �ݸ��� �ð�ȭ.
	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		bDrawCollision = !bDrawCollision;
	}

	playerController->Update(deltaTime);

	for (AIController* controller : aiControllers)
	{
		controller->Update(deltaTime);
	}
}

void TestLevel::Draw()
{
	Super::Draw();

	if (bDrawCollision)
	{
		for (const auto& collisionComponent : collisionComponents)
		{
			collisionComponent->Draw();
		}
	}
}