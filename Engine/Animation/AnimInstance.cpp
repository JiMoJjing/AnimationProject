#include "PreCompiledHeader.h"
#include "AnimInstance.h"
#include "Engine/Engine.h"

#include "Actor/Actor.h"

AnimInstance::AnimInstance(const std::string& SpriteFileDirectory, const std::string& offsetFileDirectory, int sizeX, int sizeY)
	: spriteSize(sizeX, sizeY)
{
	// Sprite File ĳ��.
	FILE* file = nullptr;
	fopen_s(&file, SpriteFileDirectory.c_str(), "rb");

	if (file == nullptr)
	{
		std::cout << "���� ���� ����.\n";
		__debugbreak();
		return;
	}

	// ���� �� �پ� �б�.
	std::vector<std::string> spriteBuffers;

	char buffer[1024];
	while (fgets(buffer, 1024, file) != nullptr)
	{
		spriteBuffers.emplace_back(buffer);
	}

	fclose(file);
	file = nullptr;

	// Offset File ĳ��.
	fopen_s(&file, offsetFileDirectory.c_str(), "r");

	if (file == nullptr)
	{
		std::cout << "���� ���� ����.\n";
		__debugbreak();
		return;
	}

	// ���� �� �پ� �б�.
	std::vector<std::string> offsetBuffers;
	while (fgets(buffer, 1024, file) != nullptr)
	{
		offsetBuffers.emplace_back(buffer);
	}

	// �о�� �������� �̿��ؼ� Sprite ����.
	// ������ Sprite�����ؼ� Clip �� Add.
	if (!offsetBuffers.empty())
	{
		for (const std::string& str : offsetBuffers)
		{
			int moveState = 0, startX = 0, startY = 0, endX = 0, endY = 0;

			if (sscanf_s(str.c_str(), "%d %d %d", &moveState, &startX, &startY) == 3)
			{
				endX = startX + spriteSize.x;
				endY = startY + spriteSize.y;

				if (animations.size() == moveState)
				{
					animations.push_back(new Animation());
				}
				animations[moveState]->AddSprite(spriteBuffers, Vector2(startX, startY), Vector2(endX, endY));
			}
		}
	}

	fclose(file);
	file = nullptr;

	// emptyStringBuffer �ʱ�ȭ.
	for (int ix = 0; ix < spriteSize.y + 2; ++ix)
	{
		emptySpriteBuffer.push_back(std::string(spriteSize.x + 2, ' '));
	}
}

AnimInstance::~AnimInstance()
{
	currentAnimation = nullptr;

	for (Animation* animation : animations)
	{
		SafeDelete(animation);
	}
}

void AnimInstance::NativeInitializeAnimation()
{
	// currentAnimation �ʱ�ȭ.
	if (animations.size() > 0)
	{
		SetCurrentAnimation(0);
	}
}

void AnimInstance::NativeUpdateAnimation(float deltaTime)
{
	// position ������Ʈ, ���� ��ġ�� ����.
	if (owner != nullptr)
	{
		previousDrawPosition = drawPosition;
		drawPosition = owner->Position();
	}
	if (currentAnimation != nullptr)
	{
		currentAnimation->Update(deltaTime);
	}
}

void AnimInstance::Draw()
{
	// ĳ���� �̵� ���� �˻� �� �ܻ� ó��.
	if (drawPosition != previousDrawPosition)
	{
		for (int ix = 0; ix < emptySpriteBuffer.size(); ++ix)
		{
			Vector2 positon = previousDrawPosition;
			positon.y += ix;
			Engine::Get().SetCursorPosition(positon);
			Log(emptySpriteBuffer[ix]);
		}
	}
	// �ܻ� ó�� �� Draw ��.
	if (currentAnimation != nullptr)
	{
		currentAnimation->Draw(drawPosition);
	}
}

void AnimInstance::SetCurrentAnimation(int currentIndex)
{
	if (currentIndex >= animations.size())
	{
		currentIndex = 0;
	}

	if (currentAnimation != nullptr)
	{
		currentAnimation->Stop();
	}

	currentAnimation = animations[currentIndex];
	if (currentAnimation != nullptr)
	{
		currentAnimation->Play();
	}
}
