#pragma once
#include "Actor/Actor.h"


class AnimInstance;
class CollisionComponent;

class ENGINE_API Character : public Actor
{
	RTTI_DECLARATIONS(Character, Actor)

public:
	Character();
	Character(int x, int y);
	virtual ~Character();

	// Update.
	virtual void Update(float deltaTime) override;

	// Draw.
	virtual void Draw() override;

	// 컨트롤러에서 움직임 입력할 때 호출 될 함수.
	void Move(const Vector2& inputValue);

	// 애니메이션 setter.
	void SetCharacterAnimInstance(AnimInstance* newAnimation);
	AnimInstance* GetCharacterAnimInstance() { return characterAnimInstance; }

	// 이동 속도 Getter, Setter.
	inline float GetMoveSpeed() { return moveSpeed; } 
	void SetMoveSpeed(float newMoveSpeed) { moveSpeed = newMoveSpeed; }

	// 캐릭터 뱡향 Getter.
	Vector2 GetDirection() { return direction; }

	// 캐릭터 이동여부 Getter.
	bool IsCharacterMove() { return bIsCharacterMove; }

	// 콜리전의 OnComponentHit에 바인드 할 함수.
	virtual void OnComponentHit(Actor* otherActor) override;

	// 콜리전 Getter.
	CollisionComponent* GetCollisionComponent() { return collisionComponent; }

private:
	// 캐릭터의 애니메이션.
	AnimInstance* characterAnimInstance = nullptr;

	// 캐릭터 크기.
	Vector2 characterSize = Vector2(33, 21);

	// 이동 입력 Vector2.
	Vector2 moveInput;

	// 이동 속도.
	float moveSpeed = 100.f;

	// 캐릭터 방향.
	Vector2 direction = Vector2(0, 1);

	// 캐릭터 이동 여부.
	bool bIsCharacterMove = false;

	// 콜리전.
	CollisionComponent* collisionComponent = nullptr;
};