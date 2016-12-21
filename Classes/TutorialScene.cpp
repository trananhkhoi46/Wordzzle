#include "TutorialScene.h"
#include "SplashScene.h"

Scene* TutorialScene::scene() {
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	TutorialScene *layer = TutorialScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TutorialScene::init() {
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
			CC_CALLBACK_2(TutorialScene::backButtonCallback, this));
	board->addChild(btnBack);

	//Add btn sound
	Button* btnSound = Button::create(
			isSound ?
					s_settingscene_btn_sound_on :
					s_settingscene_btn_sound_off);
	btnSound->setPosition(Vec2(board->getContentSize().width / 2, 545));
	btnSound->setTouchEnabled(true);
	btnSound->setPressedActionEnabled(true);
	btnSound->addTouchEventListener(
			CC_CALLBACK_2(TutorialScene::soundButtonCallback, this));
	board->addChild(btnSound);

	//Add btn more game
	Button* btnMoreGame = Button::create(s_settingscene_btn_tutorial);
	btnMoreGame->setPosition(Vec2(board->getContentSize().width / 2, 410));
	btnMoreGame->setTouchEnabled(true);
	btnMoreGame->setPressedActionEnabled(true);
	btnMoreGame->addTouchEventListener(
			CC_CALLBACK_2(TutorialScene::moreGameButtonCallback, this));
	board->addChild(btnMoreGame);

	//Add btn rate
	Button* btnRate = Button::create(s_settingscene_btn_rate);
	btnRate->setPosition(Vec2(board->getContentSize().width / 2, 275));
	btnRate->setTouchEnabled(true);
	btnRate->setPressedActionEnabled(true);
	btnRate->addTouchEventListener(
			CC_CALLBACK_2(TutorialScene::rateButtonCallback, this));
	board->addChild(btnRate);

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(TutorialScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

void TutorialScene::soundButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		Button* button = dynamic_cast<Button*>(pSender);
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}
		isSound = !isSound;
		if(!isSound){
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
		}else{
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
					s_gameon, true);
		}
		UserDefault::getInstance()->setBoolForKey(SOUND, isSound);
		button->loadTextureNormal(
				isSound ?
						s_settingscene_btn_sound_on :
						s_settingscene_btn_sound_off, TextureResType::LOCAL);
	}
}
void TutorialScene::moreGameButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		Application::getInstance()->openURL(s_linkToAppStoreMoreGame);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		Application::getInstance()->openURL(s_linkToGooglePlayMoreGame);
#endif
	}
}
void TutorialScene::rateButtonCallback(Ref* pSender,
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
void TutorialScene::backButtonCallback(Ref* pSender,
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

void TutorialScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
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
