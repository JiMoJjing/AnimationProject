#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4172)

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"

class Actor;

// 함수 포인터 선언.
using CallBack = void (Actor::*)(Actor* /* otherActor */);

struct FOnComponentHit
{
public:
	void bindFunction(Actor* object, CallBack function)
	{
		actor = object;
		callBackFunction = function;
	}

	void broadCast(Actor* otherActor)
	{
		if (actor != nullptr)
		{
			(actor->*callBackFunction)(otherActor);
		}
	}
	bool isBound()
	{
		return actor != nullptr;
	}

public:
	Actor* actor = nullptr;
	CallBack callBackFunction = nullptr;
};

class ENGINE_API CollisionComponent : public RTTI
{
	RTTI_DECLARATIONS(CollisionComponent, RTTI)

public:
	CollisionComponent(const Vector2& position, const Vector2& size);
	CollisionComponent(int positionX, int positionY, int sizeX, int sizeY);
	virtual ~CollisionComponent();

	// 업데이트.
	virtual void Update(float deltaTime);
	
	// Draw
	void Draw();

	// 충돌 검사.
	bool Intersect(CollisionComponent* other);

	// 충돌 시 실행.
	void ComponentHit(Actor* otherActor);

	// Owner 설정.
	void SetOwner(Actor* inActor);

	// Owner Getter.
	Actor* GetOwner() { return owner; }

	// Color 설정.
	void SetCollisionColor(Color inColor) { color = inColor; }

	// Position Getter.
	inline Vector2 GetPosition() const { return position; }

	// Size Getter.
	inline Vector2 GetSize() const { return size; }

	// Position + Size Getter.
	Vector2 GetMax() const;

private:
	// 오너 액터.
	Actor* owner = nullptr;

	// 크기.
	Vector2 size = Vector2(0, 0);

	// 위치.
	Vector2 position = Vector2(0, 0);

	// DrawColor.
	Color color = Color::Green;

public:
	// 델리게이트 선언.
	FOnComponentHit OnComponentHit;
};