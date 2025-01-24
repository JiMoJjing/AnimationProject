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
	// 액터의 위치
	Vector2 position = Vector2(0, 0);

	// 활성화 상태인지를 나타내는 변수
	bool isActive;

	// 액터의 제거 요청이 됐는지 여부를 나타내는 변수
	bool isExpired;
};

