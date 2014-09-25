#pragma once

#include <WinSock2.h>
#include "Config.h"
#include "..\..\PacketType.h"
#include "ObjectPool.h"


/// 모든 DB관련 작업은 아래의 추상 클래스를 상속받아 사용해야 함
struct DatabaseJobContext
{
	DatabaseJobContext() : mSuccess(false)
	{}

	DatabaseJobContext(SOCKET socketKey) :  mSockKey(socketKey), mSuccess(false) 
	{}

	virtual ~DatabaseJobContext() {}

	virtual bool OnExecute() = 0 ;

	SOCKET	mSockKey;
	bool	mSuccess ;
} ;


/// player load 작업
struct LoadPlayerDataContext : public DatabaseJobContext, public ObjectPool<LoadPlayerDataContext>
{
	LoadPlayerDataContext(SOCKET socketKey, const char* playerId, const char* playerPW) : DatabaseJobContext(socketKey)
	{
		memcpy(mPlayerId, playerId, sizeof(mPlayerId));
		memcpy(mPlayerPassword, playerPW, sizeof(mPlayerPassword));
		mResultType = LRT_SUCCEED;
		mIndex = -1;
	}


	virtual bool OnExecute() ;


	char	mPlayerId[MAX_ID_LEN];
	char	mPlayerPassword[MAX_PW_LEN];

	LoginResultTypes mResultType;
	PlayerIndexForDB mIndex;
	PlayerLoadingInfo mInfo;
} ;


/// Player 생성 작업
struct CreatePlayerDataContext : public DatabaseJobContext, public ObjectPool<CreatePlayerDataContext>
{
	CreatePlayerDataContext(SOCKET socketKey, const char* id, const char* pw, const wchar_t* name)
		: DatabaseJobContext(socketKey)
	{
		memcpy(mPlayerID, id, sizeof(mPlayerID));
		memcpy(mPlayerPW, pw, sizeof(mPlayerPW));
		memcpy(mPlayerName, name, sizeof(mPlayerName));
		mReusltType = SRT_SUCCEED;
	}

	virtual bool OnExecute() ;

	char		mPlayerID[MAX_ID_LEN];
	char		mPlayerPW[MAX_PW_LEN];
	wchar_t	mPlayerName[MAX_NAME_LEN] ;

	SignUpResultType mReusltType;

} ;


