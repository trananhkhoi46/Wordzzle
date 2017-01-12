#include "TutorialScene.h"
#include "SettingScene.h"

int tutorialPage;
Scene* TutorialScene::scene() {
	return scene(1);
}
Scene* TutorialScene::scene(int tutorialPagePassed) {
	tutorialPage = tutorialPagePassed;

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

    touchable = true;
    
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

	//Add tutorial text
	tutorialText;
	if (tutorialPage == 1)
		tutorialText = Sprite::create(s_tutorialscene_tutorial);
	else if (tutorialPage == 2)
		tutorialText = Sprite::create(s_tutorialscene_tutorial2);
	else if (tutorialPage == 3)
		tutorialText = Sprite::create(s_tutorialscene_tutorial3);
	else if (tutorialPage == 4)
		tutorialText = Sprite::create(s_tutorialscene_tutorial4);
	tutorialText->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    if(tutorialPage == 4){
        tutorialText->setPosition(winSize.width / 2, winSize.height * 0.4 - 85);
    }else
        tutorialText->setPosition(winSize.width / 2, winSize.height * 0.4 - 15);
	this->addChild(tutorialText);

	//Add tutorial
	tutorial;
	int frameNumber;
	switch (tutorialPage) {
	case 1:
		frameNumber = 20;
		tutorial = Sprite::create(s_tutorialscene_tutorial);
		break;
	case 2:
		frameNumber = 40;
		tutorial = Sprite::create(s_tutorialscene_tutorial2);
		break;
	case 3:
		frameNumber = 56;
		tutorial = Sprite::create(s_tutorialscene_tutorial3);
		break;
	case 4:
		frameNumber = 37;
		tutorial = Sprite::create(s_tutorialscene_tutorial4);
		break;
	}
	tutorial->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	tutorial->setPosition(winSize.width / 2, winSize.height * 0.7 - 30);
	this->addChild(tutorial);
	Vector<SpriteFrame*> animFrames(frameNumber);
	char str[254] = { 0 };
	for (int i = 0; i < frameNumber; i++) {
		SpriteFrame* frame;
		if (tutorialPage == 1)
			frame =
					SpriteFrame::create(
							String::createWithFormat(s_tutorialscene_gif, i)->getCString(),
							Rect(0, 0, 768, 500));
		else if (tutorialPage == 2)
			frame =
					SpriteFrame::create(
							String::createWithFormat(s_tutorialscene_gif2, i)->getCString(),
							Rect(0, 0, 768, 500));
		else if (tutorialPage == 3)
			frame =
					SpriteFrame::create(
							String::createWithFormat(s_tutorialscene_gif3, i)->getCString(),
							Rect(0, 0, 768, 500));
		else if (tutorialPage == 4)
			frame =
					SpriteFrame::create(
							String::createWithFormat(s_tutorialscene_gif4, i)->getCString(),
							Rect(0, 0, 768, 768));

		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames,
			tutorialPage == 1 ? 0.1f : 0.06f);
	auto animate = Animate::create(animation);
	tutorial->runAction(RepeatForever::create(animate));

	//Add btn got it
	if (tutorialPage == 1)
		btnGotIt = Button::create(s_tutorialscene_btn_ok);
    else if (tutorialPage == 2)
		btnGotIt = Button::create(s_tutorialscene_btn_understand);
    else if (tutorialPage == 3)
        btnGotIt = Button::create(s_tutorialscene_btn_soundgood);
    else if (tutorialPage == 4)
        btnGotIt = Button::create(s_tutorialscene_btn_letsplay);

  	btnGotIt->setPosition(Vec2(board->getContentSize().width / 2, 100));
	btnGotIt->setTouchEnabled(true);
	btnGotIt->setPressedActionEnabled(true);
	btnGotIt->addTouchEventListener(
			CC_CALLBACK_2(TutorialScene::gotItButtonCallback, this));
	board->addChild(btnGotIt);

	//Add btn skip
	Button* btnSkip = Button::create(s_tutorialscene_btn_skip);
	btnSkip->setPosition(
			Vec2(winSize.width - btnSkip->getContentSize().width,
					title->getPositionY()));
	btnSkip->setTouchEnabled(true);
	btnSkip->setPressedActionEnabled(true);
	btnSkip->addTouchEventListener(
			CC_CALLBACK_2(TutorialScene::backButtonCallback, this));
	this->addChild(btnSkip);

	//Add ads banner
	addBottomBanner();
	showAdsBanner();

	//Keyboard handling
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(
			TutorialScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,
			this);

	return result;
}

