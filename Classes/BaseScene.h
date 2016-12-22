#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "cocos/network/HttpRequest.h"
#include "cocos/network/HttpClient.h"
#include "SimpleAudioEngine.h"
#include "Constants/Resources.h"
#include "Constants/Constants.h"
#include "Constants/RiddleResource.h"
#include "Helper/CppUtils.h"
#include "Helper/RiddleHelper.h"
#include "Helper/SocialPlugin.h"
#include "View/BLabel.h"
#include "View/BScrollView.h"
#include "Helper/CustomDirector.h"

using namespace cocos2d::network;
using namespace cocos2d::ui;
using namespace CocosDenshion;
using namespace std;
using namespace sdkbox;
USING_NS_CC;

class BaseScene: public cocos2d::LayerColor {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	static cocos2d::Scene* scene();

	CREATE_FUNC(BaseScene)
	void showFullscreenAds();

	bool isSound;
	Size winSize;
	Point origin;
};

#endif // __BASE_SCENE_H__
