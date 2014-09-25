#include "LoginScene.h"
#include "base/CCEventKeyboard.h"
#include "TcpClient.h"
#include "../../PacketType.h"

const std::string LoginScene::layerName = std::string( "login_layer");

Scene* LoginScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoginScene::create();

	// add layer as a child to scene
	scene->addChild(layer, 1, std::string(LoginScene::layerName));

	auto signUpLayer = SignUpLayer::create();
	scene->addChild(signUpLayer, 2, std::string(SignUpLayer::layerName));
	signUpLayer->setVisible(false);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(ccc4(255, 255, 255, 255)))
	{
		return false;
	}

	memset(mPassword, 0, sizeof(mPassword));
	memset(mID, 0, sizeof(mID));
	mFocusStatus = FS_NONE;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	// ID TextField Init
	{
		char buf[1024];
		WideCharToMultiByte(CP_UTF8, 0, mIDPlaceHolder, -1, buf, sizeof(buf), NULL, NULL);
		mIDItem = MenuItemFont::create(
			buf,
			this,
			menu_selector(LoginScene::onMenuItemPressed));
		mIDItem->setAnchorPoint(Vec2(0.5f, 0.5f));
		mIDItem->setFontNameObj("맑은 고딕");
		mIDItem->setFontSizeObj(30);
		mIDItem->setColor(ccBLUE);
	}

	// PW Textfield Init
	{
		char buf[1024];
		WideCharToMultiByte(CP_UTF8, 0, mPWPlaceHolder, -1, buf, sizeof(buf), NULL, NULL);
		mPWItem = MenuItemFont::create(
			buf,
			this,
			menu_selector(LoginScene::onMenuItemPressed));
		mPWItem->setAnchorPoint(Vec2(0.5f, 0.5f));
		mPWItem->setFontSizeObj(30);
		mPWItem->setFontNameObj("맑은 고딕");
		mPWItem->setColor(ccGREEN);
	}

	// Login Button Init
	{
		char buf[1024];
		WideCharToMultiByte(CP_UTF8, 0, L"<로그인> <-클릭", -1, buf, sizeof(buf), NULL, NULL);
		mLoginButtonItem = MenuItemFont::create(
			buf,
			this,
			menu_selector(LoginScene::onMenuItemPressed));
		mLoginButtonItem->setAnchorPoint(Vec2(0.5f, 0.5f));
		mLoginButtonItem->setFontNameObj("맑은 고딕");
		mLoginButtonItem->setFontSizeObj(30);
		mLoginButtonItem->setColor(ccBLACK);
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(mIDItem, mPWItem, mLoginButtonItem, NULL);
	menu->setPosition(ccp(visibleSize.width / 2.f, visibleSize.height /2.f));
	this->addChild(menu);
	menu->alignItemsVertically();

	/// 게임루프에서 돌도록 추가
	this->schedule(schedule_selector(LoginScene::update), 0.0f);

	this->setKeyboardEnabled(true);

	return true;
}


void LoginScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE
		&& mIsBackSpacePressed == false)
	{
		mIsBackSpacePressed = true;
		mBackSpaceTick = 0.f;
		mIsFirstPeriodForBackSpace = true;
		switch (mFocusStatus)
		{
		case LoginScene::FS_NONE:
			break;
		case LoginScene::FS_ID:
			if (strlen(mID) > 0)mID[strlen(mID) - 1] = NULL;
			break;
		case LoginScene::FS_PW:
			if (strlen(mPassword) > 0)mPassword[strlen(mPassword) - 1] = NULL;
			break;
		default:
			break;
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SHIFT && mIsShiftPressed == false)
	{
		mIsShiftPressed = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_CAPS_LOCK)
	{
		mIsCapslockOn = !mIsCapslockOn;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER)
	{
		if (mFocusStatus == FS_ID)
		{
			switchFocus(FS_PW);
		}
		else if ( mFocusStatus == FS_PW)
			onMenuItemPressed(mLoginButtonItem);
	}


	for (auto keyItem : PrintableKeyCodeStructArray)
	{
		if (keyItem.keyCode == keyCode)
		{
			switch (mFocusStatus)
			{
			case LoginScene::FS_NONE:
				break;
			case LoginScene::FS_ID:
			{
				if (strlen(mID) < MAX_ID_LEN)
				{
				
					if (keyItem.glfwkeyCode >= GLFW_KEY_A
						&& keyItem.glfwkeyCode <= GLFW_KEY_Z)
					{
						if (isShiftingOn() == true )
							mID[strlen(mID)] = toupper(keyItem.glfwkeyCode);
						else
							mID[strlen(mID)] = tolower(keyItem.glfwkeyCode);
					}
					else
						mID[strlen(mID)] = keyItem.glfwkeyCode;
				}
			}
				break;
			case LoginScene::FS_PW:
			{
				if (strlen(mPassword) < MAX_PW_LEN)
				{
					if (keyItem.glfwkeyCode >= GLFW_KEY_A
						&& keyItem.glfwkeyCode <= GLFW_KEY_Z)
					{

						if (isShiftingOn())
							mPassword[strlen(mPassword)] = toupper(keyItem.glfwkeyCode);
						else
							mPassword[strlen(mPassword)] = tolower(keyItem.glfwkeyCode);
					}
					else
					{
						switch (keyItem.glfwkeyCode)
						{
						case GLFW_KEY_0:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '0' : ')';
						}break;
						case GLFW_KEY_1:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '1' : '!';
						}break;
						case GLFW_KEY_2:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '2' : '@';
						}break;
						case GLFW_KEY_3:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '3' : '#';
						}break;
						case GLFW_KEY_4:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '4' : '$';
						}break;
						case GLFW_KEY_5:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '5' : '%';
						}break;
						case GLFW_KEY_6:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '6' : '^';
						}break;
						case GLFW_KEY_7:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '7' : '&';
						}break;
						case GLFW_KEY_8:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '8' : '*';
						}break;
						case GLFW_KEY_9:
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '9' : '(';
						}break;
						case '`':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '`' : '~';
						}break;
						case '-':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '-' : '_';
						}break;
						case '=':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '=' : '+';
						}break;
						case '[':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '[' : '{';
						}break;
						case ']':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? ']' : '}';
						}break;
						case '\\':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '\\' : '|';
						}break;
						case ';' :
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? ';' : ':';
						}break;
						case '\'':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '\'' : '\"';
						}break;
						case ',':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? ',' : '<';
						}break;
						case '.':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '.' : '>';
						}break;
						case '/':
						{
							mPassword[strlen(mPassword)] = (isShiftingOn() == false) ? '/' : '?';
						}break;
						}
					}
				}
			}
				break;
			default:
				break;
			}
			break;
		}
	}
}
void LoginScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		mIsBackSpacePressed = false;
		mIsFirstPeriodForBackSpace = true;
		mBackSpaceTick = 0.f;

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
	{
		switch (mFocusStatus)
		{
		case LoginScene::FS_NONE:
			switchFocus(FS_ID);
			break;
		case LoginScene::FS_ID:
			switchFocus(FS_PW);
			break;
		case LoginScene::FS_PW:
			switchFocus(FS_ID);
			break;
		default:
			break;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SHIFT
		&& mIsShiftPressed == true)
	{
		mIsShiftPressed = false;
	}
}

