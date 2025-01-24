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
	// ��ũ�� ������ ũ�Ⱑ���ͼ� ����Ʈ�� ����.
	Vector2 screenSize = Engine::Get().ScreenSize();
	QuadTree quadTree(new CollisionComponent(0, 0, screenSize.x, screenSize.y));

	// ��� ����.
	for (CollisionComponent* component : collisionComponents)
	{
		if(component != nullptr)
		{
			quadTree.Insert(new Node(component));
		}
	}

	// ��� ������Ʈ �浹 ���.
	for (CollisionComponent* component : collisionComponents)
	{
		// �˻��� ������Ʈ ������ �������� ��� ����.
		Node intersectNode(new CollisionComponent(component->GetPosition(), component->GetSize()));

		// �ش� ���� ����Ʈ������ �˻�.
		std::vector<Node*> intersects = quadTree.Query(&intersectNode);

		// �ڱ��ڽ��̸� �浹 �˻� ���ϴ� ���·� �Ķ��� ����.
		if (intersects.size() == 1 && intersects[0]->GetBounds() == component)
		{
			component->SetCollisionColor(Color::Blue);
			continue;
		}

		// ���� �浹 ���ɼ� �ִ� ���� ���� �˻�.
		for (Node* node : intersects)
		{
			CollisionComponent* otherComponent = node->GetBounds();
			
			// �ڱ��ڽ��� ����.
			if (component == otherComponent)
			{
				continue;
			}

			// �浹 ���¸� ������, �浹 ���ɼ��ִµ� �浹 ���� �ƴϸ� �ʷϻ�.
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
