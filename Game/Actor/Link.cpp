#include "Link.h"
#include "Engine/Engine.h"
#include "Animation/LinkAnimInstance.h"

Link::Link()
	: Character()
{
	// �ִϸ��̼� ���� �� set.
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
	// �ִϸ��̼� ���� �� set.
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

	// direction ������� currentMoveState ����.
	Vector2 direction = GetDirection();
	static int moveState = 0;

	// ���⿡ ���� ���� ���� ����.
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

	// �����ӻ��¸� 4 ����.
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
	// ��ȭ ������ �� ����.
	if (currentMoveState == newMoveState)
	{
		return;
	}

	// currentMoveState �ٲٱ�
	currentMoveState = newMoveState;
}
