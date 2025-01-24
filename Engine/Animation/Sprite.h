#pragma once
#pragma warning(disable: 4251)

#include "Core.h"
#include "Math/Vector2.h"



class ENGINE_API Sprite
{
public:
	// 이미지 vector를 받아 생성.
	Sprite(const std::vector<std::string>& spriteSheet, const Vector2& start, const Vector2& end);

	~Sprite() = default;

	// 포지션을 받아 Draw.
	void Draw(const Vector2& position);

	// 이미지의 크기 Getter.
	inline Vector2 GetSize() const { return size; }


private:
	// 이미지 저장 vector.
	std::vector<std::string> image;

	// 이미지의 크기.
	Vector2 size;
};