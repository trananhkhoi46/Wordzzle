#include "MenuScene.h"
#include "HomeScene.h"

Scene* MenuScene::scene() {
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	MenuScene *layer = MenuScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init() {
	bool result = BaseScene::init();

	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
		return false;
	}

	TTFConfig config(s_font, 120 * s_font_ratio);

//	//Add background
//	Sprite* background = Sprite::create(s_menuscene_background);
//	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//	background->setPosition(winSize.width / 2, winSize.height / 2);
//	this->addChild(background);
//
//	//Add btn plau
//	Button* btnPlay = Button::create(s_menuscene_btn_play);
//	btnPlay->setPosition(Vec2(winSize.width * 0.5, winSize.height - 622));
//	btnPlay->setTouchEnabled(true);
//	btnPlay->setPressedActionEnabled(true);
//	btnPlay->addTouchEventListener(
//			CC_CALLBACK_2(MenuScene::playButtonCallback, this));
//	this->addChild(btnPlay);
//
//	//Add btn daily puzzle
//	Button* btnDailyPuzzle = Button::create(s_menuscene_btn_dailypuzzle);
//	btnDailyPuzzle->setPosition(Vec2(winSize.width * 0.5, winSize.height - 792));
//	btnDailyPuzzle->setTouchEnabled(true);
//	btnDailyPuzzle->setPressedActionEnabled(true);
//	btnDailyPuzzle->addTouchEventListener(
//			CC_CALLBACK_2(MenuScene::dailyPuzzleButtonCallback, this));
//	this->addChild(btnDailyPuzzle);
//
//	//Add btn shop
//	Button* btnShop = Button::create(s_menuscene_btn_shop);
//	btnShop->setPosition(Vec2(240, winSize.height - 961));
//	btnShop->setTouchEnabled(true);
//	btnShop->setPressedActionEnabled(true);
//	btnShop->addTouchEventListener(
//			CC_CALLBACK_2(MenuScene::shopButtonCallback, this));
//	this->addChild(btnShop);
//
//	//Add btn setting
//	Button* btnSetting = Button::create(s_menuscene_btn_setting);
//	btnSetting->setPosition(Vec2(551, winSize.height - 961));
//	btnSetting->setTouchEnabled(true);
//	btnSetting->setPressedActionEnabled(true);
//	btnSetting->addTouchEventListener(
//			CC_CALLBACK_2(MenuScene::settingButtonCallback, this));
//	this->addChild(btnSetting);
//
//	//Keyboard handling
//	auto keyboardListener = EventListenerKeyboard::create();
//	keyboardListener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased,
//			this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
//			this);

	return result;
}
void MenuScene::settingButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {

	}
}
void MenuScene::shopButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {

	}
}
void MenuScene::playButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {

	}
}
void MenuScene::dailyPuzzleButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {

	}
}
void MenuScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = HomeScene::scene();
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}
