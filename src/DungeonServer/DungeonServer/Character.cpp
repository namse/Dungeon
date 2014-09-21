#include "stdafx.h"
#include "Character.h"
#include "CharacterManager.h"

Character::Character()
{
	CharacterManager::GetInstance()->AddCharacter(this);
}


Character::~Character()
{
}
