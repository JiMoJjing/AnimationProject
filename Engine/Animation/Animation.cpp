#include "PreCompiledHeader.h"
#include "Animation.h"

#include "Engine/Timer.h"


Animation::Animation()
{
	// 클립 마다 각자의 타이머 소유.
	timer = new Timer(frameTime);
}

Animation::~Animation()
{
	for (Sprite* sprite : sprites)
	{
		SafeDelete(sprite);
	}

	SafeDelete(timer);
}

void Animation::Update(float deltaTime)
{
	// 재생중일 때만 프레임 업데이트
	if(bIsPlaying)
	{
		timer->Update(deltaTime);

		if (timer->IsTimeOut())
		{
			++frameIndex;
			frameIndex %= frameMaxIndex;
			timer->Reset();
		}
	}
}

void Animation::Draw(const Vector2& position)
{
	// 프레임에 해당하는 스프라이트 Draw 콜.
	if(sprites.size() > 0)
	{
		sprites[frameIndex]->Draw(position);
	}
}

void Animation::AddSprite(const std::vector<std::string>& spriteSheet, const Vector2& start, const Vector2& end)
{
	// 생성해서 추가.
	Sprite* newSprite = new Sprite(spriteSheet, start, end);
	AddSprite(newSprite);
}

void Animation::AddSprite(Sprite* newSprite)
{
	// vector에 넣기.
	sprites.push_back(newSprite);

	// 최대 프레임 값 갱신.
	frameMaxIndex = (int)sprites.size();
}

void Animation::Play()
{
	// 처음부터 재생.
	frameIndex = 0;
	bIsPlaying = true;
}

void Animation::Stop()
{
	bIsPlaying = false;
}

void Animation::SetFrameTime(float frameTime)
{
	// 프레임 간격 설정.
	this->frameTime = frameTime;
	timer->SetTime(frameTime);
}
