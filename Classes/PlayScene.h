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
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	string getAnswerStringFromTag(int tag);
	int getTagFromAnswerStringPosition(int i, int j);
	void giveUserAHint();
	void updateUIGetMoreHintButton();
	void addRiddleAnswerMatrix();
	void addRiddleAnswer();
	void updateNinePathHintHolder();
	bool checkGameWin();
	bool checkTheAnswerMatrixSpriteIsValid(Sprite* sprite);

	bool isTouchedOnAnswerMatrix;
	Label* labelHint;
	Label* labelHintOfTheRiddle;
	Sprite* hintHolder;
	Sprite* hintHolderLeft;
	Sprite* hintHolderRight;
	Button* btnHint;
	string currentAnswer;
	string touchingAnswer;
	vector<Sprite*> vtSpriteAnswer;
	vector<Sprite*> vtSpriteAnswerMatrix;
	vector<int> vtPoints;
	Sprite* mostLastestTouchedSpriteAnswerMatrix;
};



#endif
