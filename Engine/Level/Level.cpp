#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}

Level::~Level()
{
	// 메모리 해제
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
	// 액터 순회 후 삭제 요청된 액터를 처리.
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

	// 추가 요청된 액터 처리.
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
