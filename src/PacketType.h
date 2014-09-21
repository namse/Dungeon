#pragma once

#define MAX_CHAT_LEN	256

#define MAX_NAME_LEN	8
#define MAX_COMMENT_LEN	40

#define MAX_ID_LEN 15
#define MAX_PW_LEN 15

enum PacketTypes
{
	PKT_NONE	= 0,
	
	PKT_CS_LOGIN = 1,
	PKT_SC_LOGIN = 2,
	
	PKT_SC_ENTER_PLACE = 3,
	PKT_CS_LOAD_PLACE = 4,
	PKT_SC_CHARACTER_LOAD = 5,
	PKT_SC_INFO_LOAD = 6,
	PKT_SC_LOADING_END = 7,

	PKT_CS_MOVE = 8,
	PKT_SC_MOVE = 9,

	PKT_CS_CHAT = 10,
	PKT_SC_CHAT = 11,


	PKT_MAX	= 1024
} ;

enum PlaceType
{
	PT_NONE = 0,

	PT_DONGDONG_DUNGEON = 1,
};
enum CharacterType
{
	CT_NONE = 0,

	CT_PLAYER = 1,
	CT_MONSTER = 2,
};
struct CharacterInfo
{
	CharacterInfo()
	{
		mType = CT_NONE;
		mX = mY = INFINITE;
		memset(mName, 0, sizeof(mName));
	}
	CharacterType	mType;
	float				mX, mY;
	CharacterID		mID;
	wchar_t			mName[MAX_NAME_LEN];
};

#pragma pack(push, 1)

struct PacketHeader
{
	PacketHeader() : mSize(0), mType(PKT_NONE) 	{}
	short mSize ;
	short mType ;
} ;



struct LoginRequest : public PacketHeader
{
	LoginRequest()
	{
		mSize = sizeof(LoginRequest) ;
		mType = PKT_CS_LOGIN ;
		memset(mID, 0, sizeof(mID));
		memset(mPassword, 0, sizeof(mPassword));
	}
	char mID			[MAX_ID_LEN];
	char mPassword[MAX_PW_LEN];
} ;

struct LoginResult : public PacketHeader
{
	LoginResult()
	{
		mSize = sizeof(LoginResult) ;
		mType = PKT_SC_LOGIN ;
		mSucceed = false;
	}
	bool mSucceed;
} ;

struct EnterPlaceResult : public PacketHeader
{
	EnterPlaceResult()
	{
		mSize = sizeof(EnterPlaceResult);
		mType = PKT_SC_ENTER_PLACE;
		mPlaceType = PT_NONE;
	}
	PlaceType mPlaceType;
};

struct LoadPlaceRequest : public PacketHeader
{
	LoadPlaceRequest()
	{
		mSize = sizeof(LoadPlaceRequest);
		mType = PKT_CS_LOAD_PLACE;
	}
};

struct CharacterLoadResult : public PacketHeader
{
	CharacterLoadResult()
	{
		mSize = sizeof(CharacterLoadResult);
		mType = PKT_SC_CHARACTER_LOAD;
		memset(&mInfo, 0, sizeof(mInfo));
	}
	CharacterLoadResult(CharacterInfo info)
	{
		mSize = sizeof(CharacterLoadResult);
		mType = PKT_SC_CHARACTER_LOAD;
		mInfo = info;
	}
	CharacterInfo mInfo;
};

struct InfoLoadResult : public PacketHeader
{
	InfoLoadResult()
	{
		mSize = sizeof(InfoLoadResult);
		mType = PKT_SC_INFO_LOAD;
		mMyPlayerID = -1;
	}
	CharacterID mMyPlayerID;



};

struct LoadingEndResult : public PacketHeader
{
	LoadingEndResult()
	{
		mSize = sizeof(LoadingEndResult);
		mType = PKT_SC_LOADING_END;
	}
};

struct ChatBroadcastRequest : public PacketHeader
{
	ChatBroadcastRequest()
	{
		mSize = sizeof(ChatBroadcastRequest) ;
		mType = PKT_CS_CHAT ;
		mPlayerId = -1 ;
	
		memset(mChat, 0, MAX_CHAT_LEN) ;
	}

	int	mPlayerId ;
	char mChat[MAX_CHAT_LEN] ;
} ;

struct ChatBroadcastResult : public PacketHeader
{
	ChatBroadcastResult()
	{
		mSize = sizeof(ChatBroadcastResult) ;
		mType = PKT_SC_CHAT ;
		mPlayerId = -1 ;
		
		memset(mName, 0, MAX_NAME_LEN) ;
		memset(mChat, 0, MAX_CHAT_LEN) ;
	}
	
	int	mPlayerId ;
	char mName[MAX_NAME_LEN] ;
	char mChat[MAX_CHAT_LEN] ;
} ;


struct MoveRequest : public PacketHeader
{
	MoveRequest()
	{
		mSize = sizeof(MoveRequest);
		mType = PKT_CS_MOVE;
		mPlayerId = -1;
		mPosX = 0;
		mPosY = 0;
	}

	int		mPlayerId;
	float	mPosX;
	float	mPosY;
};

struct MoveBroadcastResult : public PacketHeader
{
	MoveBroadcastResult()
	{
		mSize = sizeof(MoveBroadcastResult);
		mType = PKT_SC_MOVE;
		mPlayerId = -1;
		mPosX = 0;
		mPosY = 0;
	}

	int		mPlayerId;
	float	mPosX;
	float	mPosY;
};



#pragma pack(pop)