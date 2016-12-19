#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "BaseScene.h"

class MenuScene: public BaseScene{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();
	CREATE_FUNC(MenuScene)
	void dailyPuzzleButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void playButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void shopButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void settingButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
};



#endif
