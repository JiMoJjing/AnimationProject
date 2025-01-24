#include "PreCompiledHeader.h"
#include "Sprite.h"
#include "Engine/Engine.h"

Sprite::Sprite(const std::vector<std::string>& spriteSheet, const Vector2& start, const Vector2& end)
{
	// SpriteSheet���� start, end ������� ������ ��������
	for (int ix = start.y - 1; ix < min(end.y, spriteSheet.size()); ++ix)
	{
		std::string str = "";
		for (int jx = start.x - 1; jx < min(end.x, spriteSheet[ix].size()); ++jx)
		{
			// %�� ��� �� %% �� �ؾ� ����� ��µ�.
			if (spriteSheet[ix][jx] == '%')
			{
				str += "%%";
				continue;
			}
			str += spriteSheet[ix][jx];
		}
		image.push_back(str);
	}

	// ũ�� ����.
	if(this->image.empty() == false)
	{
		size.x = (int)this->image[0].length();
		size.y = (int)this->image.size();
	}
}

void Sprite::Draw(const Vector2& position)
{
	// �������� �޾Ƽ� �� ��ġ�� Log �Լ��� ����Ͽ� �׸���.
	for (int ix = 0; ix < image.size(); ++ix)
	{
		Vector2 drawPositon = position;
		drawPositon.y += ix;
		Engine::Get().SetCursorPosition(drawPositon);
		Log(image[ix]);
	}

	// �� �׷����� Ŀ�� ��ġ ����.
	//Engine::Get().SetCursorPosition(0, 0);
}
