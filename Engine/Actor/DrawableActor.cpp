#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"
#include <string>
DrawableActor::DrawableActor(const char* image)
	: Actor()
{
	size_t length = strlen(image) + 1;
	this->image = new char[length];

	strcpy_s(this->image, length, image);

	// 너비 설정.
	width = (int)strlen(image);
}

DrawableActor::~DrawableActor()
{
	if(image != nullptr)
	{
		delete[] image;
		image = nullptr;
	}
}

void DrawableActor::Draw()
{
	Super::Draw();

	// 색상 설정.
	SetColor(color);

	// 그리기.
	// 1단계: 콘솔 좌표 옮기기.
	Engine::Get().SetCursorPosition(position);

	// 2단계: 그리기 ( 콘솔 출력 ).
	Log(image);

	// 색상 복구.
	SetColor(Color::White);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	//// 이전 프레임 위치 먼저 지우기.
	//Engine::Get().SetCursorPosition(position);
	//Log(" ");

	// 위치 이동.
	Super::SetPosition(newPosition);
}

bool DrawableActor::Intersect(const DrawableActor& other)
{
	// AABB(Axis Aligned Bounding Box).

	// 내 x좌표 최소/최대.
	int min = position.x;
	int max = position.x + width;

	// 다른 액터의 x좌표 최소/최대.
	int otherMin = other.position.x;
	int otherMax = other.position.x + other.width;

	// 다른 액터의 왼쪽 끝 위치가 내 오른쪽 끝 위치를 벗어나면 충돌 안함.
	if (otherMin > max)
	{
		return false;
	}

	// 다른 액터의 오른쪽 끝 위치가 내 왼쪽 끝 위치를 벗어나면 충돌 안함.
	if (otherMax < min)
	{
		return false;
	}

	// 위의 두 경우가 아니라면 (x좌표는 서로 겹침), y위치 비교.
	return position.y == other.position.y;
}
