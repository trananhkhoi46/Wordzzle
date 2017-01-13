#include "PlayScene.h"
#include "LevelScene.h"
#include "ShopScene.h"
#include "GameWinScene.h"
#include "SplashScene.h"

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

	UserDefault::getInstance()->setIntegerForKey(
			String::createWithFormat("%s,%d", KEY_LAST_PLAYED_LEVEL,
					riddle->riddle_packet_id)->getCString(), riddle->riddle_level) ;

	//Init default value
	isDailyPuzzle = UserDefault::getInstance()->getBoolForKey(
	KEY_IS_DAILY_PUZZLE_MODE, false);
	TTFConfig config(s_font, 120 * s_font_ratio);
	isTouchedOnAnswerMatrix = false;
	currentAnswer = "";
	touchingAnswer = "";
	vtSpriteAnswer.clear();
	vtSpriteAnswer_Checking.clear();
	vtSpriteAnswerMatrix.clear();
	vtSpriteAnswerMatrix_Touching.clear();
	vtPoints.clear();
	mostLastestTouchedSpriteAnswerMatrix = nullptr;

	//Add background
	Sprite* background = Sprite::create(s_background);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(background);

	//Add hint holder
	hintHolder = Sprite::create(s_playscene_hint_holder);
	hintHolder->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	hintHolder->setPosition(winSize.width / 2, winSize.height - 71);
	this->addChild(hintHolder);

	//And hint label
	TTFConfig configLabelHint(s_font_bold, 35 * s_font_ratio);
	labelHintOfTheRiddle = Label::createWithTTF(configLabelHint,
			riddle->riddle_hint, TextHAlignment::CENTER);
	labelHintOfTheRiddle->setPosition(hintHolder->getPosition());
	labelHintOfTheRiddle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelHintOfTheRiddle->setColor(Color3B::BLACK);
	this->addChild(labelHintOfTheRiddle);

	hintHolderLeft = Sprite::create(s_playscene_hint_holder_left);
	hintHolderLeft->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(hintHolderLeft);

	hintHolderRight = Sprite::create(s_playscene_hint_holder_right);
	hintHolderRight->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(hintHolderRight);
	updateNinePathHintHolder();

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
	TTFConfig configLabelHintButton(s_font_bold, 28 * s_font_ratio);
	labelHint = Label::createWithTTF(configLabelHintButton, "",
			TextHAlignment::CENTER);
	labelHint->setPosition(btnHint->getPosition());
	labelHint->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelHint->setColor(Color3B::WHITE);
	this->addChild(labelHint);
	updateUIGetMoreHintButton();

	//Add answer sprites
	addRiddleAnswer();
	addRiddleAnswerMatrix();

	//Restore used hints
	string usedHintString =
			UserDefault::getInstance()->getStringForKey(
					String::createWithFormat("%s_%d", USED_HINT,
							riddle->riddle_id)->getCString(), "");
	UserDefault::getInstance()->setStringForKey(
			String::createWithFormat("%s_%d", USED_HINT, riddle->riddle_id)->getCString(),
			"");
	vector < string > vtUsedHint = CppUtils::splitStringByDelim(usedHintString,
			',');
//	CCLog("bambi PlayScene -> init - usedHintString: %s",
//			usedHintString.c_str());
	if (usedHintString != "") {
		for (string record : vtUsedHint) {
			if (record != "") {
				//TODO cho user dua theo index cua used hint
				if (UserDefault::getInstance()->getIntegerForKey(HINT_NUMBER,
				HINT_NUMBER_DEFAULT_VALUE) != -100) {
					RiddleHelper::receiveHints(1);
				}
				giveUserAHint();
			}
		}
	}

	//Restore chosen answer
	string chosenAnswerSpriteTagString =
			UserDefault::getInstance()->getStringForKey(
					String::createWithFormat("%s_%d", CHOSEN_TAG,
							riddle->riddle_id)->getCString(), "");
	UserDefault::getInstance()->setStringForKey(
			String::createWithFormat("%s_%d", CHOSEN_TAG, riddle->riddle_id)->getCString(),
			"");
	vector < string > vtAnswerSpriteTag = CppUtils::splitStringByDelim(
			chosenAnswerSpriteTagString, ',');
	if (chosenAnswerSpriteTagString != "") {
		for (string record : vtAnswerSpriteTag) {
			if (record != "") {
				for (Sprite* sprite : vtSpriteAnswerMatrix) {
					if (sprite->getTag() == CppUtils::stringToDouble(record)) {
						vtSpriteAnswerMatrix_Touching.push_back(sprite);
					}
				}

				string answer = getAnswerStringFromTag(
						CppUtils::stringToDouble(record));
				touchingAnswer += answer;
			}
		}
	}
