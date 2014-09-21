#pragma once
#include "stdafx.h"
class CharacterManager;
class Character
{
	friend	class CharacterManager;
public:
	Character();
	virtual ~Character() = NULL;


private:
	CharacterID mID;
};

