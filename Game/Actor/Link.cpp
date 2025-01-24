#include "Link.h"
#include "Engine/Engine.h"
#include "Animation/LinkAnimInstance.h"

Link::Link()
	: Character()
{
	// 애니메이션 생성 및 set.
	LinkAnimInstance* linkAnimInstance = new LinkAnimInstance("../Assets/Character/LinkR.txt", "../Assets/Offset/LinkSpriteOffset.txt", 33, 21);
	if (linkAnimInstance)
	{
		SetCharacterAnimInstance(linkAnimInstance);
	}
	SetMoveSpeed(200.f);
}

Link::Link(int x, int y)
	: Character(x, y)
{
	// 애니메이션 생성 및 set.
	LinkAnimInstance* linkAnimInstance = new LinkAnimInstance("../Assets/Character/LinkR.txt", "../Assets/Offset/LinkSpriteOffset.txt", 33, 21);
	if (linkAnimInstance)
	{
		SetCharacterAnimInstance(linkAnimInstance);
	}
	SetMoveSpeed(200.f);
}

Link::~Link()
{
}

void Link::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// direction 기반으로 currentMoveState 설정.
	Vector2 direction = GetDirection();
	static int moveState = 0;

	// 방향에 따라 방향 숫자 더함.
	if (direction.y == 1)
	{
		moveState = 0;
	}
	else if (direction.y == -1)
	{
		moveState = 2;
	}
	else if (direction.x == 1)
	{
		moveState = 3;
	}
	else if (direction.x == -1)
	{
		moveState = 1;
	}

	// 0 ~ 3 : Idle // 4 ~ 7 : Move

	// 움직임상태면 4 더함.
	if (IsCharacterMove())
	{
		moveState += 4;
	}
	moveState %= 8;

	SetMoveState(static_cast<EMoveState>(moveState));
}

void Link::Draw()
{
	Super::Draw();
}

void Link::SetMoveState(EMoveState newMoveState)
{
	// 변화 없으면 얼리 리턴.
	if (currentMoveState == newMoveState)
	{
		return;
	}

	// currentMoveState 바꾸기
	currentMoveState = newMoveState;
}
