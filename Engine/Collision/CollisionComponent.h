#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4172)

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"

class Actor;

// �Լ� ������ ����.
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

	// ������Ʈ.
	virtual void Update(float deltaTime);
	
	// Draw
	void Draw();

	// �浹 �˻�.
	bool Intersect(CollisionComponent* other);

	// �浹 �� ����.
	void ComponentHit(Actor* otherActor);

	// Owner ����.
	void SetOwner(Actor* inActor);

	// Owner Getter.
	Actor* GetOwner() { return owner; }

	// Color ����.
	void SetCollisionColor(Color inColor) { color = inColor; }

	// Position Getter.
	inline Vector2 GetPosition() const { return position; }

	// Size Getter.
	inline Vector2 GetSize() const { return size; }

	// Position + Size Getter.
	Vector2 GetMax() const;

private:
	// ���� ����.
	Actor* owner = nullptr;

	// ũ��.
	Vector2 size = Vector2(0, 0);

	// ��ġ.
	Vector2 position = Vector2(0, 0);

	// DrawColor.
	Color color = Color::Green;

public:
	// ��������Ʈ ����.
	FOnComponentHit OnComponentHit;
};