//	CCLog("bambi PlayScene -> init - touchingAnswer after restoring: %s",
//			touchingAnswer.c_str());
	bool isIsSoundWasTrue = isSound;
	isSound = false;
	onTouchEnded(nullptr, nullptr);
	if (isIsSoundWasTrue) {
		isSound = true;
	}

	//Add ads banner
	addBottomBanner();
	showAdsBanner();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	//Handling touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return result;
}

void PlayScene::updateNinePathHintHolder() {
	if (labelHintOfTheRiddle != nullptr
			&& labelHintOfTheRiddle->getString().length() > 18) {
		TTFConfig configLabelHint(s_font_bold,
				35 * 18 / labelHintOfTheRiddle->getString().length()
						* s_font_ratio);
		labelHintOfTheRiddle->setTTFConfig(configLabelHint);
	}

	float scaleX = labelHintOfTheRiddle->getContentSize().width / 10;
	hintHolder->setScaleX(scaleX);

	hintHolderLeft->setPosition(
			hintHolder->getPositionX()
					- hintHolder->getContentSize().width * scaleX / 2
					- hintHolderLeft->getContentSize().width / 2,
			hintHolder->getPositionY());

	hintHolderRight->setPosition(
			hintHolder->getPositionX()
					+ hintHolder->getContentSize().width * scaleX / 2
					+ hintHolderRight->getContentSize().width / 2,
			hintHolder->getPositionY());
}

