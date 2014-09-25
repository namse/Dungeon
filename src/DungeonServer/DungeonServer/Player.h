
#include "Character.h"
class Player :
	public Character
{
public:
	Player(CharacterID id, PlayerLoadingInfo info);
	virtual ~Player();
};
