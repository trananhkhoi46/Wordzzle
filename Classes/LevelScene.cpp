#include "LevelScene.h"
#include "PacketScene.h"

int riddlePacketId;
Scene* LevelScene::scene(int riddle_packet_id) {
	riddlePacketId = riddle_packet_id;

	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	LevelScene *layer = LevelScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelScene::init() {
	bool result = BaseScene::init();

	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
		return false;
	}

	TTFConfig config(s_font, 120 * s_font_ratio);

	//Add background
	Sprite* background = Sprite::create(s_background);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(background);

	//Add btn facebook
	Button* btnFacebook = Button::create(s_levelscene_btn_facebook);
	btnFacebook->setPosition(Vec2(677, winSize.height - 71));
	btnFacebook->setTouchEnabled(true);
	btnFacebook->setPressedActionEnabled(true);
	btnFacebook->addTouchEventListener(
			CC_CALLBACK_2(LevelScene::facebookButtonCallback, this));
	this->addChild(btnFacebook);

	//Add btn back
	Button* btnBack = Button::create(s_levelscene_btn_back);
	btnBack->setPosition(Vec2(91, winSize.height - 71));
	btnBack->setTouchEnabled(true);
	btnBack->setPressedActionEnabled(true);
	btnBack->addTouchEventListener(
			CC_CALLBACK_2(LevelScene::backButtonCallback, this));
	this->addChild(btnBack);

	//Add title
	Button* title = Button::create(s_levelscene_title);
	title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	title->setPosition(Vec2(winSize.width / 2, winSize.height - 71));
	this->addChild(title);

	//Add scrollview
	initRiddleButtons();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(LevelScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

void LevelScene::initRiddleButtons() {
	//Get riddles belong to the packet
	vector<Riddle*> vt_riddles_of_this_packet =
			RiddleHelper::getRiddlesOfThePacket(riddlePacketId);

	//Scrollview configuration
	TTFConfig configLabelRiddleLevel(s_font, 45 * s_font_ratio);
	TTFConfig configLabelRiddleName(s_font_thin, 30 * s_font_ratio);
	int numberOfItems = vt_riddles_of_this_packet.size();
	int scrollviewMarginTop = 150;
	int scrollviewMarginBottom = 150;
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
	CCLog("bambi LevelScene - inner height: %f, frame hight: %f",
			scrollview->getInnerContainerSize().height, scrollFrameSize.height);
	if (scrollview->getInnerContainerSize().height <= scrollFrameSize.height) {
		scrollview->setBounceEnabled(false);
	}
	this->addChild(scrollview);

	//Add sth to scroll view
	float positionX = scrollview->leftPosition;
	float positionY = scrollview->topPosition;
	for (int i = 0; i < numberOfItems; i++) {
		Riddle* riddle = vt_riddles_of_this_packet.at(i);
		bool isRiddleActive = RiddleHelper::isRiddleActive(riddle->riddle_id);

		//Add btn packet
		Button* btnLevel = Button::create(
				s_levelscene_level_holders[i
						% (sizeof s_levelscene_level_holders
								/ sizeof s_levelscene_level_holders[0])]);
		btnLevel->setPosition(Vec2(scrollFrameSize.width * 0.5f, positionY));
		btnLevel->setTouchEnabled(true);
		btnLevel->setZoomScale(0);
		btnLevel->setPressedActionEnabled(false);
		btnLevel->setPressedActionEnabled(true);
		btnLevel->addTouchEventListener(
				[this,isRiddleActive,riddle,btnLevel](Ref *pSender,
						Widget::TouchEventType type) {
					if (type == cocos2d::ui::Widget::TouchEventType::ENDED && isRiddleActive)
					{
						btnLevel->setScale(1);
						if(isSound) {
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_click);
						}
						SocialPlugin::showToast("Ahihi");
					}
					else if (type == cocos2d::ui::Widget::TouchEventType::BEGAN && isRiddleActive)
					{
						btnLevel->setScale(1.05f);
					} else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED && isRiddleActive) {
						btnLevel->setScale(1);
					}});
		scrollview->addChild(btnLevel);

		//Add holder image
		Sprite* holderImage = Sprite::create(s_levelscene_active_holder);
		holderImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		holderImage->setPosition(
				Vec2(btnLevel->getContentSize().width / 2,
						btnLevel->getContentSize().height / 2));
		btnLevel->addChild(holderImage);

		if (isRiddleActive) {
			//Add icon
			Sprite* icon = Sprite::create(s_levelscene_tick);
			icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			icon->setPosition(Vec2(80, btnLevel->getContentSize().height / 2));
			btnLevel->addChild(icon);
		}

		//Add label riddle level
		Label* labelName =
				Label::createWithTTF(configLabelRiddleLevel,
						String::createWithFormat("Level %d",
								riddle->riddle_level)->getCString(),
						TextHAlignment::CENTER);
		labelName->setPosition(
				Vec2(btnLevel->getContentSize().width / 2 + 10, 75));
		labelName->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		labelName->setColor(Color3B::BLACK);
		labelName->setOpacity(isRiddleActive ? 255 : 60);
		btnLevel->addChild(labelName);

		//Add label riddle name
		Label* labelLevelNumber = Label::createWithTTF(configLabelRiddleName,
				riddle->riddle_hint, TextHAlignment::CENTER);
		labelLevelNumber->setPosition(
				Vec2(btnLevel->getContentSize().width / 2 + 10, 35));
		labelLevelNumber->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		labelLevelNumber->setColor(Color3B::BLACK);
		labelLevelNumber->setOpacity(isRiddleActive ? 255 : 60);
		btnLevel->addChild(labelLevelNumber);

		positionY -= itemMargin;
	}
}

void LevelScene::backButtonCallback(Ref* pSender,
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

void LevelScene::facebookButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		sdkbox::PluginFacebook::inviteFriends(FACEBOOK_INVITE_APP_URL,
		FACEBOOK_INVITE_IMAGE_URL);
	}
}
void LevelScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
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
