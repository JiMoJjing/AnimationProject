#pragma once
#pragma warning(disable: 4172)

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"

class ENGINE_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor();
	virtual ~Actor();

	virtual void Update(float deltaTime);
	virtual void Draw();

	// Getter/ Setter
	virtual void SetPosition(const Vector2& newPosition);
	inline Vector2 Position() const;

	inline bool IsActive() const { return isActive && !isExpired; }
	inline bool IsExpired() const { return isExpired; }
	inline void SetActive(bool active) { isActive = active; }
	inline void Destroy() { isExpired = true; }

	virtual void OnComponentHit(Actor* otherActor);
	
protected:
	// ������ ��ġ
	Vector2 position = Vector2(0, 0);

	// Ȱ��ȭ ���������� ��Ÿ���� ����
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired;
};

