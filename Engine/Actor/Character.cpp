#include "PreCompiledHeader.h"
#include "Character.h"

#include "Engine/Engine.h"
#include "Animation/AnimInstance.h"
#include "Collision/CollisionComponent.h"

Character::Character()
{
	// �ݸ��� ����.
	collisionComponent = new CollisionComponent(position, characterSize);
	
	// ���� ����.
	collisionComponent->SetOwner(this);
	//collisionComponent->OnComponentHit.bindFunction(this, static_cast<CallBack>(&Character::OnComponentHit));

	// �Լ� ���ε�
	collisionComponent->OnComponentHit.bindFunction(this, &Actor::OnComponentHit);

	// �ݸ��� ���.
	Engine::Get().AddCollisionComponent(collisionComponent);
}

Character::Character(int x, int y)
{
	position = Vector2(x, y);

	// �ݸ��� ����.
	collisionComponent = new CollisionComponent(position, characterSize);

	// ���� ����.
	collisionComponent->SetOwner(this);
	//collisionComponent->OnComponentHit.bindFunction(this, static_cast<CallBack>(&Character::OnComponentHit));

	// �Լ� ���ε�
	collisionComponent->OnComponentHit.bindFunction(this, &Actor::OnComponentHit);

	// �ݸ��� ���.
	Engine::Get().AddCollisionComponent(collisionComponent);
}

Character::~Character()
{
	delete characterAnimInstance;
	delete collisionComponent;
}

void Character::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// �ִϸ��̼� ������Ʈ.
	if (characterAnimInstance != nullptr)
	{
		characterAnimInstance->NativeUpdateAnimation(deltaTime);
	}

	// �ݸ��� ������Ʈ.
	if (collisionComponent != nullptr)
	{
		collisionComponent->Update(deltaTime);
	}

	// ��ǲ �� ó��
	// �Է� �� ������ �̵� �Ÿ� ���.
	Vector2 newPosition(0, 0);
	moveInput.x = (int)(moveInput.x * moveSpeed * deltaTime);
	moveInput.y = (int)(moveInput.y * moveSpeed * deltaTime * 0.75f);
	newPosition = position + moveInput;
	moveInput = Vector2(0, 0);

	// @Todo: ������ �浹 ó��.
	//if (false)
	//{
	//	return;
	//}

	// �̵��ߴ��� �˻��ؼ� ���� ���.
	if (newPosition != position)
	{
		direction = newPosition - position;
		direction.Normalize();
	}

	// �̵� ���� ����.
	bIsCharacterMove = position != newPosition;

	// �̵� ó��.
	position = newPosition;
}

void Character::Draw()
{
	Super::Draw();

	if(characterAnimInstance != nullptr)
	{
		characterAnimInstance->Draw();
	}
}

void Character::Move(const Vector2& inputValue)
{
	moveInput = inputValue;
}

void Character::SetCharacterAnimInstance(AnimInstance* newAnimation)
{
	characterAnimInstance = newAnimation;
	
	if (characterAnimInstance != nullptr)
	{
		characterAnimInstance->SetOwner(this);
		characterAnimInstance->NativeInitializeAnimation();
	}
}

void Character::OnComponentHit(Actor* otherActor)
{
	Super::OnComponentHit(otherActor);

	collisionComponent->SetCollisionColor(Color::Red);
}
