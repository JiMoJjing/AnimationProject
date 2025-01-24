#pragma once

#include "Level/Level.h"

class Link;
class CollisionComponent;
class PlayerController;
class AIController;

class TestLevel : public Level
{
	RTTI_DECLARATIONS(TestLevel, Level)

public:
	TestLevel();
	virtual ~TestLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	// �ݸ��� ����.
	std::vector<CollisionComponent*> collisionComponents;

	// �ݸ��� Draw ����.
	bool bDrawCollision = false;

	// �÷��̾� ��Ʈ�ѷ�.
	PlayerController* playerController = nullptr;

	// AiController.
	std::vector<AIController*> aiControllers;
};
