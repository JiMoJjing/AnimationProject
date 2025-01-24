#pragma once
//#pragma warning(disable : 4172)

#include "Animation/AnimInstance.h"

class Link;
class LinkAnimInstance : public AnimInstance
{
	RTTI_DECLARATIONS(LinkAnimInstance, AnimInstance)

public:
	LinkAnimInstance(const std::string& SpriteFileDirectory, const std::string& offsetFileDirectory, int sizeX, int sizeY);
	virtual ~LinkAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;

private:
	// 링크 레퍼런스 캐싱.
	Link* linkReference = nullptr;

	// MoveState 저장.
	int currentMoveState = 0;
};