void TutorialScene::gotItButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType) {
	if (eEventType == ui::Widget::TouchEventType::ENDED && touchable) {
		if (isSound) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					s_click);
		}

		if (tutorialPage < 4) {
            tutorialPage++;
            
            if (tutorialPage == 1)
                btnGotIt->loadTextureNormal(s_tutorialscene_btn_ok);
            else if (tutorialPage == 2)
                btnGotIt->loadTextureNormal(s_tutorialscene_btn_understand);
            else if (tutorialPage == 3)
                btnGotIt->loadTextureNormal(s_tutorialscene_btn_soundgood);
            else if (tutorialPage == 4)
                btnGotIt->loadTextureNormal(s_tutorialscene_btn_letsplay);
            
            touchable = false;
            auto func = CallFunc::create([=]() {
                tutorial->stopAllActions();
                tutorial->runAction(FadeOut::create(0.25f));
                tutorialText->stopAllActions();
                tutorialText->runAction(FadeOut::create(0.25f));
            });

            auto func3 = CallFunc::create([=]() {
//                tutorial->runAction(FadeOut::create(0.5f));
//                tutorialText->runAction
//                (FadeOut::create(0.5f));
            });

            auto func2 = CallFunc::create([=]() {
                
                
                
                
                //Add tutorial text
                if (tutorialPage == 1)
                    tutorialText->setTexture(s_tutorialscene_tutorial);
                else if (tutorialPage == 2)
                    tutorialText->setTexture(s_tutorialscene_tutorial2);
                else if (tutorialPage == 3)
                    tutorialText->setTexture(s_tutorialscene_tutorial3);
                else if (tutorialPage == 4)
                    tutorialText->setTexture(s_tutorialscene_tutorial4);
                
                if(tutorialPage == 4){
                    tutorialText->setPosition(winSize.width / 2, winSize.height * 0.4 - 85);
                }else
                    tutorialText->setPosition(winSize.width / 2, winSize.height * 0.4 - 15);
                
                
                //Add tutorial
                int frameNumber;
                switch (tutorialPage) {
                    case 1:
                        frameNumber = 20;
                        break;
                    case 2:
                        frameNumber = 40;
                        break;
                    case 3:
                        frameNumber = 56;
                        break;
                    case 4:
                        frameNumber = 37;
                        break;
                }
                Vector<SpriteFrame*> animFrames(frameNumber);
                char str[254] = { 0 };
                for (int i = 0; i < frameNumber; i++) {
                    SpriteFrame* frame;
                    if (tutorialPage == 1)
                        frame =
                        SpriteFrame::create(
                                            String::createWithFormat(s_tutorialscene_gif, i)->getCString(),
                                            Rect(0, 0, 768, 500));
                    else if (tutorialPage == 2)
                        frame =
                        SpriteFrame::create(
                                            String::createWithFormat(s_tutorialscene_gif2, i)->getCString(),
                                            Rect(0, 0, 768, 500));
                    else if (tutorialPage == 3)
                        frame =
                        SpriteFrame::create(
                                            String::createWithFormat(s_tutorialscene_gif3, i)->getCString(),
                                            Rect(0, 0, 768, 500));
                    else if (tutorialPage == 4)
                        frame =
                        SpriteFrame::create(
                                            String::createWithFormat(s_tutorialscene_gif4, i)->getCString(),
                                            Rect(0, 0, 768, 768));
                    
                    animFrames.pushBack(frame);
                }
                
                auto animation = Animation::createWithSpriteFrames(animFrames,
                                                                   tutorialPage == 1 ? 0.1f : 0.06f);
                auto animate = Animate::create(animation);
                tutorial->stopAllActions();
                tutorial->runAction(RepeatForever::create(animate));
                
                
                
                
                tutorial->runAction(FadeIn::create(0.25f));
                tutorialText->runAction(FadeIn::create(0.25f));
                
                
                
                touchable = true;
            });
            
            
            this->runAction(
                            Sequence::create(func,DelayTime::create(0.5),func2,DelayTime::create(0.5), func3,nullptr));
         
		} else {
			auto *newScene = SettingScene::scene();
			auto transition = TransitionFade::create(1.0, newScene);
			Director *pDirector = Director::getInstance();
			pDirector->replaceScene(transition);
		}
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

void TutorialScene::onKeyReleased(EventKeyboard::KeyCode keycode,
		Event* event) {
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
