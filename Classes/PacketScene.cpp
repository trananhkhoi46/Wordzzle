#include "PacketScene.h"
#include "SplashScene.h"
#include "LevelScene.h"

bool clearedPackAnimationEnabled;
Scene* PacketScene::scene() {
	return scene(false);
}
Scene* PacketScene::scene(bool clearedPackAnimationEnabledPassed) {
	clearedPackAnimationEnabled = clearedPackAnimationEnabledPassed;
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

	//Add ads banner
	addBottomBanner();
	showAdsBanner();

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
	int activePacket = UserDefault::getInstance()->getIntegerForKey(
	ACTIVE_PACKET, ACTIVE_PACKET_DEFAULT_VALUE);
	float positionX = scrollview->leftPosition;
	float positionY = scrollview->topPosition;
	for (int i = 0; i < numberOfItems; i++) {
		RiddlePacket* packet = vt_riddle_packets.at(i);
		bool isPacketActive = RiddleHelper::isPacketActive(
				packet->riddle_packet_id)
				&& RiddleHelper::getLevelNumberInThePacket(
						packet->riddle_packet_id) > 0;

		//Add btn packet

		Button* btnPacket = Button::create(
				s_levelscene_level_holders[i
						% (sizeof s_levelscene_level_holders
								/ sizeof s_levelscene_level_holders[0])]);
		btnPacket->setPosition(Vec2(scrollFrameSize.width * 0.5f, positionY));
		btnPacket->setTouchEnabled(true);
		btnPacket->setZoomScale(0);
		btnPacket->setPressedActionEnabled(false);
		btnPacket->addTouchEventListener(
				[this,isPacketActive,packet,btnPacket](Ref *pSender,
						Widget::TouchEventType type) {
					if (type == cocos2d::ui::Widget::TouchEventType::ENDED && isPacketActive)
					{
						btnPacket->setScale(1);
						if(isSound) {
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_click);
						}
						auto *newScene = LevelScene::scene(packet->riddle_packet_id);
						auto transition = TransitionFade::create(1.0, newScene);
						Director *pDirector = Director::getInstance();
						pDirector->replaceScene(transition);
					} else if (type == cocos2d::ui::Widget::TouchEventType::BEGAN && isPacketActive)
					{
						btnPacket->setScale(1.05f);
					} else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED && isPacketActive) {
						btnPacket->setScale(1);
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

		if (clearedPackAnimationEnabled
				&& activePacket == packet->riddle_packet_id) {
			CCLog(
					"bambi PacketScene -> initPacketButtons - activePacket: %d, riddle_packet_id: %d",
					activePacket, packet->riddle_packet_id);
			if (RiddleHelper::getLevelNumberInThePacket(
					packet->riddle_packet_id) > 0) {
				btnPackUnlocked = btnPacket;
			}
		}

		positionY -= itemMargin;
	}

	if (clearedPackAnimationEnabled && btnPackUnlocked != nullptr) {
		btnPackUnlocked->setScale(0);
		auto func =
				CallFunc::create(
						[=]() {
							int activePacket = UserDefault::getInstance()->getIntegerForKey(
									ACTIVE_PACKET, ACTIVE_PACKET_DEFAULT_VALUE) - 1;
							scrollview->scrollToPercentVertical(activePacket * 100.0f / vt_riddle_packets.size() , 0.5f, true);
						});
		auto func2 =
				CallFunc::create([=]() {
					//Appear animation
						btnPackUnlocked->runAction(Sequence::create(ScaleTo::create(0.3, 1.1),ScaleTo::create(0.2, 1),nullptr));
					});
		auto func3 = CallFunc::create([=]() {
			showNotification(NOTIFICATION_UNLOCK_NEW_PACK);
		});
		this->runAction(
				Sequence::create(DelayTime::create(0.5f), func,
						DelayTime::create(0.3), func2, DelayTime::create(1),
						func3, nullptr));
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
		if (PluginFacebook::isLoggedIn()) {
			PluginFacebook::inviteFriends(FACEBOOK_INVITE_APP_URL,
			FACEBOOK_INVITE_IMAGE_URL);
		} else {
			PluginFacebook::login();
		}
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
