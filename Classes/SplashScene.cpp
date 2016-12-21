#include "SplashScene.h"
#include "PacketScene.h"
#include "SettingScene.h"
#include "ShopScene.h"

Scene* SplashScene::scene() {
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	SplashScene *layer = SplashScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init() {
	bool result = BaseScene::init();
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
		return false;
	}

	loadedImageNumber = 0;
	//Add background
	Sprite* background = Sprite::create(s_splashscene_background);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(background);

	//Add loading sprite
	loadingSprite = Sprite::create(s_splashscene_loading_sprite);
	loadingSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	loadingSprite->setScale(1.2f);
	loadingSprite->setPosition(winSize.width / 2, winSize.height - 840);
	this->addChild(loadingSprite);
	loadingSprite->runAction(RepeatForever::create(RotateBy::create(1, 360)));

	//Add btn plau
	btnPlay = Button::create(s_splashscene_btn_play);
	btnPlay->setPosition(
			Vec2(-btnPlay->getContentSize().width / 2, winSize.height - 742));
	btnPlay->setTouchEnabled(true);
	btnPlay->setPressedActionEnabled(true);
	btnPlay->addTouchEventListener(
			CC_CALLBACK_2(SplashScene::playButtonCallback, this));
	this->addChild(btnPlay);

	//Add btn daily puzzle
	btnDailyPuzzle = Button::create(s_splashscene_btn_dailypuzzle);
	btnDailyPuzzle->setPosition(
			Vec2(winSize.width + btnDailyPuzzle->getContentSize().width / 2,
					winSize.height - 892));
	btnDailyPuzzle->setTouchEnabled(true);
	btnDailyPuzzle->setPressedActionEnabled(true);
	btnDailyPuzzle->addTouchEventListener(
			CC_CALLBACK_2(SplashScene::dailyPuzzleButtonCallback, this));
	this->addChild(btnDailyPuzzle);

	//Add btn shop
	btnShop = Button::create(s_splashscene_btn_shop);
	btnShop->setPosition(Vec2(238, -btnShop->getContentSize().height / 2));
	btnShop->setTouchEnabled(true);
	btnShop->setPressedActionEnabled(true);
	btnShop->addTouchEventListener(
			CC_CALLBACK_2(SplashScene::shopButtonCallback, this));
	this->addChild(btnShop);

	//Add btn setting
	btnSetting = Button::create(s_splashscene_btn_setting);
	btnSetting->setPosition(
			Vec2(530, -btnSetting->getContentSize().height / 2));
	btnSetting->setTouchEnabled(true);
	btnSetting->setPressedActionEnabled(true);
	btnSetting->addTouchEventListener(
			CC_CALLBACK_2(SplashScene::settingButtonCallback, this));
	this->addChild(btnSetting);

	SplashScene::PreloadSounds();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(SplashScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

void SplashScene::loadingImageCallback(cocos2d::Texture2D* resulting_texture) {
	loadedImageNumber++;
	if (loadedImageNumber >= sizeof s_imgloading / sizeof s_imgloading[0]) {
		loadedImageNumber = 0; //To prevent StartGameScene from being called 2 times
		this->runAction(
				CallFunc::create(
						std::bind(&SplashScene::StartGameScene, this)));
	}
}

void SplashScene::PreloadImages() {
	auto textureCache = Director::getInstance()->getTextureCache();
	int size = sizeof s_imgloading / sizeof s_imgloading[0];

	for (int var = 0; var < size; var++) {
		textureCache->addImageAsync(s_imgloading[var],
				CC_CALLBACK_1(SplashScene::loadingImageCallback, this));
	}
}

void SplashScene::PreloadSounds() {
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	int size = sizeof s_soundloading / sizeof s_soundloading[0];

	for (int var = 0; var < size; ++var) {
		audioEngine->preloadEffect(s_soundloading[var]);
	}

	this->runAction(
			CallFunc::create(std::bind(&SplashScene::PreloadImages, this)));
}

void SplashScene::StartGameScene() {
	//Hide loading sprite
	loadingSprite->setVisible(false);

	//Run buttons' actions
	float velocity = 1000; // 1000px/s
	btnPlay->runAction(
			MoveTo::create(
					(winSize.width * 0.5f - btnPlay->getPositionX()) / velocity,
					Vec2(winSize.width * 0.5, winSize.height - 722)));
	btnDailyPuzzle->runAction(
			MoveTo::create(
					(btnDailyPuzzle->getPositionX() - winSize.width * 0.5f)
							/ velocity,
					Vec2(winSize.width * 0.5, winSize.height - 892)));
	btnShop->runAction(
			MoveTo::create(
					((winSize.height - 961) - btnShop->getPositionY())
							/ velocity, Vec2(238, winSize.height - 1041)));
	btnSetting->runAction(
			MoveTo::create(
					((winSize.height - 961) - btnSetting->getPositionY())
							/ velocity, Vec2(530, winSize.height - 1041)));

	//Background music
	if (isSound) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
				s_gameon, true);
	}
}

void SplashScene::settingButtonCallback(Ref* pSender,
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
void SplashScene::shopButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = ShopScene::scene();
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}
void SplashScene::playButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = PacketScene::scene();
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}
void SplashScene::dailyPuzzleButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

//		auto *newScene = StickerScene::scene();
//		auto transition = TransitionFade::create(1.0, newScene);
//		Director *pDirector = Director::getInstance();
//		pDirector->replaceScene(transition);
	}
}

//TODO exist game if press back twice in 2 seconds
bool firstClickInHomeScene = true;
void SplashScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		if (firstClickInHomeScene) {
			if (isSound) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
						s_click);
			}

			firstClickInHomeScene = false;
			SocialPlugin::showToast("Press back again to Exit!");

			auto func = CallFunc::create([=]() {
				firstClickInHomeScene = true;
			});
			this->runAction(
					Sequence::create(DelayTime::create(2), func, nullptr));
		} else {
			CCDirector::sharedDirector()->end();
		}
	}
}
