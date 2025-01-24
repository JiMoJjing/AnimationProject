#pragma once

#pragma warning(disable : 4172)

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"

#include "Sprite.h"
#include "Animation.h"

class Actor;

class ENGINE_API AnimInstance : public RTTI
{
	RTTI_DECLARATIONS(AnimInstance, RTTI)

public:
	// Sprite Sheet ���� ���丮�� Offset ���� ���丮�� �޾� Clip ��Ƶ� Animation ����.
	AnimInstance(const std::string& SpriteFileDirectory, const std::string& offsetFileDirectory, int sizeX, int sizeY);
	virtual ~AnimInstance();

	// AnimInstance�� ������ �� ȣ��.
	virtual void NativeInitializeAnimation();

	// Update.
	virtual void NativeUpdateAnimation(float deltaTime);

	void Draw();

	// Sprite ���� ũ��.
	void SetSpriteSize(const Vector2& offset) { spriteSize = offset; }

	// Owner ����.
	void SetOwner(Actor* inActor) { owner = inActor; }

	// Owner Getter.
	Actor* GetOwner() { return owner; }

	// Set CurrentClip.
	void SetCurrentAnimation(int currentIndex);

private:
	// Owner.
	Actor* owner = nullptr;

	// Clip �����̳�.
	std::vector<Animation*> animations;

	// ���� Clip.
	Animation* currentAnimation = nullptr;

	// Sprite Read Offset.
	Vector2 spriteSize = Vector2(33, 21);

	// DrawPosition.
	Vector2 drawPosition = Vector2(0, 0);

	// �ܻ� ó���� buffer
	std::vector<std::string> emptySpriteBuffer;

	// �ܻ� ó���� Draw position.
	Vector2 previousDrawPosition = Vector2(0, 0);
};