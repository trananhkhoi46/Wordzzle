#include "PlayScene.h"
#include "LevelScene.h"
#include "ShopScene.h"

Riddle* riddle;
Scene* PlayScene::scene(Riddle* riddlePassed) {
	riddle = riddlePassed;

	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	PlayScene *layer = PlayScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init() {
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

	//Add hint holder
	Sprite* hintHolder = Sprite::create(s_playscene_hint_holder);
	hintHolder->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	hintHolder->setPosition(winSize.width / 2, winSize.height - 71);
	this->addChild(hintHolder);

	//And hint label
	TTFConfig configLabelHint(s_font_bold, 35 * s_font_ratio);
	Label* labelHintOfTheRiddle = Label::createWithTTF(configLabelHint,
			riddle->riddle_hint, TextHAlignment::CENTER);
	labelHintOfTheRiddle->setPosition(
			Vec2(hintHolder->getContentSize().width / 2,
					hintHolder->getContentSize().height / 2));
	labelHintOfTheRiddle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelHintOfTheRiddle->setColor(Color3B::BLACK);
	hintHolder->addChild(labelHintOfTheRiddle);

	//Add btn back
	Button* btnBack = Button::create(s_levelscene_btn_back);
	btnBack->setPosition(Vec2(91, winSize.height - 71));
	btnBack->setTouchEnabled(true);
	btnBack->setPressedActionEnabled(true);
	btnBack->addTouchEventListener(
			CC_CALLBACK_2(PlayScene::backButtonCallback, this));
	this->addChild(btnBack);

	//Add btn shop
	Button* btnShop = Button::create(s_playscene_btn_shop);
	btnShop->setPosition(Vec2(110, 230));
	btnShop->setTouchEnabled(true);
	btnShop->setPressedActionEnabled(true);
	btnShop->addTouchEventListener(
			CC_CALLBACK_2(PlayScene::shopButtonCallback, this));
	this->addChild(btnShop);

	//Add btn restart
	Button* btnRestart = Button::create(s_playscene_btn_restart);
	btnRestart->setPosition(Vec2(winSize.width - 110, 230));
	btnRestart->setTouchEnabled(true);
	btnRestart->setPressedActionEnabled(true);
	btnRestart->addTouchEventListener(
			CC_CALLBACK_2(PlayScene::restartButtonCallback, this));
	this->addChild(btnRestart);

	//Add btn hint
	btnHint = Button::create(s_playscene_hint_holder);
	btnHint->setPosition(Vec2(winSize.width / 2, 230));
	btnHint->setTouchEnabled(true);
	btnHint->setPressedActionEnabled(true);
	btnHint->addTouchEventListener(
			CC_CALLBACK_2(PlayScene::getMoreHintButtonCallback, this));
	this->addChild(btnHint);
	TTFConfig configLabelHintButton(s_font_bold, 30 * s_font_ratio);
	labelHint = Label::createWithTTF(configLabelHintButton, "",
			TextHAlignment::CENTER);
	labelHint->setPosition(
			Vec2(btnHint->getContentSize().width / 2 - 23,
					btnHint->getContentSize().height / 2)); //Don't know why it will be deflected to the right? So we need to -23 posX
	labelHint->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelHint->setColor(Color3B::WHITE);
	btnHint->addChild(labelHint);
	updateUIGetMoreHintButton();

	//Add answer sprites
	addRiddleAnswerMatrix();
	addRiddleAnswer();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

void PlayScene::addRiddleAnswerMatrix() {
	TTFConfig configLabel(s_font_bold, 60 * s_font_ratio);
	int index = 0;
	float spriteWidth = 160; //size = 152, margin = 8
	float maxSizeX = riddle->riddle_answer_matrix.size();
	float maxSizeY = riddle->riddle_answer_matrix.at(0).size();
	for (int i = 0; i < maxSizeX; i++) {
		if (maxSizeY < riddle->riddle_answer_matrix.at(i).size()) {
			maxSizeY = riddle->riddle_answer_matrix.at(i).size();
		}
	}
	float totalWidth = maxSizeX * spriteWidth;
	float totalHeight = maxSizeY * spriteWidth;
	float posY = 855 + totalHeight / 2 - spriteWidth / 2;
	for (int i = 0; i < riddle->riddle_answer_matrix.size(); i++) {
		float posX = winSize.width / 2 - totalWidth / 2 + spriteWidth / 2;
		for (int j = 0; j < riddle->riddle_answer_matrix.at(i).size(); j++) {
			if (riddle->riddle_answer_matrix.at(i).at(j) != "_") {
				Sprite* spriteAnswer =
						Sprite::create(
								s_playscene_letter_holders[index
										% (sizeof s_playscene_letter_holders
												/ sizeof s_playscene_letter_holders[0])]);
				spriteAnswer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				spriteAnswer->setPosition(posX, posY);
				this->addChild(spriteAnswer);

				Label* labelAnswer = Label::createWithTTF(configLabel,
						riddle->riddle_answer_matrix.at(i).at(j),
						TextHAlignment::CENTER);
				labelAnswer->setPosition(
						Vec2(spriteAnswer->getContentSize().width / 2,
								spriteAnswer->getContentSize().height / 2));
				labelAnswer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				labelAnswer->setColor(Color3B::WHITE);
				spriteAnswer->addChild(labelAnswer);
			}
			index++;
			posX += spriteWidth;
		}
		posY -= spriteWidth;
	}
}
void PlayScene::addRiddleAnswer() {
	vtSpriteAnswer.clear();
	float spriteWidth = 70; //size = 60, margin = 10
	float totalSize = riddle->riddle_answer.length();
	float totalWidth = totalSize * spriteWidth;
	float posX = winSize.width / 2 - totalWidth / 2 + spriteWidth / 2;
	float posY = 465;
	for (int i = 0; i < totalSize; i++) {
		Sprite* spriteAnswer = Sprite::create(
				s_playscene_answer_holders[i
						% (sizeof s_playscene_answer_holders
								/ sizeof s_playscene_answer_holders[0])]);
		spriteAnswer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		spriteAnswer->setPosition(posX, posY);
		this->addChild(spriteAnswer);
		posX += spriteWidth;

		vtSpriteAnswer.push_back(spriteAnswer);
	}
}
void PlayScene::backButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = LevelScene::scene(riddle->riddle_packet_id);
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}

void PlayScene::restartButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = PlayScene::scene(riddle);
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}

