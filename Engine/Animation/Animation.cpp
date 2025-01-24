#include "PreCompiledHeader.h"
#include "Animation.h"

#include "Engine/Timer.h"


Animation::Animation()
{
	// Ŭ�� ���� ������ Ÿ�̸� ����.
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
	// ������� ���� ������ ������Ʈ
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
	// �����ӿ� �ش��ϴ� ��������Ʈ Draw ��.
	if(sprites.size() > 0)
	{
		sprites[frameIndex]->Draw(position);
	}
}

void Animation::AddSprite(const std::vector<std::string>& spriteSheet, const Vector2& start, const Vector2& end)
{
	// �����ؼ� �߰�.
	Sprite* newSprite = new Sprite(spriteSheet, start, end);
	AddSprite(newSprite);
}

void Animation::AddSprite(Sprite* newSprite)
{
	// vector�� �ֱ�.
	sprites.push_back(newSprite);

	// �ִ� ������ �� ����.
	frameMaxIndex = (int)sprites.size();
}

void Animation::Play()
{
	// ó������ ���.
	frameIndex = 0;
	bIsPlaying = true;
}

void Animation::Stop()
{
	bIsPlaying = false;
}

void Animation::SetFrameTime(float frameTime)
{
	// ������ ���� ����.
	this->frameTime = frameTime;
	timer->SetTime(frameTime);
}
