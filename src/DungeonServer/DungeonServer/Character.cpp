#include "stdafx.h"
#include "Character.h"
#include "CharacterManager.h"

Character::Character(CharacterID id)
	:mID(id)
{
	CharacterManager::GetInstance()->AddCharacter(this);
}


Character::~Character()
{
}
