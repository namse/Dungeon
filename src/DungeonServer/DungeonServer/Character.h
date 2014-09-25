#pragma once
#include "stdafx.h"
class CharacterManager;
class Character
{
	friend	class CharacterManager;
public:
	Character(CharacterID id);
	virtual ~Character() = NULL;


protected:
	CharacterID		mID;
	wchar_t			mName[MAX_NAME_LEN];
};

