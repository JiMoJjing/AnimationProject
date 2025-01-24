#include <iostream>
#include "Engine/Engine.h"
#include "Level/TestLevel.h"

int main()
{
    CheckMemoryLeak();

	// 현재 콘솔 창의 핸들 가져오기
	HWND consoleWindow = GetConsoleWindow();
    
	// 콘솔 창 해상도.
	Engine::Get().SetConsoleBufferSize(1920, 1080);
   
	// 폰트 크기 조정.
	Engine::Get().SetConsoleFont(1, 2);
	
	// 콘솔 창 최대화
	ShowWindow(consoleWindow, SW_MAXIMIZE); 

	Engine engine;
	engine.LoadLevel(new TestLevel());
	engine.Run();
}