string PlayScene::getAnswerStringFromTag(int tag) {
	try {
		return riddle->riddle_answer_matrix.at(tag / 1000).at(tag % 1000);
	} catch (...) {
		return "_";
	}
}
int PlayScene::getTagFromAnswerStringPosition(int i, int j) {
	return i * 1000 + j;
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
    
    
    
    scale = 1;
    float maxSizeAllMatrix = 600;
    scale = 1 / (totalWidth / maxSizeAllMatrix);
    if(scale > 1.5f){
        scale = 1.5f;
    }
    
    
    maxSizeX *= scale;
    maxSizeY *= scale;
    spriteWidth *= scale;
    totalWidth *= scale;
    totalHeight *= scale;
    
    
	float posY = 830 + totalHeight / 2 - spriteWidth / 2;
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
				spriteAnswer->setTag(getTagFromAnswerStringPosition(i, j));
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
                spriteAnswer->setScale(scale);

				vtSpriteAnswerMatrix.push_back(spriteAnswer);
			}
			index++;
			posX += spriteWidth;
		}
		posY -= spriteWidth;
	}
}
void PlayScene::addRiddleAnswer() {
	vtSpriteAnswer.clear();
	vector < string > vtRiddleAnswerSplited = CppUtils::splitStringByDelim(
			riddle->riddle_answer, ' ');
	float spriteWidth = 70; //size = 60, margin = 10
	float totalHeight = vtRiddleAnswerSplited.size() * spriteWidth;
	float posY = 390 + totalHeight / 2 - spriteWidth / 2;
	int index = 0;
	for (int j = 0; j < vtRiddleAnswerSplited.size(); j++) {
		float totalSize = vtRiddleAnswerSplited.at(j).length();
		float totalWidth = totalSize * spriteWidth;

		float posX = winSize.width / 2 - totalWidth / 2 + spriteWidth / 2;
		for (int i = 0; i < totalSize; i++) {
			Sprite* spriteAnswer = Sprite::create(
					s_playscene_answer_holders[i
							% (sizeof s_playscene_answer_holders
									/ sizeof s_playscene_answer_holders[0])]);
			spriteAnswer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			spriteAnswer->setPosition(posX, posY);
			spriteAnswer->setTag(index);
			this->addChild(spriteAnswer);
			posX += spriteWidth;

			index++;
			vtSpriteAnswer.push_back(spriteAnswer);
			vtSpriteAnswer_Checking.push_back(spriteAnswer);
		}
		index++;
		posY -= spriteWidth;
	}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//    vtSpriteAnswer.clear();
//    vector < string > vtRiddleAnswerSplited = CppUtils::splitStringByDelim(
//                                                                           riddle->riddle_answer, ' ');
//    float spriteWidth = 70; //size = 60, margin = 10
//    float totalHeight = vtRiddleAnswerSplited.size() * spriteWidth;
//    
//    float posY = 390 + totalHeight / 2 - spriteWidth / 2;
//    
//    
//    
//    int rowNumber = 1;
//    float maxWidth = 768;
//    
//    vector<int> wordNumberInARow;
//    int digits = 0;
//    for (int i = 0; i < vtRiddleAnswerSplited.size(); i++) {
//        digits += vtRiddleAnswerSplited.at(i).length();
//        
//        CCLog("bambi PlayScene -> addRiddleAnswer - digits: %d, i: %d, rowNumber: %d", digits, i, rowNumber);
//        
//        bool justPlusRowNumber = false;
//        if(digits * spriteWidth > maxWidth){
//            rowNumber++;
//            justPlusRowNumber = true;
//        }
//        
//        
//        if(wordNumberInARow.size() > rowNumber - 1)
//            wordNumberInARow.at(rowNumber-1) = digits;
//        else
//            wordNumberInARow.push_back(digits);
//        
//        if(justPlusRowNumber){
//            digits = 0;
//        }
//        
//        CCLog("bambi PlayScene -> addRiddleAnswer 2 - digits: %d, i: %d, rowNumber: %d", digits, i, rowNumber);
//    }
//    
//    
//    
//    
//    for(int k = 0 ; k < wordNumberInARow.size() ; k++){
//        CCLog("bambi PlayScene -> addRiddleAnswer - in loop - wordNumberInARow[%d]: %d,",k,wordNumberInARow.at(k));
//    }
//    
//    
//    CCLog("bambi PlayScene -> addRiddleAnswer - rowNumber: %d", rowNumber);
//    
//    
//    int index = 0;
//    int wordIndexFrom = 0;
//    int wordIndexTo = 0;
//    for (int j = 0; j < wordNumberInARow.size(); j++) {
//        float totalSize;
//        float totalWidth;
//        
//        while (totalWidth < maxWidth) {
//            totalSize += vtRiddleAnswerSplited.at(wordIndexTo).length();
//            totalWidth = totalSize * spriteWidth;
//            
//            (wordIndexTo)++;
//        }
//        
//        
//        float posX = winSize.width / 2 - totalWidth / 2 + spriteWidth / 2;
//        for (int i = wordIndexFrom; i <= wordIndexTo; i++) {
//            Sprite* spriteAnswer = Sprite::create(
//                                                  s_playscene_answer_holders[i
//                                                                             % (sizeof s_playscene_answer_holders
//                                                                                / sizeof s_playscene_answer_holders[0])]);
//            spriteAnswer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//            spriteAnswer->setPosition(posX, posY);
//            spriteAnswer->setTag(index);
//            this->addChild(spriteAnswer);
//            posX += spriteWidth;
//            
//            index++;
//            vtSpriteAnswer.push_back(spriteAnswer);
//            vtSpriteAnswer_Checking.push_back(spriteAnswer);
//        }
//        index++;
//        wordIndexFrom++;
//        wordIndexTo++;
//        posY -= spriteWidth;
//    }
}
void PlayScene::backButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		if (isDailyPuzzle) {
			auto *newScene = SplashScene::scene();
			auto transition = TransitionFade::create(1.0, newScene);
			Director *pDirector = Director::getInstance();
			pDirector->replaceScene(transition);
		} else {
			auto *newScene = LevelScene::scene(riddle->riddle_packet_id);
			auto transition = TransitionFade::create(1.0, newScene);
			Director *pDirector = Director::getInstance();
			pDirector->replaceScene(transition);
		}
	}
}

void PlayScene::restartButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		//Don't restore chosen sprite answer for this riddle anymore
		UserDefault::getInstance()->setStringForKey(
				String::createWithFormat("%s_%d", CHOSEN_TAG, riddle->riddle_id)->getCString(),
				"");

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
		if (currentHint != -100) {
			labelHint->setString(
					String::createWithFormat("Use Hint: %d", currentHint)->getCString());
		} else {
			labelHint->setString("Use Hint: Unlimited");
		}
		labelHint->setVisible(true);
		btnHint->loadTextureNormal(s_playscene_btn_hint, TextureResType::LOCAL);
	}
}

