#pragma once

#include <map>
#include <WinSock2.h>

class ClientSession ;
struct PacketHeader ;
struct DatabaseJobContext ;

class ClientManager
{
public:
	ClientManager() : mLastGCTick(0)
	{}

	ClientSession* CreateClient(SOCKET sock) ;
	
	void BroadcastPacket(ClientSession* from, PacketHeader* pkt) ;

	void OnPeriodWork() ;


	void FlushClientSend();

private:

private:
	void CollectGarbageSessions() ;
	void DispatchDatabaseJobResults() ;
	

private:
	typedef std::map<SOCKET, ClientSession*> ClientList ;
	ClientList	mClientList ;

	DWORD		mLastGCTick ;
} ;

extern ClientManager* GClientManager ;