#include <iostream>
#include "Engine/Engine.h"
#include "Level/TestLevel.h"

int main()
{
    CheckMemoryLeak();

	// ���� �ܼ� â�� �ڵ� ��������
	HWND consoleWindow = GetConsoleWindow();
    
	// �ܼ� â �ػ�.
	Engine::Get().SetConsoleBufferSize(1920, 1080);
   
	// ��Ʈ ũ�� ����.
	Engine::Get().SetConsoleFont(1, 2);
	
	// �ܼ� â �ִ�ȭ
	ShowWindow(consoleWindow, SW_MAXIMIZE); 

	Engine engine;
	engine.LoadLevel(new TestLevel());
	engine.Run();
}