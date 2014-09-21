#pragma once
#include "stdafx.h"
#include "EventListener.h"
#include "Character.h"

class CharacterManager : public EventListener
{
public:
	static CharacterManager* GetInstance() {
		if (mInstance == nullptr)
			mInstance = new CharacterManager();
		return mInstance;
	}

	static void FreeInstance() {
		if (mInstance != nullptr)
			delete mInstance;
	}

	Character* GetElements(CharacterID identity)
	{
		if (mCharacterList.find(identity) == mCharacterList.end())
			return nullptr;
		return mCharacterList[identity];
	}

	virtual void Notify(EventHeader* event);


	// only use on character's constructor
	void AddCharacter(Character* character);

private:
	CharacterManager();
	~CharacterManager();

	CharacterID GenerateID(){
		static CharacterID id = 0;
		return id++;
	}



	typedef std::map<CharacterID, Character*> CharacterList;
	CharacterList	mCharacterList;
	static CharacterManager* mInstance;
};
