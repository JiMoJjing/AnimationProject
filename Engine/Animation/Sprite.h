#pragma once
#pragma warning(disable: 4251)

#include "Core.h"
#include "Math/Vector2.h"



class ENGINE_API Sprite
{
public:
	// �̹��� vector�� �޾� ����.
	Sprite(const std::vector<std::string>& spriteSheet, const Vector2& start, const Vector2& end);

	~Sprite() = default;

	// �������� �޾� Draw.
	void Draw(const Vector2& position);

	// �̹����� ũ�� Getter.
	inline Vector2 GetSize() const { return size; }


private:
	// �̹��� ���� vector.
	std::vector<std::string> image;

	// �̹����� ũ��.
	Vector2 size;
};