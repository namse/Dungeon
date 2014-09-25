#include "stdafx.h"
#include "DatabaseJobContext.h"
#include "SQLStatement.h"
#include "DbHelper.h"



bool LoadPlayerDataContext::OnExecute()
{
	DbHelper dbhelper(SQL_LoginRequest) ;
	dbhelper.BindParamText(mPlayerId, strlen(mPlayerId)) ;
	dbhelper.BindParamText(mPlayerPassword, strlen(mPlayerPassword));

	/// 데이터가 없네?
	if (dbhelper.FetchRow() == RESULT_DONE)
	{
		// TODO
		//확인작업 해야함. 아이디가 틀린건지 비번이 틀린건지 등등
		DbHelper wrongPwChecker(SQL_IsIDRegisteredRequest);
		wrongPwChecker.BindParamText(mPlayerId, strlen(mPlayerId));
		if (RESULT_ROW != wrongPwChecker.FetchRow())
		{
			assert(false);
			return false;
		}
		int idCount = wrongPwChecker.GetResultParamInt();
		if (idCount == 0)
		{
			mResultType = LRT_NOT_REGIESTERED_ID;
			return true;
		}
		else
		{
			mResultType = LRT_WRONG_PW;
			return true;
		}
	}
	else if (dbhelper.GetResultColCount() == 1)
	{
		mIndex = dbhelper.GetResultParamInt();

		//필요한 데이터 끌어오자
		DbHelper infoLoader(SQL_GetPlayerInfo);
		infoLoader.BindParamInt(mIndex);

		if (RESULT_ROW != infoLoader.FetchRow())
		{
			// 문제 있다냥;;
			assert(false);
			return false;
		}
		else
		{
			MultiByteToWideChar(CP_UTF8, 0, (LPSTR)infoLoader.GetResultParamText(), -1, mInfo.mName, MAX_NAME_LEN);
			mResultType = LRT_SUCCEED;
			return true;
		}
	}
	else
	{
		assert(false);
		return false;
	}
}

bool CreatePlayerDataContext::OnExecute()
{

	DbHelper checkDupplicatedIDHelper(SQL_IsIDRegisteredRequest);

	checkDupplicatedIDHelper.BindParamText(mPlayerID, strlen(mPlayerID));
	if (checkDupplicatedIDHelper.FetchRow() == RESULT_ERROR)
	{
		assert(false);
		return false;
	}
	if (checkDupplicatedIDHelper.GetResultParamInt() == 0)
	{
		DbHelper checkDupplicatedNameHelper(SQL_IsNameRegisteredRequest);

		char nameBuf[1024] = "";
		WideCharToMultiByte(CP_UTF8, 0, mPlayerName, -1, nameBuf, sizeof(nameBuf), NULL, NULL);
		checkDupplicatedNameHelper.BindParamText(nameBuf, strlen(nameBuf));

		if (checkDupplicatedNameHelper.FetchRow() == RESULT_ERROR)
		{
			assert(false);
			return false;
		}
		if (checkDupplicatedNameHelper.GetResultParamInt() == 0)
		{
			DbHelper signUpHelper(SQL_SignUpRequest);
			signUpHelper.BindParamText(mPlayerID, strlen(mPlayerID));
			signUpHelper.BindParamText(mPlayerPW, strlen(mPlayerPW));
			signUpHelper.BindParamText(nameBuf, strlen(nameBuf));
			if (RESULT_ERROR == signUpHelper.FetchRow())
			{
				assert(false);
				return false;
			}
			else
			{
				mReusltType = SRT_SUCCEED;
				return true;
			}
		}
		else
		{
			mReusltType = SRT_DupplicatedName;
			return true;
		}
	}
	else
	{
		mReusltType = SRT_DupplicatedID;
		return true;
	}
}