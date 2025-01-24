#include "PreCompiledHeader.h"
#include "Physics.h"
#include "Engine/Engine.h"
#include "Collision/CollisionComponent.h"
#include "Math/QuadTree.h"

Physics::Physics()
{
}

Physics::~Physics()
{

}

void Physics::Update(float deltaTime)
{
	// 스크린 사이즈 크기가져와서 쿼드트리 생성.
	Vector2 screenSize = Engine::Get().ScreenSize();
	QuadTree quadTree(new CollisionComponent(0, 0, screenSize.x, screenSize.y));

	// 노드 삽입.
	for (CollisionComponent* component : collisionComponents)
	{
		if(component != nullptr)
		{
			quadTree.Insert(new Node(component));
		}
	}

	// 모든 컴포넌트 충돌 계산.
	for (CollisionComponent* component : collisionComponents)
	{
		// 검사할 컴포넌트 포지션 기준으로 노드 생성.
		Node intersectNode(new CollisionComponent(component->GetPosition(), component->GetSize()));

		// 해당 노드로 쿼드트리에서 검사.
		std::vector<Node*> intersects = quadTree.Query(&intersectNode);

		// 자기자신이면 충돌 검사 안하는 상태로 파란색 설정.
		if (intersects.size() == 1 && intersects[0]->GetBounds() == component)
		{
			component->SetCollisionColor(Color::Blue);
			continue;
		}

		// 얻어온 충돌 가능성 있는 노드들 상대로 검사.
		for (Node* node : intersects)
		{
			CollisionComponent* otherComponent = node->GetBounds();
			
			// 자기자신은 무시.
			if (component == otherComponent)
			{
				continue;
			}

			// 충돌 상태면 빨간색, 충돌 가능성있는데 충돌 상태 아니면 초록색.
			if (otherComponent)
			{
				if (component->Intersect(otherComponent))
				{
					component->ComponentHit(otherComponent->GetOwner());
				}
				else
				{
					component->SetCollisionColor(Color::Green);
				}
			}
		}
	}
}

void Physics::AddComponent(CollisionComponent* inComponent)
{
	collisionComponents.push_back(inComponent);
}