void PlayScene::giveUserAHint() {
	if (currentAnswer.length() >= riddle->riddle_answer.length()) {
		showNotification(NOTIFICATION_USED_HINT_ENOUGH);
		return;
	}

//Give a hint to this riddle
//	CCLog("bambi PlayScene -> giveUserAHint - currentAnswer 1: %s",
//			currentAnswer.c_str());

	int minIndex = vtAnsweredIndex.size();
	for (int i = 0; i < vtAnsweredIndex.size(); i++) {
		if (vtAnsweredIndex.at(i) < minIndex) {
			minIndex = vtAnsweredIndex.at(i);
		}
	}

	int loopNumber = 1;
	if (currentAnswer.length() >= minIndex + 1
			|| (minIndex == 0 && currentAnswer.length() == 0)) {
		loopNumber = minIndex + vtAnsweredIndex.size() + 1;
		vtAnsweredIndex.clear();
	}
	if (loopNumber > 1) {
		currentAnswer = "";
	}

	bool willConsumeAHint = true;
//	CCLog("bambi PlayScene -> giveUserAHint - loopNumber: %d", loopNumber);
	for (int i = 0; i < loopNumber; i++) {
		if (currentAnswer.length() < riddle->riddle_answer.length()) {
			if (riddle->riddle_answer[currentAnswer.length()] == ' ') {
				currentAnswer += " ";
			}
			currentAnswer += riddle->riddle_answer[currentAnswer.length()];

			//Add to used hint for restoring
			UserDefault::getInstance()->setStringForKey(
					String::createWithFormat("%s_%d", USED_HINT,
							riddle->riddle_id)->getCString(),
					UserDefault::getInstance()->getStringForKey(
							String::createWithFormat("%s_%d", USED_HINT,
									riddle->riddle_id)->getCString(), "") + ","
							+ CppUtils::doubleToString(currentAnswer.length()));
		} else {
			showNotification(NOTIFICATION_USED_HINT_ENOUGH);
			willConsumeAHint = false;
			break;
		}
//		CCLog("bambi PlayScene -> giveUserAHint - currentAnswer 2: %s",
//				currentAnswer.c_str());
		if (currentAnswer.length() > riddle->riddle_answer.length()) {
			showNotification(NOTIFICATION_USED_HINT_ENOUGH);
			willConsumeAHint = false;
			break;
		}
	}

	//Consume a hint
	if (willConsumeAHint) {
		RiddleHelper::consumeAHint();
	}

//Update UI
	TTFConfig configLabel(s_font_bold, 35 * s_font_ratio);
	int index = 0;
	for (Sprite* sprite : vtSpriteAnswer) {
		if (index >= currentAnswer.length()) {
			return;
		}
		string newCharString = currentAnswer.substr(index, 1);
		if (newCharString == " ") {
			index++;
			newCharString = currentAnswer.substr(index, 1);
		}
		CCLog(
				"bambi PlayScene -> giveUserAHint - vtSpriteAnswerSize: %d, string: %s, index: %d",
				vtSpriteAnswer.size(), newCharString.c_str(), index);

		sprite->removeAllChildren();
        std::transform(newCharString.begin(), newCharString.end(),
                       newCharString.begin(), ::toupper);
        
		Label* label = Label::createWithTTF(configLabel, newCharString,
				TextHAlignment::CENTER);
		label->setPosition(sprite->getPosition());
		label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        Color3B colorOfParticle;
        
//        switch (sprite->getTag() % 4) {
//            case 0:
//                colorOfParticle = Color3B(171,210,113);
//                break;
//                
//            case 1:
//                colorOfParticle = Color3B(246,136,4);
//                break;
//                
//            case 2:
//                colorOfParticle = Color3B(183,68,180);
//                break;
//                
//            case 3:
//                colorOfParticle = Color3B(27,187,180);
//                break;
//        }
        sprite->setTexture(s_playscene_letter_holders[(sizeof s_playscene_letter_holders
                                                       / sizeof s_playscene_letter_holders[0]) - 1- (sprite->getTag()
                                                      % (sizeof s_playscene_letter_holders
                                                         / sizeof s_playscene_letter_holders[0]))]);
        sprite->setScale(0.3947368421f);
        label->setColor(Color3B::WHITE);
		this->addChild(label);

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

bool PlayScene::onTouchBegan(Touch* touch, Event* event) {
	if (isNotificationShowing) {
		return true;
	}
	touchingAnswer = "";
	vtPoints.clear();
	vtSpriteAnswerMatrix_Touching.clear();
	isTouchedOnAnswerMatrix = false;
	mostLastestTouchedSpriteAnswerMatrix = nullptr;

	if (isNotificationShowing) {
		return true;
	}

	if (isTouchedOnAnswerMatrix && vtPoints.size() > 0) {
		int random = CppUtils::randomBetween(0, vtPoints.size() - 1);
		Sprite* point = Sprite::create(s_playscene_points[vtPoints.at(random)]);
		point->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		point->setScale(0.75f);
		point->setPosition(touch->getLocation());
		this->addChild(point);
		auto func = CallFunc::create([point]() {
			point->removeFromParentAndCleanup(true);
		});
		point->runAction(
				Sequence::create(DelayTime::create(0.5f), FadeOut::create(0.5f),
						func, nullptr));
	}

	for (Sprite* sprite : vtSpriteAnswerMatrix) {
		Rect rect = sprite->getBoundingBox();
		if (rect.containsPoint(touch->getLocation())
				&& sprite->getNumberOfRunningActions() == 0
				&& checkTheAnswerMatrixSpriteIsValid(sprite)) {
			string answer = getAnswerStringFromTag(sprite->getTag());
			touchingAnswer += answer;
			sprite->runAction(ScaleTo::create(0.1f, 0));

			vtSpriteAnswerMatrix_Touching.push_back(sprite);
			vtPoints.push_back(
					(((int) (sprite->getTag() / 1000))
							* riddle->riddle_answer_matrix.size()
							+ sprite->getTag() % 1000)
							% (sizeof s_playscene_points
									/ sizeof s_playscene_points[0]));
			labelHintOfTheRiddle->setString(touchingAnswer);
			updateNinePathHintHolder();
			mostLastestTouchedSpriteAnswerMatrix = sprite;
			isTouchedOnAnswerMatrix = true;
			break;
		}
	}
	return true;
}

void PlayScene::onTouchMoved(Touch* touch, Event* event) {
	if (isNotificationShowing) {
		return;
	}

	if (isTouchedOnAnswerMatrix && vtPoints.size() > 0) {
		int random = CppUtils::randomBetween(0, vtPoints.size() - 1);
		Sprite* point = Sprite::create(s_playscene_points[vtPoints.at(random)]);
		point->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		point->setScale(0.75f);
		point->setPosition(touch->getLocation());
		this->addChild(point);
		auto func = CallFunc::create([point]() {
			point->removeFromParentAndCleanup(true);
		});
		point->runAction(
				Sequence::create(DelayTime::create(0.5f), FadeOut::create(0.5f),
						func, nullptr));
	}

	for (Sprite* sprite : vtSpriteAnswerMatrix) {
		Rect rect = sprite->getBoundingBox();
		rect.setRect(rect.origin.x + rect.size.width / 4,
				rect.origin.y + rect.size.height / 4, rect.size.width / 2,
				rect.size.height / 2);
		if (rect.containsPoint(touch->getLocation())
				&& sprite->getNumberOfRunningActions() == 0
				&& checkTheAnswerMatrixSpriteIsValid(sprite)) {
			string answer = getAnswerStringFromTag(sprite->getTag());
			touchingAnswer += answer;
			sprite->runAction(ScaleTo::create(0.1f, 0));

			vtSpriteAnswerMatrix_Touching.push_back(sprite);
			vtPoints.push_back(
					(((int) (sprite->getTag() / 1000))
							* riddle->riddle_answer_matrix.size()
							+ sprite->getTag() % 1000)
							% (sizeof s_playscene_points
									/ sizeof s_playscene_points[0]));
			labelHintOfTheRiddle->setString(touchingAnswer);
			updateNinePathHintHolder();
			mostLastestTouchedSpriteAnswerMatrix = sprite;
			isTouchedOnAnswerMatrix = true;
			break;
		}
	}
}

bool PlayScene::checkTheAnswerMatrixSpriteIsValid(Sprite* sprite) {
	if (mostLastestTouchedSpriteAnswerMatrix != nullptr) {
		int coordXPreviousSprite =
				mostLastestTouchedSpriteAnswerMatrix->getTag() / 1000;
		int coordYPreviousSprite =
				mostLastestTouchedSpriteAnswerMatrix->getTag() % 1000;
		int coordXThisSprite = sprite->getTag() / 1000;
		int coordYThisSprite = sprite->getTag() % 1000;

		if (coordXThisSprite - coordXPreviousSprite > 1
				|| coordYThisSprite - coordYPreviousSprite > 1
				|| coordXPreviousSprite - coordXThisSprite > 1
				|| coordYPreviousSprite - coordYThisSprite > 1) {
			return false;
		}
	}
	return true;
}

bool PlayScene::checkGameWin() {
	return vtSpriteAnswer_Checking.size() == 0;
}

string PlayScene::checkWordMatch() {
	std::transform(touchingAnswer.begin(), touchingAnswer.end(),
			touchingAnswer.begin(), ::tolower);

	vector < string > splitedStringVt = CppUtils::splitStringByDelim(
			riddle->riddle_answer, ' ');
	for (string record : splitedStringVt) {
//		CCLog("bambi PlayScene -> wordMatch - record: %s, touchingAnswer: %s",
//				record.c_str(), touchingAnswer.c_str());
		if (touchingAnswer.find(record) != std::string::npos) {
			return record;
		}
	}
	return "";
}

bool PlayScene::checkHolderInWordIndex(int holderTag, int index) {
	/*
	 *  123
	 * 4567
	 *  89
	 *
	 * hỏi số 5 nằm ở dòng thứ mấy
	 *
	 * holderTag = 4 (tag = 4 khi value là 5), index = 2 -> cần return true
	 *
	 */

	int count = 0;
	vector < string > vtWordAnswer = CppUtils::splitStringByDelim(
			riddle->riddle_answer, ' ');
	int minLoopSize = index;
	if (minLoopSize > vtWordAnswer.size() - 1) {
		minLoopSize = vtWordAnswer.size() - 1;
	}
//	CCLog("bambi PlayScene -> checkHolderInWordIndex -> minLoopSize: %d",
//			minLoopSize);
	for (int i = 0; i <= minLoopSize; i++) {
		count += vtWordAnswer.at(i).length() + 1;

		/**
		 * i == 1
		 * -> count = 8 (7 con so + 1 dau cach)
		 * Neu holderTag = 4 < 8
		 * Va holder tag = 4 >= 3
		 * Va 2 == i=1 + 1
		 */

//		CCLog(
//				"bambi PlayScene -> checkHolderInWordIndex -> holderTag: %d, count: %d, count - vtWordAnswer.at(i).length() -i - 1: %d, index: %d, i: %d",
//				holderTag, count, count - vtWordAnswer.at(i).length() - i - 1,
//				index, i);
		if (holderTag < count
				&& holderTag >= count - i - vtWordAnswer.at(i).length() - 1
				&& index == i) {
			return true;
		}
	}
	return false;
}

void PlayScene::onTouchEnded(Touch* touch, Event* event) {
	string wordMatch = checkWordMatch();
	if (wordMatch != "" && touchingAnswer.length() == wordMatch.length()) {
		int wordMatchIndex = 0;
		float animationDuration = 0;
		vector < string > vtWordAnswer = CppUtils::splitStringByDelim(
				riddle->riddle_answer, ' ');
		for (int i = 0; i < vtWordAnswer.size(); i++) {
			CCLog(
					"bambi PlayScene -> onTouchEnded - vtWordAnswer.at(i): %s, wordMatch: %s",
					vtWordAnswer.at(i).c_str(), wordMatch.c_str());
			if (vtWordAnswer.at(i) == wordMatch) {
				wordMatchIndex = i;
				break;
			}
		}

		//Animation
		CCLog(
				"bambi PlayScene -> onTouchEnded -> wordMatch: %s - wordMatchIndex: %d",
				wordMatch.c_str(), wordMatchIndex);
		std::transform(touchingAnswer.begin(), touchingAnswer.end(),
				touchingAnswer.begin(), ::tolower);
		int index = 0;
		for (Sprite* sprite : vtSpriteAnswerMatrix_Touching) {
			string answer = getAnswerStringFromTag(sprite->getTag());
			std::transform(answer.begin(), answer.end(), answer.begin(),
					::tolower);

			CCLog(
					"bambi PlayScene -> onTouchEnded -> answer: %s, touchingAnswer: %s",
					answer.c_str(), touchingAnswer.c_str());
			for (Sprite* holder : vtSpriteAnswer_Checking) {

				CCLog(
						"bambi PlayScene -> checking word index - holderTag: %d, wordMatchIndex: %d, result: %s",
						holder->getTag(), wordMatchIndex,
						checkHolderInWordIndex(holder->getTag(),
								wordMatchIndex) ? "true" : "false");

				if (holder != nullptr
						&& riddle->riddle_answer[holder->getTag()] == answer[0]
						&& checkHolderInWordIndex(holder->getTag(),
								wordMatchIndex)) {
					animationDuration += 0.05f;
					vtAnsweredIndex.push_back(holder->getTag());
					auto func =
							CallFunc::create(
									[=]() {
										sprite->setZOrder(time(nullptr));
										sprite->stopAllActions();
										sprite->setScale(0.45);
										sprite->setPositionY(winSize.height * 0.7f);
										sprite->runAction(MoveTo::create(0.3, holder->getPosition()));
									});
					this->runAction(
							Sequence::create(DelayTime::create(index * 0.05f),
									func, nullptr));

					//Remove from vtSpriteAnswer_Checking
					vtSpriteAnswer_Checking.erase(
							std::remove(vtSpriteAnswer_Checking.begin(),
									vtSpriteAnswer_Checking.end(), holder),
							vtSpriteAnswer_Checking.end());

					vtSpriteAnswerMatrix.erase(
							std::remove(vtSpriteAnswerMatrix.begin(),
									vtSpriteAnswerMatrix.end(), sprite),
							vtSpriteAnswerMatrix.end());

					//Save to sharedpreferences for restoring
					string chosenAnswerSpriteTagString =
							UserDefault::getInstance()->getStringForKey(
									String::createWithFormat("%s_%d",
									CHOSEN_TAG, riddle->riddle_id)->getCString(),
									"");
					UserDefault::getInstance()->setStringForKey(
							String::createWithFormat("%s_%d", CHOSEN_TAG,
									riddle->riddle_id)->getCString(),
							chosenAnswerSpriteTagString + ","
									+ CppUtils::doubleToString(
											sprite->getTag()));
					CCLog(
							"bambi PlayScene -> onTouchedEnded - UserDefault - CHOSEN_TAG: %s",
							UserDefault::getInstance()->getStringForKey(
									String::createWithFormat("%s_%d",
									CHOSEN_TAG, riddle->riddle_id)->getCString(),
									"").c_str());
					break;
				}
			}
			index++;
		}

		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_correct_answer);
		}

		if (checkGameWin()) {
			if (isDailyPuzzle) {
				UserDefault::getInstance()->setIntegerForKey(
				KEY_WIN_CONTINUALLY_NUMBER_TO_GIVE_HINT,
						UserDefault::getInstance()->getIntegerForKey(
						KEY_WIN_CONTINUALLY_NUMBER_TO_GIVE_HINT,
								0) + GIVE_USER_A_HINT_AFTER_WINNING_TIMES);
			}

			UserDefault::getInstance()->setStringForKey(
					String::createWithFormat("%s_%d", CHOSEN_TAG,
							riddle->riddle_id)->getCString(), "");
			UserDefault::getInstance()->setStringForKey(
					String::createWithFormat("%s_%d", USED_HINT,
							riddle->riddle_id)->getCString(), "");
			auto func = CallFunc::create([=]() {
				auto *newScene = GameWinScene::scene(riddle);
				auto transition = TransitionSlideInR::create(0.35f, newScene);
				Director *pDirector = Director::getInstance();
				pDirector->replaceScene(transition);
			});
			this->runAction(
					Sequence::create(
							DelayTime::create(animationDuration + 0.5f), func,
							nullptr));

		}
	} else {
		if (isSound && vtSpriteAnswerMatrix_Touching.size() > 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_wrong_answer);
		}

		for (Sprite* sprite : vtSpriteAnswerMatrix) {
			sprite->runAction(ScaleTo::create(0.1f, 1 * scale));
		}
	}
	labelHintOfTheRiddle->setString(riddle->riddle_hint);
	updateNinePathHintHolder();
}

void PlayScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		if (isDailyPuzzle) {
			auto *newScene = SplashScene::scene();
			auto transition = TransitionFade::create(1.0, newScene);
			Director *pDirector = Director::getInstance();
			pDirector->replaceScene(transition);
		} else {
			auto *newScene = LevelScene::scene(riddle->riddle_packet_id);
			auto transition = TransitionFade::create(1.0, newScene);
			Director *pDirector = Director::getInstance();
			pDirector->replaceScene(transition);
		}
	}
}
