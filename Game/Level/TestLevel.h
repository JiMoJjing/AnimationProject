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
	// 콜리전 모음.
	std::vector<CollisionComponent*> collisionComponents;

	// 콜리전 Draw 여부.
	bool bDrawCollision = false;

	// 플레이어 컨트롤러.
	PlayerController* playerController = nullptr;

	// AiController.
	std::vector<AIController*> aiControllers;
};
