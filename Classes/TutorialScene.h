#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "BaseScene.h"

class TutorialScene: public BaseScene{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();
	CREATE_FUNC(TutorialScene)
	void soundButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void moreGameButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void rateButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void backButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
};



#endif // __SETTING_SCENE_H__
