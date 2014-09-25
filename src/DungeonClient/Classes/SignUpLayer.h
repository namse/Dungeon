#ifndef __SIGNUP_LAYER_H__
#define __SIGNUP_LAYER_H__

#include "cocos2d.h"
#include "../../PacketType.h"
#include "../extensions/GUI/CCEditBox/CCEditBox.h"

USING_NS_CC;
USING_NS_CC_EXT;



class SignUpLayer : public cocos2d::LayerColor, public EditBoxDelegate
{
public:
	static const std::string layerName;

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(SignUpLayer);

	void onSignUpResult(SignUpResult	outPacket);
	virtual void editBoxEditingDidBegin(EditBox* editBox) {};
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) {};
	virtual void editBoxReturn(EditBox* editBox) {};
private:
	void onMenuItemClicked(Ref* sender);
	
	EditBox*			mNameEditBox = nullptr;
	MenuItemFont* mSignUpButtonItem = nullptr;
	MenuItemFont* mExitButtonItem = nullptr;
	
};

#endif // __SIGNUP_LAYER_H__
