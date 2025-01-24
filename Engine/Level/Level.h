#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4172)

#include "Core.h"
#include "RTTI.h"

// forward declaration
class Actor;

class ENGINE_API Level : public RTTI
{
	// RTTI ����
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// ���� �߰� �Լ�.
	void AddActor(Actor* newActor);

	// ���� ��û�� �� ���͸� �����ϴ� �Լ�.
	void ProcessAddedAndDestroyedActor();

	// ���� ó�� �Լ�.
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭.
	std::vector<Actor*> actors;

	// �߰� ��û�� ����.
	std::vector<Actor*> addRequestedActors;
};

