#include "PreCompiledHeader.h"
#include "CollisionComponent.h"
#include "Engine/Engine.h"

//#include "Actor/Actor.h"

CollisionComponent::CollisionComponent(const Vector2& position, const Vector2& size)
{
	this->position = position;
	this->size = size;
}

CollisionComponent::CollisionComponent(int positionX, int positionY, int sizeX, int sizeY)
{
	this->position.x = positionX;
	this->position.y = positionY;
	this->size.x = sizeX;
	this->size.y = sizeY;
}

CollisionComponent::~CollisionComponent()
{
	if (owner != nullptr)
	{
		owner = nullptr;
	}
}

void CollisionComponent::Update(float deltaTime)
{
	// ��ġ ������Ʈ.
	if (owner != nullptr)
	{
		position = owner->Position();
	}
}

void CollisionComponent::Draw()
{
	// ���� ����.
	SetColor(color);
	
	// �׸���.
	for (int ix = 0; ix < size.y; ++ix)
	{
		// Ŀ�� ��ġ ����.
		Vector2 drawPosition = position;
		drawPosition.y += ix;
		Engine::Get().SetCursorPosition(drawPosition);

		if (ix == 0 || ix == size.y - 1)
		{
			Log(std::string(size.x, '#'));
		}
		else
		{
			Log("#");
			drawPosition.x += size.x;
			Engine::Get().SetCursorPosition(drawPosition);
			Log("#");
		}
	}

	// ���� ����.
	SetColor(Color::White);
}

bool CollisionComponent::Intersect(CollisionComponent* other)
{
	// �������� ����.
	Vector2 posStart = this->GetPosition();
	Vector2 posEnd = posStart + this->GetSize();

	Vector2 otherPosStart = other->GetPosition();
	Vector2 otherPosEnd = otherPosStart + other->GetSize();

	// �浹 �˻�.
	if (posEnd.x < otherPosStart.x || posStart.x > otherPosEnd.x || posEnd.y < otherPosStart.y || posStart.y > otherPosEnd.y)
	{
		return false;
	}

	return true;
}

void CollisionComponent::ComponentHit(Actor* otherActor)
{
	// ��������Ʈ ȣ��.
	if(OnComponentHit.isBound())
	{
		OnComponentHit.broadCast(otherActor);
	}
}

void CollisionComponent::SetOwner(Actor* inActor)
{
	owner = inActor;
}

Vector2 CollisionComponent::GetMax() const
{
	Vector2 p = position;
	Vector2 s = size;
	return p + s;
}
