#include "stdafx.h"
#include "Player.h"


Player::Player(CharacterID id, PlayerLoadingInfo info)
	:Character(id)
{
	wcscpy(mName, info.mName);
}


Player::~Player()
{
}
