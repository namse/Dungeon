#include "stdafx.h"
#include "CharacterManager.h"

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
