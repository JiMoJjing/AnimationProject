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

	// ��Ʈ�ѷ����� ������ �Է��� �� ȣ�� �� �Լ�.
	void Move(const Vector2& inputValue);

	// �ִϸ��̼� setter.
	void SetCharacterAnimInstance(AnimInstance* newAnimation);
	AnimInstance* GetCharacterAnimInstance() { return characterAnimInstance; }

	// �̵� �ӵ� Getter, Setter.
	inline float GetMoveSpeed() { return moveSpeed; } 
	void SetMoveSpeed(float newMoveSpeed) { moveSpeed = newMoveSpeed; }

	// ĳ���� ���� Getter.
	Vector2 GetDirection() { return direction; }

	// ĳ���� �̵����� Getter.
	bool IsCharacterMove() { return bIsCharacterMove; }

	// �ݸ����� OnComponentHit�� ���ε� �� �Լ�.
	virtual void OnComponentHit(Actor* otherActor) override;

	// �ݸ��� Getter.
	CollisionComponent* GetCollisionComponent() { return collisionComponent; }

private:
	// ĳ������ �ִϸ��̼�.
	AnimInstance* characterAnimInstance = nullptr;

	// ĳ���� ũ��.
	Vector2 characterSize = Vector2(33, 21);

	// �̵� �Է� Vector2.
	Vector2 moveInput;

	// �̵� �ӵ�.
	float moveSpeed = 100.f;

	// ĳ���� ����.
	Vector2 direction = Vector2(0, 1);

	// ĳ���� �̵� ����.
	bool bIsCharacterMove = false;

	// �ݸ���.
	CollisionComponent* collisionComponent = nullptr;
};