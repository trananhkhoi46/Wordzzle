#include "GameWinScene.h"
#include "SplashScene.h"
#include "PlayScene.h"

Riddle* solvedRiddle;
Scene* GameWinScene::scene(Riddle* passedRiddle) {
	solvedRiddle = passedRiddle;
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	GameWinScene *layer = GameWinScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameWinScene::init() {
	bool result = BaseScene::init();

	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
		return false;
	}

	//Show ads if passed 5 rounds
	int continuallyWinNumber = UserDefault::getInstance()->getIntegerForKey(
	KEY_WIN_CONTINUALLY_NUMBER_TO_SHOW_ADS, 1);
	if (continuallyWinNumber >= SHOW_FULLSCREEN_ADS_AFTER_WINNING_TIMES) {
		showFullscreenAds();
		UserDefault::getInstance()->setIntegerForKey(
		KEY_WIN_CONTINUALLY_NUMBER_TO_SHOW_ADS, 1);
	} else {
		UserDefault::getInstance()->setIntegerForKey(
		KEY_WIN_CONTINUALLY_NUMBER_TO_SHOW_ADS, continuallyWinNumber + 1);
	}

	//Give user 1 hint if passed 10 rounds
	bool isGivingUser1Hint = false;
	continuallyWinNumber = UserDefault::getInstance()->getIntegerForKey(
	KEY_WIN_CONTINUALLY_NUMBER_TO_GIVE_HINT, 1);
	if (continuallyWinNumber >= GIVE_USER_A_HINT_AFTER_WINNING_TIMES) {
		RiddleHelper::receiveHints(1);
		isGivingUser1Hint = true;
		UserDefault::getInstance()->setIntegerForKey(
		KEY_WIN_CONTINUALLY_NUMBER_TO_GIVE_HINT,
				continuallyWinNumber - GIVE_USER_A_HINT_AFTER_WINNING_TIMES);
	} else {
		UserDefault::getInstance()->setIntegerForKey(
		KEY_WIN_CONTINUALLY_NUMBER_TO_GIVE_HINT, continuallyWinNumber + 1);
	}

	//Add background
	Sprite* background = Sprite::create(s_background);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(background);

	RiddlePacket* packet = RiddleHelper::getPacketById(
			solvedRiddle->riddle_packet_id);

	//Add btn packet
	Button* btnPacket = Button::create(
			s_levelscene_level_holders[CppUtils::randomBetween(0,
					(sizeof s_levelscene_level_holders
							/ sizeof s_levelscene_level_holders[0]) - 1)]);
	btnPacket->setPosition(Vec2(winSize.width * 0.5f, 260));
	btnPacket->setTouchEnabled(true);
	btnPacket->setZoomScale(0);
	btnPacket->setPressedActionEnabled(false);
	this->addChild(btnPacket);

	//Add holder image
	Sprite* holderImage = Sprite::create(s_packetscene_active_holder);
	holderImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	holderImage->setPosition(
			Vec2(btnPacket->getContentSize().width / 2,
					btnPacket->getContentSize().height / 2));
	btnPacket->addChild(holderImage);

	//Add icon
	Sprite* icon = Sprite::create(packet->riddle_packet_icon_image);
	icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	icon->setPosition(Vec2(80, btnPacket->getContentSize().height / 2));
	btnPacket->addChild(icon);

	//Add label packet name
	TTFConfig configLabelPacketName(s_font, 45 * s_font_ratio);
	Label* labelName = Label::createWithTTF(configLabelPacketName,
			packet->riddle_packet_name, TextHAlignment::CENTER);
	labelName->setPosition(
			Vec2(btnPacket->getContentSize().width / 2 + 10,
					btnPacket->getContentSize().height / 2));
	labelName->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelName->setColor(Color3B::BLACK);
	btnPacket->addChild(labelName);

	//Add sprite level holder
	Sprite* levelHolder = Sprite::create(s_gamewinscene_spirte_level_holder);
	levelHolder->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	levelHolder->setPosition(winSize.width / 2, 915);
	this->addChild(levelHolder);
	//Add label riddle level
	TTFConfig configLabelRiddleLevel(s_font_bold, 300 * s_font_ratio);
	Label* labelLevelPassed;
	if (UserDefault::getInstance()->getBoolForKey(
	KEY_IS_DAILY_PUZZLE_MODE, false)) {
		labelLevelPassed = Label::createWithTTF(configLabelRiddleLevel, "DP",
				TextHAlignment::CENTER);
	} else {
		labelLevelPassed =
				Label::createWithTTF(configLabelRiddleLevel,
						String::createWithFormat("%d",
								solvedRiddle->riddle_level)->getCString(),
						TextHAlignment::CENTER);
	}
	labelLevelPassed->setPosition(levelHolder->getPosition());
	labelLevelPassed->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelLevelPassed->setColor(Color3B(124, 189, 35));
	labelLevelPassed->setScale(0);
	this->addChild(labelLevelPassed);
	labelLevelPassed->runAction(
			Sequence::create(DelayTime::create(0.8), ScaleTo::create(0.3, 1),
					nullptr));

	//Add sprite level solved
	Sprite* levelSolved = Sprite::create(s_gamewinscene_spirte_excellent);
	levelSolved->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	levelSolved->setPosition(winSize.width / 2, 485);
	this->addChild(levelSolved);

	auto func3 =
			CallFunc::create(
					[this,levelSolved,levelHolder,isGivingUser1Hint]() {

						ParticleSystemQuad* particleSystem = ParticleSystemQuad::create(
								s_gamewinscene_particle);
						particleSystem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
						particleSystem->setPosition(Vec2(winSize.width / 2, levelHolder->getPositionY()));
						particleSystem->setScale(2);
						this->addChild(particleSystem);

						auto move = MoveBy::create(0.4f, Vec2(0, 10));
						auto move2 = move->reverse();
						auto seq = Sequence::create(move, move2, nullptr);
						auto repeat = RepeatForever::create(seq);
						levelSolved->runAction(repeat);

						auto funcaaa =
						CallFunc::create(
								[=]() {
									if(isGivingUser1Hint) {
										showNotification(NOTIFICATION_GOT_1_FREE_HINT);
									}
								});
						this->runAction(Sequence::create(DelayTime::create(0.5), funcaaa, nullptr));

					});
	this->runAction(Sequence::create(DelayTime::create(0.8), func3, nullptr));

	auto func =
			CallFunc::create([=]() {
				if(UserDefault::getInstance()->getBoolForKey(
								KEY_IS_DAILY_PUZZLE_MODE, false)) {
					//Save winning date of daily puzzle
					time_t rawtime;
					struct tm * timeinfo;
					time (&rawtime);
					timeinfo = localtime (&rawtime);

					CCLog("bambi year->%d",timeinfo->tm_year+1900);
					CCLog("bambi month->%d",timeinfo->tm_mon+1);
					CCLog("bambi date->%d",timeinfo->tm_mday);
					UserDefault::getInstance()->setStringForKey(KEY_DAILY_PUZZLE_WINNING_DATE,
							String::createWithFormat("%d-%d-%d", timeinfo->tm_year+1900,
									timeinfo->tm_mon+1, timeinfo->tm_mday)->getCString());
					CCLog("bambi GameWinScene -> init -> KEY_DAILY_PUZZLE_WINNING_DATE: %s", UserDefault::getInstance()->getStringForKey(KEY_DAILY_PUZZLE_WINNING_DATE,"").c_str());

					UserDefault::getInstance()->setIntegerForKey(
							KEY_DAILY_PUZZLE_RIDDLE_ID, vt_riddles.at(CppUtils::randomBetween(0, vt_riddles.size() - 1))->riddle_id);

					auto *newScene = SplashScene::scene();
					auto transition = TransitionSlideInB::create(0.5f, newScene);
					Director *pDirector = Director::getInstance();
					pDirector->replaceScene(transition);
				} else {
					Riddle* nextRiddle = RiddleHelper::getNextLevelRiddleAndUnlockIfNeeded(solvedRiddle);
					if(nextRiddle != nullptr) {
						auto *newScene = PlayScene::scene(nextRiddle);
						auto transition = TransitionSlideInB::create(0.5f, newScene);
						Director *pDirector = Director::getInstance();
						pDirector->replaceScene(transition);
					} else {
						auto func2 =
						CallFunc::create(
								[=]() {
									auto *newScene = SplashScene::scene();
									auto transition = TransitionSlideInB::create(0.5f, newScene);
									Director *pDirector = Director::getInstance();
									pDirector->replaceScene(transition);
								});
						this->runAction(Sequence::create(DelayTime::create(3), func2, nullptr));
						showNotification("You have won all level!");
					}
				}
			});
	this->runAction(
			Sequence::create(DelayTime::create(isGivingUser1Hint ? 5.5f : 3),
					func, nullptr));

	return result;
}