void LoginScene::update(float dtime)
{

	// on BackSpace
	if (mIsBackSpacePressed)
	{
		mBackSpaceTick += dtime;
		if ((mIsFirstPeriodForBackSpace == true && mBackSpaceTick >= mBackSpaceFirstPeriod)
			|| (mIsFirstPeriodForBackSpace == false && mBackSpaceTick >= mBackSpacePeriod))
		{
			mIsFirstPeriodForBackSpace = false;
			mBackSpaceTick = 0.f;
			switch (mFocusStatus)
			{
			case LoginScene::FS_NONE:
				break;
			case LoginScene::FS_ID:
				if (strlen(mID) > 0)mID[strlen(mID) - 1] = NULL;
				break;
			case LoginScene::FS_PW:
				if (strlen(mPassword) > 0)mPassword[strlen(mPassword) - 1] = NULL;
				break;
			default:
				break;
			}
		}
	}

	mCursorTick += dtime;
	if (mCursorTick > mCursorTickPeriod)
	{
		mCursorTick = 0.f;
		mIsCursorShow = !mIsCursorShow;
	}

	// Set TextFileds
	char bufID[1024] = "";
	char bufPW[1024] = "";
	if (strlen(mID) == 0)
	{
		if (mFocusStatus == FS_ID)
		{
			if (mIsCursorShow == true && mFocusStatus == FS_ID)
				bufID[0] = mCursor;
			else
				bufID[0] = ' ';
		}
		else
			WideCharToMultiByte(CP_UTF8, 0, mIDPlaceHolder, -1, bufID, sizeof(bufID), NULL, NULL);
	}
	else
	{
		strcpy(bufID, mID);
		if (mIsCursorShow == true && mFocusStatus == FS_ID)
		{
			memcpy(bufID + 1, bufID, sizeof(bufID) - 1);
			bufID[0] = ' ';
			bufID[strlen(bufID)] = mCursor;
		}
	}


	if (strlen(mPassword) == 0)
	{
		if (mFocusStatus == FS_PW)
		{
			if (mIsCursorShow == true)
				bufPW[0] = mCursor;
			else
				bufPW[0] = ' ';
		}
		else
			WideCharToMultiByte(CP_UTF8, 0, mPWPlaceHolder, -1, bufPW, sizeof(bufPW), NULL, NULL);
	}
	else
	{
		memset(bufPW, '*', strlen(mPassword));
		if (mIsCursorShow == true && mFocusStatus == FS_PW)
		{
			memcpy(bufPW + 1, bufPW, sizeof(bufPW) - 1);
			bufPW[0] = ' ';
			bufPW[strlen(bufPW)] = mCursor;
		}
	}
	mIDItem->setString(bufID);
	mPWItem->setString(bufPW);
}


void LoginScene::onMenuItemPressed(Ref* sender)
{
	if (sender == mLoginButtonItem)
	{
		tryLogin();
		switchFocus(FS_NONE);
	}
	else if (sender == mIDItem)
	{
		switchFocus(FS_ID);
	}
	else if (sender == mPWItem)
	{
		switchFocus(FS_PW);
	}
}

void LoginScene::switchFocus(FocusStatus focusStatus)
{
	//Pre
	switch (mFocusStatus)
	{
	case LoginScene::FS_NONE:
		break;
	case LoginScene::FS_ID:
		break;
	case LoginScene::FS_PW:
		break;
	default:
		break;
	}

	//Post
	//Actually Change focus type in here.
	switch (focusStatus)
	{
	case LoginScene::FS_NONE:
	{
		mFocusStatus = focusStatus;
		mIsCursorShow = false;
		mCursorTick = 0.f;
	}break;
	case LoginScene::FS_ID:
	{
		mFocusStatus = focusStatus;
		mIsCursorShow = true;
		mCursorTick = 0.f;
	}break;
	case LoginScene::FS_PW:
	{
		mFocusStatus = focusStatus;
		mIsCursorShow = true;
		mCursorTick = 0.f;
	}break;
	default:
		break;
	}
}

void LoginScene::onLoginResult(LoginResult inPacket)
{
	switch (inPacket.mResultType)
	{
	case LRT_SUCCEED:
	{
		//TODO
	}break;
	case LRT_WRONG_PW:
	{
		MessageBox("비밀번호가 틀렸습니다", "잘못된 비밀번호");
		switchFocus(FS_PW);
	}break;
	case LRT_NOT_REGIESTERED_ID:
	{
		auto signUpLayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName(SignUpLayer::layerName);

		if (signUpLayer != nullptr)
			signUpLayer->setVisible(true);
	}break;
	case LRT_WRONG_VALUE:
	{
		MessageBox("이상한 값이 입력되었습니다.\n입력하신 내용을 다시 확인해주세요.", "잘못된 값 입력");
		switchFocus(FS_ID);
	}
	default:
		break;
	}
}

void LoginScene::tryLogin()
{
	TcpClient::getInstance()->loginRequest(mID, mPassword);
}
