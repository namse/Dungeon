#include "stdafx.h"
#include "CharacterManager.h"
#include "Player.h"
CharacterManager* CharacterManager::mInstance = nullptr;

CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
}

void CharacterManager::AddCharacter(Character* character)
{
	if (character != nullptr)
	{
		character->mID = GenerateID();
	}
}

void CharacterManager::Notify(EventHeader* event)
{

}

CharacterID CharacterManager::NewPlayer(PlayerLoadingInfo info)
{
	CharacterID retID = GenerateID();

	Player* player = new Player(retID, info);
	return retID;
}
