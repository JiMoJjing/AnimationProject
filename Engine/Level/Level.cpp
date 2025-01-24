#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}

Level::~Level()
{
	// �޸� ����
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}
}

void Level::AddActor(Actor* newActor)
{
	addRequestedActors.push_back(newActor);
}

void Level::ProcessAddedAndDestroyedActor()
{
	// ���� ��ȸ �� ���� ��û�� ���͸� ó��.
	for (int ix = 0; ix < actors.size();)
	{
		if (actors[ix]->IsExpired())
		{
			delete actors[ix];
			actors[ix] = nullptr;
			actors.erase(actors.begin() + ix);
			continue;
		}

		++ix;
	}

	// �߰� ��û�� ���� ó��.
	if (addRequestedActors.size() > 0)
	{
		for (auto* actor : addRequestedActors)
		{
			actors.push_back(actor);
		}
		
		addRequestedActors.clear();
	}
}

void Level::Update(float deltaTime)
{
	for (Actor* actor : actors)
	{
		if (!actor->IsActive() || actor->IsExpired())
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	for (Actor* actor : actors)
	{
		if (!actor->IsActive() || actor->IsExpired())
		{
			continue;
		}

		actor->Draw();
	}
}
