#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "BaseScene.h"

class TutorialScene: public BaseScene{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();
	static cocos2d::Scene* scene(int tutorialPage);
		CREATE_FUNC(TutorialScene)
	void gotItButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void backButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
    bool touchable;
    Sprite* tutorialText;
    Sprite* tutorial;
    Button* btnGotIt;
};



#endif // __SETTING_SCENE_H__
