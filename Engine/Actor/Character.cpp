#include "PreCompiledHeader.h"
#include "Character.h"

#include "Engine/Engine.h"
#include "Animation/AnimInstance.h"
#include "Collision/CollisionComponent.h"

Character::Character()
{
	// 콜리전 생성.
	collisionComponent = new CollisionComponent(position, characterSize);
	
	// 오너 설정.
	collisionComponent->SetOwner(this);
	//collisionComponent->OnComponentHit.bindFunction(this, static_cast<CallBack>(&Character::OnComponentHit));

	// 함수 바인드
	collisionComponent->OnComponentHit.bindFunction(this, &Actor::OnComponentHit);

	// 콜리전 등록.
	Engine::Get().AddCollisionComponent(collisionComponent);
}

Character::Character(int x, int y)
{
	position = Vector2(x, y);

	// 콜리전 생성.
	collisionComponent = new CollisionComponent(position, characterSize);

	// 오너 설정.
	collisionComponent->SetOwner(this);
	//collisionComponent->OnComponentHit.bindFunction(this, static_cast<CallBack>(&Character::OnComponentHit));

	// 함수 바인드
	collisionComponent->OnComponentHit.bindFunction(this, &Actor::OnComponentHit);

	// 콜리전 등록.
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

	// 애니메이션 업데이트.
	if (characterAnimInstance != nullptr)
	{
		characterAnimInstance->NativeUpdateAnimation(deltaTime);
	}

	// 콜리전 업데이트.
	if (collisionComponent != nullptr)
	{
		collisionComponent->Update(deltaTime);
	}

	// 인풋 값 처리
	// 입력 값 적용한 이동 거리 계산.
	Vector2 newPosition(0, 0);
	moveInput.x = (int)(moveInput.x * moveSpeed * deltaTime);
	moveInput.y = (int)(moveInput.y * moveSpeed * deltaTime * 0.75f);
	newPosition = position + moveInput;
	moveInput = Vector2(0, 0);

	// @Todo: 움직임 충돌 처리.
	//if (false)
	//{
	//	return;
	//}

	// 이동했는지 검사해서 방향 계산.
	if (newPosition != position)
	{
		direction = newPosition - position;
		direction.Normalize();
	}

	// 이동 여부 변경.
	bIsCharacterMove = position != newPosition;

	// 이동 처리.
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
