#include "SettingScene.h"
#include "SplashScene.h"
#include "TutorialScene.h"

Scene* SettingScene::scene() {
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	SettingScene *layer = SettingScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init() {
	bool result = BaseScene::init();

	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
		return false;
	}
    
    
	//Add background
	Sprite* background = Sprite::create(s_background);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(background);

	//Add board
	Sprite* board = Sprite::create(s_settingscene_board_setting);
	board->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	board->setPosition(winSize.width / 2, winSize.height - 594);
	this->addChild(board);

	//Add btn back
	Button* btnBack = Button::create(s_settingscene_btn_close);
	btnBack->setPosition(Vec2(565, board->getContentSize().height - 42));
	btnBack->setTouchEnabled(true);
	btnBack->setPressedActionEnabled(true);
	btnBack->addTouchEventListener(
			CC_CALLBACK_2(SettingScene::backButtonCallback, this));
	board->addChild(btnBack);

	//Add btn sound
	Button* btnSound = Button::create(
			isSound ?
					s_settingscene_btn_sound_on : s_settingscene_btn_sound_off);
	btnSound->setPosition(Vec2(board->getContentSize().width / 2, 545 - 90));
	btnSound->setTouchEnabled(true);
	btnSound->setPressedActionEnabled(true);
	btnSound->addTouchEventListener(
			CC_CALLBACK_2(SettingScene::soundButtonCallback, this));
	board->addChild(btnSound);
    
    //Add btn music
    Button* btnMusic = Button::create(
                                      isMusic ?
                                      s_settingscene_btn_music_on : s_settingscene_btn_music_off);
    btnMusic->setPosition(Vec2(board->getContentSize().width / 2, 680 - 90));
    btnMusic->setTouchEnabled(true);
    btnMusic->setPressedActionEnabled(true);
    btnMusic->addTouchEventListener(
                                    CC_CALLBACK_2(SettingScene::musicButtonCallback, this));
    board->addChild(btnMusic);
    
    //Add btn more game
	Button* btnTutorial = Button::create(s_settingscene_btn_tutorial);
	btnTutorial->setPosition(Vec2(board->getContentSize().width / 2, 410 - 90));
	btnTutorial->setTouchEnabled(true);
	btnTutorial->setPressedActionEnabled(true);
	btnTutorial->addTouchEventListener(
			CC_CALLBACK_2(SettingScene::tutorialButtonCallback, this));
	board->addChild(btnTutorial);

	//Add btn rate
	Button* btnRate = Button::create(s_settingscene_btn_rate);
	btnRate->setPosition(Vec2(board->getContentSize().width / 2, 275 - 90));
	btnRate->setTouchEnabled(true);
	btnRate->setPressedActionEnabled(true);
	btnRate->addTouchEventListener(
			CC_CALLBACK_2(SettingScene::rateButtonCallback, this));
	board->addChild(btnRate);

	//Add ads banner
	addBottomBanner();
	showAdsBanner();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(SettingScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

void SettingScene::soundButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		Button* button = dynamic_cast<Button*>(pSender);
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}
		isSound = !isSound;
		UserDefault::getInstance()->setBoolForKey(SOUND, isSound);
		button->loadTextureNormal(
				isSound ?
						s_settingscene_btn_sound_on :
						s_settingscene_btn_sound_off, TextureResType::LOCAL);
	}
}
void SettingScene::musicButtonCallback(Ref* pSender,
                                       ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        Button* button = dynamic_cast<Button*>(pSender);
       
        isMusic = !isMusic;
        if (!isMusic) {
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(
                                                                                 false);
        } else {
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
                                                                                 s_gameon, true);
        }
        UserDefault::getInstance()->setBoolForKey(MUSIC, isMusic);
        button->loadTextureNormal(
                                  isMusic ?
                                  s_settingscene_btn_music_on :
                                  s_settingscene_btn_music_off, TextureResType::LOCAL);
    }
}
void SettingScene::tutorialButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = TutorialScene::scene();
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}
void SettingScene::rateButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}
        
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		Application::getInstance()->openURL(s_linkToAppStoreRating);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		Application::getInstance()->openURL(s_linkToGooglePlayRating);
#endif
	}
}
void SettingScene::backButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}
        
		auto *newScene = SplashScene::scene();
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}

void SettingScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}
        
		auto *newScene = SplashScene::scene();
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}
