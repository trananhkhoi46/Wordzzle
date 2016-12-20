#include "HomeScene.h"
#include "PacketScene.h"
#include "SplashScene.h"
#include "LevelScene.h"

Scene* PacketScene::scene() {
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	PacketScene *layer = PacketScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PacketScene::init() {
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
	Button* btnFacebook = Button::create(s_packetscene_btn_facebook);
	btnFacebook->setPosition(Vec2(677, winSize.height - 71));
	btnFacebook->setTouchEnabled(true);
	btnFacebook->setPressedActionEnabled(true);
	btnFacebook->addTouchEventListener(
			CC_CALLBACK_2(PacketScene::facebookButtonCallback, this));
	this->addChild(btnFacebook);

	//Add btn back
	Button* btnBack = Button::create(s_packetscene_btn_back);
	btnBack->setPosition(Vec2(91, winSize.height - 71));
	btnBack->setTouchEnabled(true);
	btnBack->setPressedActionEnabled(true);
	btnBack->addTouchEventListener(
			CC_CALLBACK_2(PacketScene::backButtonCallback, this));
	this->addChild(btnBack);

	//Add title
	Button* title = Button::create(s_packetscene_title);
	title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	title->setPosition(Vec2(winSize.width / 2, winSize.height - 71));
	this->addChild(title);

	//Add scrollview
	initPacketButtons();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(PacketScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

void PacketScene::initPacketButtons() {
	//Scrollview configuration
	TTFConfig configLabelPacketName(s_font, 45 * s_font_ratio);
	TTFConfig configLabelPacketLevel(s_font_thin, 30 * s_font_ratio);
	int numberOfItems = vt_riddle_packets.size();
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
	CCLog("bambi PacketScene - inner height: %f, frame hight: %f",
			scrollview->getInnerContainerSize().height, scrollFrameSize.height);
	if (scrollview->getInnerContainerSize().height <= scrollFrameSize.height) {
		scrollview->setBounceEnabled(false);
	}
	this->addChild(scrollview);

	//Add sth to scroll view
	float positionX = scrollview->leftPosition;
	float positionY = scrollview->topPosition;
	for (int i = 0; i < numberOfItems; i++) {
		RiddlePacket* packet = vt_riddle_packets.at(i);
		bool isPacketActive = RiddleHelper::isPacketActive(
				packet->riddle_packet_id);

		//Add btn packet
		Button* btnPacket = Button::create(packet->riddle_packet_holder_image);
		btnPacket->setPosition(Vec2(scrollFrameSize.width * 0.5f, positionY));
		btnPacket->setTouchEnabled(true);
		btnPacket->setZoomScale(0);
		btnPacket->setPressedActionEnabled(true);
		btnPacket->addTouchEventListener(
				[this,isPacketActive,packet](Ref *pSender,
						Widget::TouchEventType type) {
					if (type == cocos2d::ui::Widget::TouchEventType::ENDED && isPacketActive)
					{
						if(isSound) {
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_click);
						}
						auto *newScene = LevelScene::scene(packet->riddle_packet_id);
						auto transition = TransitionFade::create(1.0, newScene);
						Director *pDirector = Director::getInstance();
						pDirector->replaceScene(transition);
					}});
		scrollview->addChild(btnPacket);

		//Add holder image
		if (isPacketActive) {
			Sprite* holderImage = Sprite::create(s_packetscene_active_holder);
			holderImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			holderImage->setPosition(
					Vec2(btnPacket->getContentSize().width / 2,
							btnPacket->getContentSize().height / 2));
			btnPacket->addChild(holderImage);
		}

		//Add icon
		Sprite* icon = Sprite::create(packet->riddle_packet_icon_image);
		icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		icon->setPosition(Vec2(80, btnPacket->getContentSize().height / 2));
		icon->setOpacity(isPacketActive ? 255 : 100);
		btnPacket->addChild(icon);

		//Add label packet name
		Label* labelName = Label::createWithTTF(configLabelPacketName,
				packet->riddle_packet_name, TextHAlignment::CENTER);
		labelName->setPosition(
				Vec2(btnPacket->getContentSize().width / 2 + 10, 75));
		labelName->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		labelName->setColor(Color3B::BLACK);
		labelName->setOpacity(isPacketActive ? 255 : 100);
		btnPacket->addChild(labelName);

		//Add label level number
		Label* labelLevelNumber = Label::createWithTTF(configLabelPacketLevel,
				String::createWithFormat("%d Levels",
						RiddleHelper::getLevelNumberInThePacket(
								packet->riddle_packet_id))->getCString(),
				TextHAlignment::CENTER);
		labelLevelNumber->setPosition(
				Vec2(btnPacket->getContentSize().width / 2 + 10, 35));
		labelLevelNumber->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		labelLevelNumber->setColor(Color3B::BLACK);
		labelLevelNumber->setOpacity(isPacketActive ? 255 : 100);
		btnPacket->addChild(labelLevelNumber);

		positionY -= itemMargin;
	}
}

void PacketScene::backButtonCallback(Ref* pSender,
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

void PacketScene::facebookButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		sdkbox::PluginFacebook::inviteFriends(FACEBOOK_INVITE_APP_URL,
		FACEBOOK_INVITE_IMAGE_URL);
	}
}
void PacketScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
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
