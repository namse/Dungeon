#include "SignUpLayer.h"
#include "base/CCEventKeyboard.h"
#include "TcpClient.h"
#include "../../PacketType.h"
#include "LoginScene.h"

// on "init" you need to initialize your instance
bool SignUpLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(ccc4(127, 127, 80, 255)))
	{
		return false;
	}

	memset(mName, 0, sizeof(mName));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size nameBoxSize = Size(100.f, 40.f);
	mNameEditBox = EditBox::create(nameBoxSize, Scale9Sprite::create("extensions/green_edit.png"));

	mNameEditBox->setPosition(Vec2(visibleSize.width / 2.f , visibleSize.height * 3.f / 4.f));
	mNameEditBox->setAnchorPoint(ccp(0.5f, 0.5f));
	mNameEditBox->setFontName("맑은 고딕");
	mNameEditBox->setFontSize(30);
	mNameEditBox->setFontColor(ccBLACK);
	mNameEditBox->setPlaceHolder(">클릭<");
	addChild(mNameEditBox);

	// Sign Up Button Init
	{
		char buf[1024];
		WideCharToMultiByte(CP_UTF8, 0, L"<로그인>", -1, buf, sizeof(buf), NULL, NULL);
		mSignUpButtonItem = MenuItemFont::create(
			buf,
			this,
			menu_selector(SignUpLayer::onMenuItemClicked));
		mSignUpButtonItem->setAnchorPoint(Vec2(0.5f, 0.5f));
		mSignUpButtonItem->setFontNameObj("맑은 고딕");
		mSignUpButtonItem->setFontSizeObj(30);
		mSignUpButtonItem->setColor(ccBLACK);
	}

	// Exit Button Init
	{
		char buf[1024];
		WideCharToMultiByte(CP_UTF8, 0, L"혹시 뭔가 잘못되었나요?", -1, buf, sizeof(buf), NULL, NULL);
		mExitButtonItem = MenuItemFont::create(
			buf,
			this,
			menu_selector(SignUpLayer::onMenuItemClicked));
		mExitButtonItem->setAnchorPoint(Vec2(0.5f, 0.5f));
		mExitButtonItem->setFontNameObj("맑은 고딕");
		mExitButtonItem->setFontSizeObj(10);
		mExitButtonItem->setColor(ccBLACK);
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(mSignUpButtonItem, mExitButtonItem, NULL);
	menu->setPosition(ccp(visibleSize.width / 2.f, visibleSize.height * 1.f / 4.f));
	this->addChild(menu, 1);
	menu->alignItemsVertically();

	this->setKeyboardEnabled(true);
	return true;
}

void SignUpLayer::onMenuItemClicked(Ref* sender)
{
	if (sender == mSignUpButtonItem)
	{
		char id[1024] = "";
		char pw[1024] = "";
		wchar_t name[1024] = L"";
		MultiByteToWideChar(CP_UTF8, 0, mNameEditBox->getText(), -1, name, sizeof(name));

		auto loginScene = dynamic_cast<LoginScene*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName(std::string("login_scene_layer")));
		if (loginScene == nullptr)
			return;

		strcpy(id, loginScene->getID());
		strcpy(pw, loginScene->getPW());

		WCHAR buf[1024] = L"";
		TcpClient::getInstance()->signUpRequest(id, pw, name);
	}
	else if (sender == mExitButtonItem)
	{
		setVisible(false);
	}
}

void SignUpLayer::onSignUpResult(SignUpResult outPacket)
{

}

void SignUpLayer::editBoxEditingDidEnd(EditBox* editBox)
{
	wchar_t name[1024] = L"";
	MultiByteToWideChar(CP_UTF8, 0, mNameEditBox->getText(), -1, name, sizeof(name));
	
	if (wcslen(name) > MAX_NAME_LEN)
	{
		char buf[1024]="";
		sprintf(buf, "이름이 너무 길어요. \n%d글자 이내로 지어주세요.", MAX_NAME_LEN);
		MessageBox(buf, "긴 이름 ㄴㄴ해");
		
		memset(buf, 0, sizeof(buf));
		WideCharToMultiByte(CP_UTF8, 0, name, MAX_NAME_LEN, buf, sizeof(buf), NULL, NULL);
		mNameEditBox->setText(buf);
	}
}
