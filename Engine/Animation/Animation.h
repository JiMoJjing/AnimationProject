#pragma once
#pragma warning(disable: 4251)


#include "Core.h"
#include "Math/Vector2.h"
#include "Animation/Sprite.h"

class Timer;

class ENGINE_API Animation
{
public:
	Animation();
	~Animation();

	// ������Ʈ �Լ�.
	void Update(float deltaTime);

	// Draw �Լ�.
	void Draw(const Vector2& position);

	// ��������Ʈ �߰�.
	void AddSprite(const std::vector<std::string>& spriteSheet, const Vector2& start, const Vector2& end);
	void AddSprite(Sprite* newSprite);

	// Ŭ�� ���.
	void Play();

	// Ŭ�� ����.
	void Stop();

	// ������ �ð� Setter.
	void SetFrameTime(float frameTime);

private:
	// ��������Ʈ ���� �����̳�.
	std::vector<Sprite*> sprites;

	// Timer.
	Timer* timer;

	// ������ �ð�.
	float frameTime = 0.2f;

	// ������ �ε���.
	int frameIndex = 0;

	// ������ �ε��� �ƽ� ��.
	int frameMaxIndex = 0;

	// Clip ��� ����.
	bool bIsPlaying = false;
};