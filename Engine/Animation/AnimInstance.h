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
	// Sprite Sheet 파일 디렉토리와 Offset 파일 디렉토리를 받아 Clip 모아둔 Animation 생성.
	AnimInstance(const std::string& SpriteFileDirectory, const std::string& offsetFileDirectory, int sizeX, int sizeY);
	virtual ~AnimInstance();

	// AnimInstance가 생성될 때 호출.
	virtual void NativeInitializeAnimation();

	// Update.
	virtual void NativeUpdateAnimation(float deltaTime);

	void Draw();

	// Sprite 추출 크기.
	void SetSpriteSize(const Vector2& offset) { spriteSize = offset; }

	// Owner 설정.
	void SetOwner(Actor* inActor) { owner = inActor; }

	// Owner Getter.
	Actor* GetOwner() { return owner; }

	// Set CurrentClip.
	void SetCurrentAnimation(int currentIndex);

private:
	// Owner.
	Actor* owner = nullptr;

	// Clip 컨테이너.
	std::vector<Animation*> animations;

	// 현재 Clip.
	Animation* currentAnimation = nullptr;

	// Sprite Read Offset.
	Vector2 spriteSize = Vector2(33, 21);

	// DrawPosition.
	Vector2 drawPosition = Vector2(0, 0);

	// 잔상 처리용 buffer
	std::vector<std::string> emptySpriteBuffer;

	// 잔상 처리용 Draw position.
	Vector2 previousDrawPosition = Vector2(0, 0);
};