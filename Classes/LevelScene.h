#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "BaseScene.h"

class LevelScene: public BaseScene{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene(int riddle_packet_id);
	CREATE_FUNC(LevelScene)
	void facebookButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void backButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void initRiddleButtons();
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
};



#endif
