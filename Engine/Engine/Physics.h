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

	// 업데이트.
	void Update(float deltaTime);

	// 콜리전 컴포넌트 등록.
	void AddComponent(CollisionComponent* inComponent);

private:
	// CollisionComponent 모아둔 컨테이너.
	std::vector<CollisionComponent*> collisionComponents;
};