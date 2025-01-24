#include "LinkAnimInstance.h"
#include "Actor/Link.h"

LinkAnimInstance::LinkAnimInstance(const std::string& SpriteFileDirectory, const std::string& offsetFileDirectory, int sizeX, int sizeY)
	: AnimInstance(SpriteFileDirectory, offsetFileDirectory, sizeX, sizeY)
{

}

LinkAnimInstance::~LinkAnimInstance()
{
}

void LinkAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Link ���۷��� ĳ��.
	Link* link = dynamic_cast<Link*>(GetOwner());
	if (link != nullptr)
	{
		linkReference = link;
	}
}

void LinkAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	// nullptr üũ.
	if (linkReference == nullptr)
	{
		return;
	}

	// MoveState ������Ʈ.
	int newMoveState = linkReference->GetMoveState();
	if (newMoveState != currentMoveState)
	{
		currentMoveState = newMoveState;
		SetCurrentAnimation(currentMoveState);
	}
}
