#pragma once
#pragma warning(disable : 4251)

#include "Core.h"
#include "Math/Vector2.h"

class CollisionComponent;
class ENGINE_API Physics
{
public:
	Physics();
	~Physics();

	// ������Ʈ.
	void Update(float deltaTime);

	// �ݸ��� ������Ʈ ���.
	void AddComponent(CollisionComponent* inComponent);

private:
	// CollisionComponent ��Ƶ� �����̳�.
	std::vector<CollisionComponent*> collisionComponents;
};