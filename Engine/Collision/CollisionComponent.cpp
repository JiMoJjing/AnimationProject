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
	// 위치 업데이트.
	if (owner != nullptr)
	{
		position = owner->Position();
	}
}

void CollisionComponent::Draw()
{
	// 색깔 설정.
	SetColor(color);
	
	// 그리기.
	for (int ix = 0; ix < size.y; ++ix)
	{
		// 커서 위치 설정.
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

	// 색깔 리셋.
	SetColor(Color::White);
}

bool CollisionComponent::Intersect(CollisionComponent* other)
{
	// 시작점과 끝점.
	Vector2 posStart = this->GetPosition();
	Vector2 posEnd = posStart + this->GetSize();

	Vector2 otherPosStart = other->GetPosition();
	Vector2 otherPosEnd = otherPosStart + other->GetSize();

	// 충돌 검사.
	if (posEnd.x < otherPosStart.x || posStart.x > otherPosEnd.x || posEnd.y < otherPosStart.y || posStart.y > otherPosEnd.y)
	{
		return false;
	}

	return true;
}

void CollisionComponent::ComponentHit(Actor* otherActor)
{
	// 델리게이트 호출.
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
