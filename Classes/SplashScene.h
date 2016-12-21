#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "BaseScene.h"

class SplashScene: public BaseScene {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();
	void StartGameScene();
	void PreloadImages();
	void PreloadSounds();CREATE_FUNC(SplashScene)
	void dailyPuzzleButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void playButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void shopButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void settingButtonCallback(Ref* pSender,
			ui::Widget::TouchEventType eEventType);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void loadingImageCallback(
			cocos2d::Texture2D* resulting_texture);

	Button* btnPlay;
	Button* btnShop;
	Button* btnSetting;
	Button* btnDailyPuzzle;
	Sprite* loadingSprite;
	int loadedImageNumber;
};

#endif // __SPLASH_SCENE_H__
