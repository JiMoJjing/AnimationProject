#pragma once

#include "Actor/Character.h"

// 애니메이션 구분 위한 움직임 상태 정의.
enum class EMoveState
{
	None = -1,
	Idle_Down = 0,
	Idle_Left = 1,
	Idle_Up = 2,
	Idle_Right = 3,
	Move_Down = 4,
	Move_Left = 5,
	Move_Up = 6,
	Move_Right = 7
};

class Link : public Character
{
	RTTI_DECLARATIONS(Link, Character)

public:
	Link();
	Link(int x, int y);
	virtual ~Link();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	inline int GetMoveState() const { return static_cast<int>(currentMoveState); }

private:
	void SetMoveState(EMoveState newMoveState);
 
private:
	EMoveState currentMoveState = EMoveState::Idle_Down;

};