#include "TutorialScene.h"
#include "SettingScene.h"

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
	Sprite* board = Sprite::create(s_tutorialscene_board);
	board->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	board->setPosition(winSize.width / 2, winSize.height - 674);
	this->addChild(board);

	//Add title
	Sprite* title = Sprite::create(s_tutorialscene_title);
	title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	title->setPosition(winSize.width / 2, winSize.height - 80);
	this->addChild(title);

	//Add tutorial
	Sprite* tutorial = Sprite::create(s_tutorialscene_tutorial);
	tutorial->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	tutorial->setPosition(winSize.width / 2, winSize.height / 2 + 30);
	this->addChild(tutorial);
    Vector<SpriteFrame*> animFrames(19);
    char str[254] = {0};
    for(int i = 1; i < 20; i++)
    {
        auto frame = SpriteFrame::create(s_tutorialscene_gif[i],Rect(0,0,758,500));
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);
    tutorial->runAction(RepeatForever::create(animate));


	//Add btn got it
	Button* btnGotIt = Button::create(s_tutorialscene_btn_got_it);
	btnGotIt->setPosition(Vec2(board->getContentSize().width / 2, 90));
	btnGotIt->setTouchEnabled(true);
	btnGotIt->setPressedActionEnabled(true);
	btnGotIt->addTouchEventListener(
			CC_CALLBACK_2(TutorialScene::gotItButtonCallback, this));
	board->addChild(btnGotIt);

	//Add ads banner
	addBottomBanner();
	showAdsBanner();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(TutorialScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

void TutorialScene::gotItButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = SettingScene::scene();
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}

void TutorialScene::backButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = SettingScene::scene();
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

		auto *newScene = SettingScene::scene();
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}
