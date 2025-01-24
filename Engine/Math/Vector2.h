#pragma once
#include "Core.h"

class ENGINE_API Vector2
{
public:
	Vector2(int x = 0, int y = 0);
	~Vector2() = default;

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);
	Vector2 operator=(const Vector2& other);

	void Normalize();

public:
	// ÁÂÇ¥ °ª
	int x = 0;
	int y = 0;
};