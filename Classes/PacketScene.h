#ifndef __PACKET_SCENE_H__
#define __PACKET_SCENE_H__

#include "BaseScene.h"

class PacketScene: public BaseScene{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();
	CREATE_FUNC(PacketScene)
	void facebookButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void backButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void initPacketButtons();
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
};



#endif
