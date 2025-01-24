#include "PreCompiledHeader.h"

#include "Engine.h"
#include <Windows.h>
#include <iostream>

#include "Level/Level.h"
#include "Actor/Actor.h"

#include <time.h>
#include "Engine/Physics.h"

// 스태틱 변수 초기화.
Engine* Engine::instance = nullptr;
Physics* Engine::physics = nullptr;

BOOL WINAPI MessageProcessor(DWORD message)
{
	switch (message)
	{
	case CTRL_CLOSE_EVENT:
		Engine::Get().QuitGame();
		break;
	}

	return true;
}

Engine::Engine()
	: bQuit(false), mainLevel(nullptr), screenSize(40, 25)
{
	// 스크린 사이즈 설정.
	COORD maxSize = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
	screenSize.x = (int)maxSize.X - 1;
	screenSize.y = (int)maxSize.Y - 1;

	// 랜덤 시드 설정.
	srand((unsigned int)time(nullptr));

	// 싱글톤 객체 설정.
	instance = this;

	// 기본 타겟 프레임 속도 설정.
	SetTargetFrameRate(60.f);

	SetConsoleCtrlHandler(MessageProcessor, TRUE);

	//// 화면 지울 때 사용할 버퍼 초기화.
	//// 1. 버퍼 크기 할당.
	//emptyStringBuffer = new char[(screenSize.x + 1) * screenSize.y + 1];
	//// 버퍼 덮어쓰기.
	//memset(emptyStringBuffer, ' ', (screenSize.x + 1) * screenSize.y + 1);
	//// 2. 값 할당.
	//for (int y = 0; y < screenSize.y; ++y)
	//{
	//	// 각 줄 끝에 개행 문자 추가.
	//	emptyStringBuffer[(y * (screenSize.x + 1)) + screenSize.x] = '\n';
	//
	//// 마지막에 널 문자 추가.
	//emptyStringBuffer[(screenSize.x + 1) * screenSize.y] = '\0';

	// 피직스 생성.
	physics = new Physics();
}

Engine::~Engine()
{
	// 메인 레벨 메모리 해제.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}
	
	// 클리어 버퍼 삭제.
	delete[] emptyStringBuffer;

	SafeDelete(physics);
}

void Engine::Run()
{
	// 시작 타임 스탬프 저장.
	// timeGetTime 함수는 밀리세컨드(1/1000초) 단위.
	//unsigned long currentTime = timeGetTime();
	//unsigned long previousTime = 0;

	// CPU 시계 사용.
	// 시스템 시계 -> 고해상도 카운터. (10000000).
	// 메인보드에 시계가 있음.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//std::cout << "Frequency: " << frequency.QuadPart << "\n";

	// 시작 시간 및 이전 시간을 위한 변수.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;

	// 프레임 제한.
	//float targetFrameRate = 90.0f;

	// 한 프레임 시간 계산.
	//float targetOneFrameTime = 1.0f / targetFrameRate;

	// Game-Loop.
	while (true)
	{
		// 종료 조건.
		if (bQuit)
		{
			break;
		}

		// 현재 프레임 시간 저장.
		//time = timeGetTime();
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// 프레임 시간 계산.
		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		// 한 프레임 시간 계산.
		//float targetOneFrameTime = 1.0f / targetFrameRate;

		// 프레임 확인.
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인).
			ProcessInput();

			// 업데이트 가능한 상태에서만 프레임 업데이트 처리.
			if (bShouldUpdate)
			{
				Update(deltaTime);
				Draw();
			}

			// 키 상태 저장.
			SavePreviousKeyStates();

			// 이전 프레임 시간 저장.
			previousTime = currentTime;

			// 액터 정리 (삭제 요청된 액터들 정리).
			if (mainLevel)
			{
				//mainLevel->DestroyActor();
				mainLevel->ProcessAddedAndDestroyedActor();
			}

			// 프레임 활성화.
			bShouldUpdate = true;
		}

		//Sleep(1);
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// 기존 레벨이 있다면 삭제 후 교체.

	// 메인 레벨 설정.
	mainLevel = newLevel;
}

void Engine::AddActor(Actor* newActor)
{
	// 예외 처리.
	if (mainLevel == nullptr)
	{
		return;
	}

	// 레벨에 액터 추가.
	bShouldUpdate = false;
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// 예외 처리.
	if (mainLevel == nullptr)
	{
		return;
	}

	// 레벨에 액터 추가.
	bShouldUpdate = false;
	targetActor->Destroy();
}

