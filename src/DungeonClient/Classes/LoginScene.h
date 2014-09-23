#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "../../PacketType.h"
#include "SignUpLayer.h"

USING_NS_CC;



class LoginScene : public cocos2d::LayerColor
{
	enum FocusStatus{
		FS_NONE,
		FS_ID,
		FS_PW,
	}	mFocusStatus;

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(LoginScene);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void onLoginResult(LoginResult inPacket);

	char* getID(){ return mID; }
	char* getPW(){ return mPassword; }

private:

	void update(float dTime);
	void onMenuItemPressed(Ref* sender);
	void switchFocus(LoginScene::FocusStatus focusStatus);
	bool isShiftingOn()
	{
		return mIsShiftPressed & mIsCapslockOn;
	}

	SignUpLayer* mSignUpLayer = nullptr;

	MenuItemFont* mIDItem = nullptr;
	MenuItemFont* mPWItem = nullptr;
	MenuItemFont* mLoginButtonItem = nullptr;

	char	mID[MAX_ID_LEN+1]; // +1 for NULL
	char	mPassword[MAX_PW_LEN+1];
	const wchar_t * mIDPlaceHolder = L"여기 눌러서 아이디 입력";
	const wchar_t*  mPWPlaceHolder = L">비번도 입력해욜<";

	float mBackSpaceTick = 0.f;
	bool mIsBackSpacePressed = false;
	bool mIsFirstPeriodForBackSpace = false;
	const float mBackSpaceFirstPeriod = 0.3f;
	const float mBackSpacePeriod = 0.01f;

	bool mIsCursorShow = false;
	float mCursorTick = 0.f; 
	const float mCursorTickPeriod = 0.5f;
	const char mCursor = 'l';
	
	bool mIsShiftPressed = false;
	bool mIsCapslockOn = false;

};


struct keyCodeItem{
	int glfwkeyCode;
	EventKeyboard::KeyCode keyCode;
};
static keyCodeItem PrintableKeyCodeStructArray[] = {
	/* Printable keys */
		{ GLFW_KEY_SPACE, EventKeyboard::KeyCode::KEY_SPACE },
		{ GLFW_KEY_APOSTROPHE, EventKeyboard::KeyCode::KEY_APOSTROPHE },
		{ GLFW_KEY_COMMA, EventKeyboard::KeyCode::KEY_COMMA },
		{ GLFW_KEY_MINUS, EventKeyboard::KeyCode::KEY_MINUS },
		{ GLFW_KEY_PERIOD, EventKeyboard::KeyCode::KEY_PERIOD },
		{ GLFW_KEY_SLASH, EventKeyboard::KeyCode::KEY_SLASH },
		{ GLFW_KEY_0, EventKeyboard::KeyCode::KEY_0 },
		{ GLFW_KEY_1, EventKeyboard::KeyCode::KEY_1 },
		{ GLFW_KEY_2, EventKeyboard::KeyCode::KEY_2 },
		{ GLFW_KEY_3, EventKeyboard::KeyCode::KEY_3 },
		{ GLFW_KEY_4, EventKeyboard::KeyCode::KEY_4 },
		{ GLFW_KEY_5, EventKeyboard::KeyCode::KEY_5 },
		{ GLFW_KEY_6, EventKeyboard::KeyCode::KEY_6 },
		{ GLFW_KEY_7, EventKeyboard::KeyCode::KEY_7 },
		{ GLFW_KEY_8, EventKeyboard::KeyCode::KEY_8 },
		{ GLFW_KEY_9, EventKeyboard::KeyCode::KEY_9 },
		{ GLFW_KEY_SEMICOLON, EventKeyboard::KeyCode::KEY_SEMICOLON },
		{ GLFW_KEY_EQUAL, EventKeyboard::KeyCode::KEY_EQUAL },
		{ GLFW_KEY_A, EventKeyboard::KeyCode::KEY_A },
		{ GLFW_KEY_B, EventKeyboard::KeyCode::KEY_B },
		{ GLFW_KEY_C, EventKeyboard::KeyCode::KEY_C },
		{ GLFW_KEY_D, EventKeyboard::KeyCode::KEY_D },
		{ GLFW_KEY_E, EventKeyboard::KeyCode::KEY_E },
		{ GLFW_KEY_F, EventKeyboard::KeyCode::KEY_F },
		{ GLFW_KEY_G, EventKeyboard::KeyCode::KEY_G },
		{ GLFW_KEY_H, EventKeyboard::KeyCode::KEY_H },
		{ GLFW_KEY_I, EventKeyboard::KeyCode::KEY_I },
		{ GLFW_KEY_J, EventKeyboard::KeyCode::KEY_J },
		{ GLFW_KEY_K, EventKeyboard::KeyCode::KEY_K },
		{ GLFW_KEY_L, EventKeyboard::KeyCode::KEY_L },
		{ GLFW_KEY_M, EventKeyboard::KeyCode::KEY_M },
		{ GLFW_KEY_N, EventKeyboard::KeyCode::KEY_N },
		{ GLFW_KEY_O, EventKeyboard::KeyCode::KEY_O },
		{ GLFW_KEY_P, EventKeyboard::KeyCode::KEY_P },
		{ GLFW_KEY_Q, EventKeyboard::KeyCode::KEY_Q },
		{ GLFW_KEY_R, EventKeyboard::KeyCode::KEY_R },
		{ GLFW_KEY_S, EventKeyboard::KeyCode::KEY_S },
		{ GLFW_KEY_T, EventKeyboard::KeyCode::KEY_T },
		{ GLFW_KEY_U, EventKeyboard::KeyCode::KEY_U },
		{ GLFW_KEY_V, EventKeyboard::KeyCode::KEY_V },
		{ GLFW_KEY_W, EventKeyboard::KeyCode::KEY_W },
		{ GLFW_KEY_X, EventKeyboard::KeyCode::KEY_X },
		{ GLFW_KEY_Y, EventKeyboard::KeyCode::KEY_Y },
		{ GLFW_KEY_Z, EventKeyboard::KeyCode::KEY_Z },
		{ GLFW_KEY_LEFT_BRACKET, EventKeyboard::KeyCode::KEY_LEFT_BRACKET },
		{ GLFW_KEY_BACKSLASH, EventKeyboard::KeyCode::KEY_BACK_SLASH },
		{ GLFW_KEY_RIGHT_BRACKET, EventKeyboard::KeyCode::KEY_RIGHT_BRACKET },
		{ GLFW_KEY_GRAVE_ACCENT, EventKeyboard::KeyCode::KEY_GRAVE }
};


#endif // __LOGIN_SCENE_H__