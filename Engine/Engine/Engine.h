#pragma once

#include "Core.h"
#include "Math/Vector2.h"

// �Է� ó���� ���� ����ü.
struct KeyState
{
	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��.
	bool isKeyDown = false;

	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��.
	bool wasKeyDown = false;
};

// Ŀ���� ������ ������ �� ��� �� ������.
enum class CursorType
{
	NoCursor,
	SolidCursor,
	NormalCursor
};

class Level;
class Actor;
class Physics;
class CollisionComponent;

// ���� Ŭ����.
class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	// ���� ���� �Լ�.
	void Run();

	// ���� �߰� �Լ�.
	void LoadLevel(Level* newLevel);

	void AddActor(Actor* newActor);
	void DestroyActor(Actor* targerActor);

	// ȭ�� ���� ���� �Լ�.
	void SetConsoleFont(int fontWidth, int fontHeight);
	void SetConsoleWindowSize(int width, int height);
	void SetConsoleBufferSize(int width, int height);

	// ȭ�� ��ǥ ���� �Լ�.
	void SetCursorType(CursorType cursorType);
	void SetCursorPosition(const Vector2& position);
	void SetCursorPosition(int x, int y);

	// ȭ�� ũ�� ��ȯ �Լ�.
	inline Vector2 ScreenSize() const { return screenSize; }

	// Ÿ�� ������ �ӵ� ���� �Լ�.
	void SetTargetFrameRate(float targetFrameRate);

	// �Է� ���� �Լ�.
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	// ���� ���� �Լ�.
	void QuitGame();
	
	//�̱��� ��ü ���� �Լ�.
	static Engine& Get();
	
	// Physics�� �ݸ��� ��� �Լ�.
	void AddCollisionComponent(CollisionComponent* inComponent);

protected:
	void ProcessInput();			//�Է� ó��.
	void Update(float deltaTime);	// Tick();
	void Clear();					// ȭ�� �����.
	void Draw();					// Render();

	// ���� �������� Ű ���¸� �����ϴ� �Լ�.
	void SavePreviousKeyStates();

protected:
	// Ÿ�� ������ ����(�ʴ� ������).
	float targetFrameRate = 60.f;

	// �� ������ �ð� ��(����: ��).
	float targetOneFrameTime = 0.f;

	// ������ �� ���� �� ����.
	bool bQuit;

	// Ű ���¸� �����ϴ� �迭.
	KeyState keyState[255];

	// �̱��� ������ ���� ���� ���� ����.
	static Engine* instance;

	// ���� ����.
	Level* mainLevel;

	// �������� ������Ʈ�ؾ� �ϴ��� ���θ� ��Ÿ���� ����.
	bool bShouldUpdate = true;

	// ȭ�� ũ��.
	Vector2 screenSize;

	// ȭ�� ���� �� ����� ����.
	char* emptyStringBuffer = nullptr;

	// ������ �̱���.
	static Physics* physics;
};