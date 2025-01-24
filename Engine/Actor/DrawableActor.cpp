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

	// �ʺ� ����.
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

	// ���� ����.
	SetColor(color);

	// �׸���.
	// 1�ܰ�: �ܼ� ��ǥ �ű��.
	Engine::Get().SetCursorPosition(position);

	// 2�ܰ�: �׸��� ( �ܼ� ��� ).
	Log(image);

	// ���� ����.
	SetColor(Color::White);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	//// ���� ������ ��ġ ���� �����.
	//Engine::Get().SetCursorPosition(position);
	//Log(" ");

	// ��ġ �̵�.
	Super::SetPosition(newPosition);
}

bool DrawableActor::Intersect(const DrawableActor& other)
{
	// AABB(Axis Aligned Bounding Box).

	// �� x��ǥ �ּ�/�ִ�.
	int min = position.x;
	int max = position.x + width;

	// �ٸ� ������ x��ǥ �ּ�/�ִ�.
	int otherMin = other.position.x;
	int otherMax = other.position.x + other.width;

	// �ٸ� ������ ���� �� ��ġ�� �� ������ �� ��ġ�� ����� �浹 ����.
	if (otherMin > max)
	{
		return false;
	}

	// �ٸ� ������ ������ �� ��ġ�� �� ���� �� ��ġ�� ����� �浹 ����.
	if (otherMax < min)
	{
		return false;
	}

	// ���� �� ��찡 �ƴ϶�� (x��ǥ�� ���� ��ħ), y��ġ ��.
	return position.y == other.position.y;
}