void PlayScene::updateUIGetMoreHintButton() {
	int currentHint = UserDefault::getInstance()->getIntegerForKey(
	HINT_NUMBER, HINT_NUMBER_DEFAULT_VALUE);
	if (currentHint == 0) {
		labelHint->setVisible(false);
		btnHint->loadTextureNormal(s_playscene_btn_getmorehint,
				TextureResType::LOCAL);
	} else {
		labelHint->setString(
				String::createWithFormat("Use Hint: %d", currentHint)->getCString());
		labelHint->setVisible(true);
		btnHint->loadTextureNormal(s_playscene_btn_hint, TextureResType::LOCAL);
	}
}

void PlayScene::giveUserAHint() {
	//Consume a hint
	RiddleHelper::consumeAHint();

	//Give a hint to this riddle
	CCLog("bambi PlayScene -> giveUserAHint - currentAnswer 1: %s",
			currentAnswer.c_str());
	if (currentAnswer.length() < riddle->riddle_answer.length()) {
		currentAnswer += riddle->riddle_answer[currentAnswer.length()];
	}
	CCLog("bambi PlayScene -> giveUserAHint - currentAnswer 2: %s",
			currentAnswer.c_str());

	//Update UI
	TTFConfig configLabel(s_font_bold, 35 * s_font_ratio);
	int index = 0;
	for (Sprite* sprite : vtSpriteAnswer) {
		if (index >= currentAnswer.length()) {
			return;
		}
		string newCharString = currentAnswer.substr(index, 1);
		CCLog(
				"bambi PlayScene -> giveUserAHint - vtSpriteAnswerSize: %d, string: %s, index: %d",
				vtSpriteAnswer.size(), newCharString.c_str(), index);

		sprite->removeAllChildren();
		Label* label = Label::createWithTTF(configLabel, newCharString,
				TextHAlignment::CENTER);
		label->setPosition(
				Vec2(sprite->getContentSize().width / 2,
						sprite->getContentSize().height / 2));
		label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		label->setColor(Color3B::BLACK);
		sprite->addChild(label);
		index++;
	}
}

void PlayScene::shopButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = ShopScene::scene(riddle);
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}

void PlayScene::getMoreHintButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}
		int currentHint = UserDefault::getInstance()->getIntegerForKey(
		HINT_NUMBER, HINT_NUMBER_DEFAULT_VALUE);
		if (currentHint == 0) {
			auto *newScene = ShopScene::scene(riddle);
			auto transition = TransitionFade::create(1.0, newScene);
			Director *pDirector = Director::getInstance();
			pDirector->replaceScene(transition);
		} else {
			giveUserAHint();
			updateUIGetMoreHintButton();
		}
	}
}

void PlayScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		auto *newScene = LevelScene::scene(riddle->riddle_packet_id);
		auto transition = TransitionFade::create(1.0, newScene);
		Director *pDirector = Director::getInstance();
		pDirector->replaceScene(transition);
	}
}
