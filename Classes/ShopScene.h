#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "BaseScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
class ShopScene: public BaseScene,
AdMobListener,
ChartboostListener,
VungleListener,
IAPListener {
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
class ShopScene: public BaseScene,
AdMobListener,
ChartboostListener,
IAPListener {
#endif
public:
// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
virtual bool init();

// there's no 'id' in cpp, so we recommend returning the class instance pointer
static cocos2d::Scene* scene(Riddle* riddle);
CREATE_FUNC(ShopScene)
void facebookButtonCallback(Ref* pSender,
		ui::Widget::TouchEventType eEventType);
void backButtonCallback(Ref* pSender, ui::Widget::TouchEventType eEventType);
void initIAPButtons();
void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
Product getIAPProductById(string id);
void showRewardedAds();
void earnFreeStickerAfterWatchingAds();
void timer(float interval);
bool isRewardedAdsAvailable();
Button* buttonRewardedAds;
Label* labelCurrentHint;
Label* labelWatchVideo;

int timeToWatchAdsInSecond;
//IAP + Ads callbacks
//IAP
virtual void onInitialized(bool success);
virtual void onSuccess(const Product& p);
virtual void onFailure(const Product& p, const std::string& msg);
virtual void onCanceled(const Product& p);
virtual void onRestored(const Product& p);
virtual void onProductRequestSuccess(const std::vector<Product>& products);
virtual void onProductRequestFailure(const std::string& msg);
virtual void onRestoreComplete(bool ok, const std::string &msg);
//Admob
virtual void adViewDidReceiveAd(const std::string &name);
virtual void adViewDidFailToReceiveAdWithError(const std::string &name,
		const std::string &msg);
virtual void adViewWillPresentScreen(const std::string &name);
virtual void adViewDidDismissScreen(const std::string &name);
virtual void adViewWillDismissScreen(const std::string &name);
virtual void adViewWillLeaveApplication(const std::string &name);
//Chartboost
virtual void onChartboostCached(const std::string& name);
virtual bool onChartboostShouldDisplay(const std::string& name);
virtual void onChartboostDisplay(const std::string& name);
virtual void onChartboostDismiss(const std::string& name);
virtual void onChartboostClose(const std::string& name);
virtual void onChartboostClick(const std::string& name);
virtual void onChartboostReward(const std::string& name, int reward);
virtual void onChartboostFailedToLoad(const std::string& name, CB_LoadError e);
virtual void onChartboostFailToRecordClick(const std::string& name,
		CB_ClickError e);
virtual void onChartboostConfirmation();
virtual void onChartboostCompleteStore();
//Vungle
virtual void onVungleCacheAvailable();
virtual void onVungleStarted();
virtual void onVungleFinished();
virtual void onVungleAdViewed(bool isComplete);
virtual void onVungleAdReward(const std::string& name);
};

#endif
