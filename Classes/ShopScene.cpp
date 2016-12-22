#include "ShopScene.h"
#include "SplashScene.h"

Scene* ShopScene::scene() {
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	ShopScene *layer = ShopScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ShopScene::init() {
	bool result = BaseScene::init();

	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
		return false;
	}

	isChartboostAdsAvailable = false;
	isVungleAdsAvailable = false;
	TTFConfig config(s_font, 120 * s_font_ratio);
#ifdef SDKBOX_ENABLED
	PluginAdMob::setListener(this);
	PluginChartboost::setListener(this);
	IAP::setDebug(true);
	IAP::setListener(this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	PluginVungle::setListener(this);
	PluginVungle::setDebug(true);
#endif
#endif

	//Add background
	Sprite* background = Sprite::create(s_background);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(background);

	//Add board
	Sprite* board = Sprite::create(s_shopscene_board);
	board->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	board->setPosition(winSize.width / 2, winSize.height / 2 + 20);
	this->addChild(board);

	//Add btn back
	Button* btnBack = Button::create(s_shopscene_btn_close);
	btnBack->setPosition(Vec2(565, board->getContentSize().height - 42));
	btnBack->setTouchEnabled(true);
	btnBack->setPressedActionEnabled(true);
	btnBack->addTouchEventListener(
			CC_CALLBACK_2(ShopScene::backButtonCallback, this));
	board->addChild(btnBack);

	//Add scrollview
	initIAPButtons();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(ShopScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

Product ShopScene::getIAPProductById(string id) {
	vector<Product> vtProducts = IAP::getProducts();
	for (Product product : vtProducts)
		if (product.name == id) {
			if (product.price == "") {
				product.price = "?";
			}
			return product;
		}
	Product product;
	return product;
}

void ShopScene::initIAPButtons() {
	//Scrollview configuration
	TTFConfig configLabelRiddleLevel(s_font, 40 * s_font_ratio);
	TTFConfig configLabelRiddleName(s_font, 20 * s_font_ratio);
	TTFConfig configLabelIAPPrice(s_font, 20 * s_font_ratio);
	int numberOfItems = 7;
	int scrollviewMarginTop = 165;
	int scrollviewMarginBottom = 140;
	float itemMargin = 140;
	Size scrollFrameSize = Size(winSize.width,
			winSize.height - scrollviewMarginTop - scrollviewMarginBottom);

	//Create scrollview
	BScrollView* scrollview = BScrollView::createVertical(numberOfItems,
			itemMargin, scrollFrameSize);
	scrollview->setPosition(
			Vec2(winSize.width / 2,
					winSize.height / 2 - scrollviewMarginTop / 2
							+ scrollviewMarginBottom / 2));
//	scrollview->setBackGroundColorType(Layout::BackGroundColorType::SOLID); //Background
//	scrollview->setBackGroundColor(Color3B(200, 200, 200)); //Background
	scrollview->setScrollBarEnabled(false);
	CCLog("bambi ShopScene - inner height: %f, frame hight: %f",
			scrollview->getInnerContainerSize().height, scrollFrameSize.height);
	if (scrollview->getInnerContainerSize().height <= scrollFrameSize.height) {
		scrollview->setBounceEnabled(false);
	}
	this->addChild(scrollview);

	//Add sth to scroll view
	float positionX = scrollview->leftPosition;
	float positionY = scrollview->topPosition;
	for (int i = 0; i < numberOfItems; i++) {
		string iapName = "";
		string iapDescription = "";
		string iapPrice = "";
		string iapKey = "";
		switch (i) {
		case 0: {
			iapName = "1 Free hint!";
			iapDescription = "Watch a video for a free hint!";
			iapPrice = "Free";
		}
			break;
		case 1: {
			iapName = IAP_PACK1_NAME;
			iapDescription = IAP_PACK1_DESCRIPTION;
			Product product;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			product = getIAPProductById(IAP_IOS_PACK1_KEY);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			product = getIAPProductById(IAP_ANDROID_PACK1_KEY);
#endif
			iapPrice = product.price;
			iapKey = product.name;
		}
			break;
		case 2: {
			iapName = IAP_PACK2_NAME;
			iapDescription = IAP_PACK2_DESCRIPTION;
			Product product;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			product = getIAPProductById(IAP_IOS_PACK2_KEY);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			product = getIAPProductById(IAP_ANDROID_PACK2_KEY);
#endif
			iapPrice = product.price;
			iapKey = product.name;
		}
			break;
		case 3: {
			iapName = IAP_PACK3_NAME;
			iapDescription = IAP_PACK3_DESCRIPTION;
			Product product;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			product = getIAPProductById(IAP_IOS_PACK3_KEY);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			product = getIAPProductById(IAP_ANDROID_PACK3_KEY);
#endif
			iapPrice = product.price;
			iapKey = product.name;
		}
			break;
		case 4: {
			iapName = IAP_PACK4_NAME;
			iapDescription = IAP_PACK4_DESCRIPTION;
			Product product;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			product = getIAPProductById(IAP_IOS_PACK4_KEY);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			product = getIAPProductById(IAP_ANDROID_PACK4_KEY);
#endif
			iapPrice = product.price;
			iapKey = product.name;
		}
			break;
		case 5: {
			iapName = IAP_PACK5_NAME;
			iapDescription = IAP_PACK5_DESCRIPTION;
			Product product;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			product = getIAPProductById(IAP_IOS_PACK5_KEY);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			product = getIAPProductById(IAP_ANDROID_PACK5_KEY);
#endif
			iapPrice = product.price;
			iapKey = product.name;
		}
			break;
		case 6: {
			iapName = IAP_PACK6_NAME;
			iapDescription = IAP_PACK6_DESCRIPTION;
			Product product;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			product = getIAPProductById(IAP_IOS_PACK6_KEY);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			product = getIAPProductById(IAP_ANDROID_PACK6_KEY);
#endif
			iapPrice = product.price;
			iapKey = product.name;
		}
			break;
		}

		//Add btn shop;
		Button* btnShop = Button::create(
				s_levelscene_level_holders[i
						% (sizeof s_levelscene_level_holders
								/ sizeof s_levelscene_level_holders[0])]);
		btnShop->setPosition(Vec2(scrollFrameSize.width * 0.5f, positionY));
		btnShop->setTouchEnabled(true);
		btnShop->setZoomScale(0);
		btnShop->setPressedActionEnabled(false);
		scrollview->addChild(btnShop);

		//Add holder image
		Sprite* holderImage = Sprite::create(s_levelscene_active_holder);
		holderImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		holderImage->setPosition(
				Vec2(btnShop->getContentSize().width / 2,
						btnShop->getContentSize().height / 2));
		btnShop->addChild(holderImage);

		//Add btn IAP
		Button* btnIAP = Button::create(s_shopscene_btn_shop);
		btnIAP->setPosition(Vec2(455, btnShop->getContentSize().height / 2));
		btnIAP->setTouchEnabled(true);
		btnIAP->setZoomScale(0);
		btnIAP->setPressedActionEnabled(false);
		btnIAP->addTouchEventListener(
				[this,btnIAP, i, iapKey](Ref *pSender,
						Widget::TouchEventType type) {
					if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
					{
						btnIAP->setScale(1);
						if(isSound) {
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_click);
						}

						if(i == 0) {
							showRewardedAds();
						} else {
							IAP::purchase(iapKey);
						}
					}
					else if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
					{
						btnIAP->setScale(1.05f);
					} else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED) {
						btnIAP->setScale(1);
					}});
		btnShop->addChild(btnIAP);
		//Add label IAP price
		Label* labelPrice = Label::createWithTTF(configLabelIAPPrice, iapPrice,
				TextHAlignment::CENTER);
		labelPrice->setPosition(
				Vec2(btnIAP->getContentSize().width / 2,
						btnIAP->getContentSize().height / 2));
		labelPrice->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		labelPrice->setColor(Color3B::WHITE);
		btnIAP->addChild(labelPrice);

		//Add icon
		Sprite* icon = Sprite::create(
				i == 0 ? s_shopscene_sprite_video_rewarded : s_shopscene_tick);
		icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		icon->setPosition(Vec2(80, btnShop->getContentSize().height / 2));
		btnShop->addChild(icon);

		//Add label IAP name
		Label* labelName = Label::createWithTTF(configLabelRiddleLevel, iapName,
				TextHAlignment::LEFT);
		labelName->setPosition(Vec2(136, 75));
		labelName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		labelName->setColor(Color3B::BLACK);
		btnShop->addChild(labelName);

		//Add label IAP description
		Label* labelLevelNumber = Label::createWithTTF(configLabelRiddleName,
				iapDescription, TextHAlignment::LEFT);
		labelLevelNumber->setPosition(Vec2(136, 35));
		labelLevelNumber->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		labelLevelNumber->setColor(Color3B::BLACK);
		btnShop->addChild(labelLevelNumber);

		positionY -= itemMargin;
	}
}

void ShopScene::backButtonCallback(Ref* pSender,
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

void ShopScene::facebookButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		PluginFacebook::inviteFriends(FACEBOOK_INVITE_APP_URL,
		FACEBOOK_INVITE_IMAGE_URL);
	}
}
void ShopScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
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

