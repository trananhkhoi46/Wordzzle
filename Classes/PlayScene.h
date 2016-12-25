#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "BaseScene.h"

class PlayScene: public BaseScene{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene(Riddle* riddle);
	CREATE_FUNC(PlayScene)
	void backButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void getMoreHintButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void restartButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void shopButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	void giveUserAHint();
	void updateUIGetMoreHintButton();
	void addRiddleAnswerMatrix();
	void addRiddleAnswer();

	Label* labelHint;
	Button* btnHint;
};



#endif
