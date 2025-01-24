#include "PreCompiledHeader.h"
#include "Sprite.h"
#include "Engine/Engine.h"

Sprite::Sprite(const std::vector<std::string>& spriteSheet, const Vector2& start, const Vector2& end)
{
	// SpriteSheet에서 start, end 기반으로 데이터 가져오기
	for (int ix = start.y - 1; ix < min(end.y, spriteSheet.size()); ++ix)
	{
		std::string str = "";
		for (int jx = start.x - 1; jx < min(end.x, spriteSheet[ix].size()); ++jx)
		{
			// %는 출력 시 %% 로 해야 제대로 출력됨.
			if (spriteSheet[ix][jx] == '%')
			{
				str += "%%";
				continue;
			}
			str += spriteSheet[ix][jx];
		}
		image.push_back(str);
	}

	// 크기 저장.
	if(this->image.empty() == false)
	{
		size.x = (int)this->image[0].length();
		size.y = (int)this->image.size();
	}
}

void Sprite::Draw(const Vector2& position)
{
	// 포지션을 받아서 그 위치에 Log 함수를 사용하여 그리기.
	for (int ix = 0; ix < image.size(); ++ix)
	{
		Vector2 drawPositon = position;
		drawPositon.y += ix;
		Engine::Get().SetCursorPosition(drawPositon);
		Log(image[ix]);
	}

	// 다 그렸으면 커서 위치 리셋.
	//Engine::Get().SetCursorPosition(0, 0);
}