void ShopScene::earnFreeStickerAfterWatchingAds() {
	RiddleHelper::receiveHints(1);
}

bool isShowingAds = false;
void ShopScene::showRewardedAds() {
	if (isShowingAds) {
		return;
	}
	isShowingAds = true;
	auto func = CallFunc::create([=]() {
		isShowingAds = false;
	});
	this->runAction(Sequence::create(DelayTime::create(1), func, nullptr));

	CCLog("bambi ShopScene -> showRewardedAds");
#ifdef SDKBOX_ENABLED
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(CppUtils::randomBetween(1,2) == 1) {
		if(PluginChartboost::isAvailable(kChartboostRewardedAds))
		{
			PluginChartboost::show(kChartboostRewardedAds);
		} else
		{
			PluginVungle::show(kVungleRewardedAds);
		}
	} else {
		if(PluginVungle::isCacheAvailable())
		{
			PluginVungle::show(kVungleRewardedAds);
		} else
		{
			PluginChartboost::show(kChartboostRewardedAds);
		}
	}
#else
	PluginChartboost::show(kChartboostRewardedAds);
#endif

#endif
}

//IAP + Ads callbacks
//IAP
void ShopScene::onInitialized(bool success) {
}
void ShopScene::onSuccess(const Product& p) {
	if (p.name == IAP_ANDROID_PACK1_KEY || IAP_IOS_PACK1_KEY) {
		RiddleHelper::receiveHints(IAP_HINT_NUMBER_TO_GET_PACK1);
	} else if (p.name == IAP_ANDROID_PACK2_KEY || IAP_IOS_PACK2_KEY) {
		RiddleHelper::receiveHints(IAP_HINT_NUMBER_TO_GET_PACK2);
	} else if (p.name == IAP_ANDROID_PACK3_KEY || IAP_IOS_PACK3_KEY) {
		RiddleHelper::receiveHints(IAP_HINT_NUMBER_TO_GET_PACK3);
	} else if (p.name == IAP_ANDROID_PACK4_KEY || IAP_IOS_PACK4_KEY) {
		RiddleHelper::receiveHints(IAP_HINT_NUMBER_TO_GET_PACK4);
	} else if (p.name == IAP_ANDROID_PACK5_KEY || IAP_IOS_PACK5_KEY) {
		RiddleHelper::receiveHints(IAP_HINT_NUMBER_TO_GET_PACK5);
	} else if (p.name == IAP_ANDROID_PACK6_KEY || IAP_IOS_PACK6_KEY) {
		RiddleHelper::receiveHints(IAP_HINT_NUMBER_TO_GET_PACK6);
	}
}
void ShopScene::onFailure(const Product& p, const std::string& msg) {
}
void ShopScene::onCanceled(const Product& p) {
}
void ShopScene::onRestored(const Product& p) {
}
void ShopScene::onProductRequestSuccess(
		const std::vector<Product>& products) {
}
void ShopScene::onProductRequestFailure(const std::string& msg) {
}
void ShopScene::onRestoreComplete(bool ok, const std::string &msg) {
}
//Admob
void ShopScene::adViewDidReceiveAd(const std::string &name) {
}
void ShopScene::adViewDidFailToReceiveAdWithError(const std::string &name,
		const std::string &msg) {
}
void ShopScene::adViewWillPresentScreen(const std::string &name) {
}
void ShopScene::adViewDidDismissScreen(const std::string &name) {
}
void ShopScene::adViewWillDismissScreen(const std::string &name) {
	PluginAdMob::cache(name);
}
void ShopScene::adViewWillLeaveApplication(const std::string &name) {
}
//Chartboost
void ShopScene::onChartboostCached(const std::string& name) {
	isChartboostAdsAvailable = true;
}
bool ShopScene::onChartboostShouldDisplay(const std::string& name) {
	return true;
}
void ShopScene::onChartboostDisplay(const std::string& name) {
}
void ShopScene::onChartboostDismiss(const std::string& name) {
}
void ShopScene::onChartboostClose(const std::string& name) {
}
void ShopScene::onChartboostClick(const std::string& name) {
}
void ShopScene::onChartboostReward(const std::string& name, int reward) {
	//TODO get a free hint here
	isChartboostAdsAvailable = false;
}
void ShopScene::onChartboostFailedToLoad(const std::string& name,
		CB_LoadError e) {
}
void ShopScene::onChartboostFailToRecordClick(const std::string& name,
		CB_ClickError e) {
}
void ShopScene::onChartboostConfirmation() {
}
void ShopScene::onChartboostCompleteStore() {
}
//Vungle
void ShopScene::onVungleCacheAvailable() {
	isVungleAdsAvailable = true;
}
void ShopScene::onVungleStarted() {
}
void ShopScene::onVungleFinished() {
}
void ShopScene::onVungleAdViewed(bool isComplete) {
}
void ShopScene::onVungleAdReward(const std::string& name) {
	cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread(
			[=]() {
				//TODO get a free hint here
				isVungleAdsAvailable = false;
			});
}
