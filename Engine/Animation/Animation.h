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

	// 업데이트 함수.
	void Update(float deltaTime);

	// Draw 함수.
	void Draw(const Vector2& position);

	// 스프라이트 추가.
	void AddSprite(const std::vector<std::string>& spriteSheet, const Vector2& start, const Vector2& end);
	void AddSprite(Sprite* newSprite);

	// 클립 재생.
	void Play();

	// 클립 멈춤.
	void Stop();

	// 프레임 시간 Setter.
	void SetFrameTime(float frameTime);

private:
	// 스프라이트 담을 컨테이너.
	std::vector<Sprite*> sprites;

	// Timer.
	Timer* timer;

	// 프레임 시간.
	float frameTime = 0.2f;

	// 프레임 인덱스.
	int frameIndex = 0;

	// 프레임 인덱스 맥스 값.
	int frameMaxIndex = 0;

	// Clip 재생 여부.
	bool bIsPlaying = false;
};