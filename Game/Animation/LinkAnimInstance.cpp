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

	// Link 레퍼런스 캐싱.
	Link* link = dynamic_cast<Link*>(GetOwner());
	if (link != nullptr)
	{
		linkReference = link;
	}
}

void LinkAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	// nullptr 체크.
	if (linkReference == nullptr)
	{
		return;
	}

	// MoveState 업데이트.
	int newMoveState = linkReference->GetMoveState();
	if (newMoveState != currentMoveState)
	{
		currentMoveState = newMoveState;
		SetCurrentAnimation(currentMoveState);
	}
}
