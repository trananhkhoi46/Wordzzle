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
			Vec2(btnPacket->getContentSize().width / 2 + 10, btnPacket->getContentSize().height / 2));
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
	Label* labelLevelPassed =
			Label::createWithTTF(configLabelRiddleLevel,
					String::createWithFormat("%d", solvedRiddle->riddle_level)->getCString(),
					TextHAlignment::CENTER);
	labelLevelPassed->setPosition(levelHolder->getPosition());
	labelLevelPassed->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelLevelPassed->setColor(Color3B(124, 189, 35));
	this->addChild(labelLevelPassed);

	//Add sprite level solved
	Sprite* levelSolved = Sprite::create(s_gamewinscene_spirte_excellent);
	levelSolved->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	levelSolved->setPosition(winSize.width / 2, 485);
	this->addChild(levelSolved);

	auto func3 =
			CallFunc::create(
					[this,levelSolved,levelHolder]() {

						ParticleSystemQuad* particleSystem = ParticleSystemQuad::create(
								s_gamewinscene_particle);
						particleSystem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
						particleSystem->setPosition(Vec2(winSize.width / 2, levelHolder->getPositionY() - levelHolder->getContentSize().height /2 ));
						this->addChild(particleSystem);

						auto move = MoveBy::create(0.4f, Vec2(0, 10));
						auto move2 = move->reverse();
						auto seq = Sequence::create(move, move2, nullptr);
						auto repeat = RepeatForever::create(seq);
						levelSolved->runAction(repeat);

					});
	this->runAction(Sequence::create(DelayTime::create(0.8), func3, nullptr));

	auto func =
			CallFunc::create(
					[=]() {
						Riddle* nextRiddle = RiddleHelper::getNextLevelRiddleAndUnlockIfNeeded(solvedRiddle);
						if(nextRiddle != nullptr) {
							auto *newScene = PlayScene::scene(nextRiddle);
							auto transition = TransitionSlideInR::create(0.5f, newScene);
							Director *pDirector = Director::getInstance();
							pDirector->replaceScene(transition);
						} else {
							auto func2 =
							CallFunc::create(
									[=]() {
										auto *newScene = SplashScene::scene();
										auto transition = TransitionSlideInR::create(0.5f, newScene);
										Director *pDirector = Director::getInstance();
										pDirector->replaceScene(transition);
									});
							this->runAction(Sequence::create(DelayTime::create(3), func2, nullptr));
							showNotification("You have won all level!");
						}
					});
	this->runAction(Sequence::create(DelayTime::create(4), func, nullptr));
	return result;
}