void Engine::SetConsoleFont(int fontWidth, int fontHeight)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (consoleHandle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "콘솔 핸들을 가져올 수 없습니다." << std::endl;
		return;
	}

	CONSOLE_FONT_INFOEX fontInfo = { 0 };
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	// 기존 폰트 정보 가져오기
	if (!GetCurrentConsoleFontEx(consoleHandle, FALSE, &fontInfo))
	{
		std::cerr << "현재 콘솔 폰트 정보를 가져올 수 없습니다." << std::endl;
		return;
	}

	// 글꼴 크기 설정
	fontInfo.dwFontSize.X = fontWidth;   // 글자 너비
	fontInfo.dwFontSize.Y = fontHeight; // 글자 높이
	wcscpy_s(fontInfo.FaceName, L"Consolas"); // 폰트 이름 설정 (Consolas)

	if (!SetCurrentConsoleFontEx(consoleHandle, FALSE, &fontInfo)) {
		std::cerr << "폰트 크기를 설정할 수 없습니다." << std::endl;
		return;
	}
}

void Engine::SetConsoleWindowSize(int width, int height)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (consoleHandle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "콘솔 핸들을 가져올 수 없습니다." << std::endl;
		return;
	}

	// 콘솔 화면 버퍼 크기 설정
	COORD bufferSize;
	bufferSize.X = width;
	bufferSize.Y = height;

	if (!SetConsoleScreenBufferSize(consoleHandle, bufferSize))
	{
		std::cerr << "콘솔 화면 버퍼 크기를 설정할 수 없습니다." << std::endl;
		return;
	}

	// 콘솔 창 크기 설정
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;

	if (!SetConsoleWindowInfo(consoleHandle, TRUE, &windowSize))
	{
		std::cerr << "콘솔 창 크기를 설정할 수 없습니다." << std::endl;
		return;
	}
}

void Engine::SetConsoleBufferSize(int width, int height)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (consoleHandle == INVALID_HANDLE_VALUE)
	{
		__debugbreak();
		std::cerr << "콘솔 핸들을 가져올 수 없습니다." << std::endl;
		return;
	}

	// 화면 버퍼 크기 설정
	COORD bufferSize;
	bufferSize.X = width;   // 너비
	bufferSize.Y = height;  // 높이

	if (!SetConsoleScreenBufferSize(consoleHandle, bufferSize))
	{
		__debugbreak();
		std::cerr << "화면 버퍼 크기를 설정할 수 없습니다." << std::endl;
		return;
	}
}

void Engine::SetCursorType(CursorType cursorType)
{
	// 1. 커서 속성 구조체 설정.
	CONSOLE_CURSOR_INFO info = { };

	// 타입 별로 구조체 값 설정.
	switch (cursorType)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;
		info.bVisible = FALSE;
		break;

	case CursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;

	case CursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;

	}

	// 2. 설정.
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Engine::SetCursorPosition(const Vector2& position)
{
	SetCursorPosition(position.x, position.y);
}

void Engine::SetCursorPosition(int x, int y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

void Engine::QuitGame()
{
	// 종료 플래그 설정.
	bQuit = true;
}

Engine& Engine::Get()
{
	// 싱글톤 객체 반환.
	return *instance;
}

void Engine::AddCollisionComponent(CollisionComponent* inComponent)
{
	if (physics != nullptr)
	{
		physics->AddComponent(inComponent);
	}
}

void Engine::ProcessInput()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].isKeyDown = (GetAsyncKeyState(ix) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// 레벨 업데이트.
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}

	// Physics 업데이트.
	if (physics != nullptr)
	{
		physics->Update(deltaTime);
	}
}

void Engine::Clear()
{
	// 화면의 (0,0)으로 이동.
	//SetCursorPosition(0, 0);

	// 화면 지우기.
	//std::cout << emptyStringBuffer;

	// 화면의 (0,0)으로 이동.
	//SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	// 레벨 그리기.
	if (mainLevel != nullptr)
	{
		mainLevel->Draw();
	}
}

void Engine::SavePreviousKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].wasKeyDown = keyState[ix].isKeyDown;
	}
}