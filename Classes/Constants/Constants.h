#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//--------------------------------------------------------------------------------------------------------- KEYS - Dont change it
//String
#define NOTIFICATION_USED_HINT_ENOUGH "Your task now is to connect all\nthe letter to be the correct answer"
#define NOTIFICATION_GOT_1_FREE_HINT "Got 1 free hint!"
#define NOTIFICATION_GOT_PURCHASED_HINT "Got %d hints!"
#define NOTIFICATION_GOT_ALL_HINT_FOR_PASSING_A_PACKET "Got all hints for passing a package!"
#define NOTIFICATION_UNLOCK_NEW_PACK "New level pack unlocked!"

//Admob key (corresponding with .json file in Resources)
#define kAdmobBannerAds "banner_ads"
#define kAdmobInstitialAds "fullscreen_ads"
#define kChartboostInstitialAds "fullscreen_ads"
#define kVungleInstitialAds "video"
#define kChartboostRewardedAds "rewarded_ads"
#define kVungleRewardedAds "reward"

//Global KEY
#define SOUND "sound"
#define MUSIC "music"
#define ACTIVE_PACKET "ACTIVE_PACKET"
#define ACTIVE_RIDDLE "ACTIVE_RIDDLE"
#define HINT_NUMBER "HINT_NUMBER"
#define USED_HINT "USED_HINT"
#define CHOSEN_TAG "CHOSEN_TAG"
#define KEY_WIN_CONTINUALLY_NUMBER_TO_SHOW_ADS "KEY_WIN_CONTINUALLY_NUMBER_TO_SHOW_ADS"
#define KEY_WIN_CONTINUALLY_NUMBER_TO_GIVE_HINT "KEY_WIN_CONTINUALLY_NUMBER_TO_GIVE_HINT"
#define KEY_IS_DAILY_PUZZLE_MODE "KEY_IS_DAILY_PUZZLE_MODE"
#define KEY_DAILY_PUZZLE_WINNING_DATE "KEY_DAILY_PUZZLE_WINNING_DATE"
#define KEY_DAILY_PUZZLE_RIDDLE_ID "KEY_DAILY_PUZZLE_RIDDLE_ID"
#define KEY_LAST_PLAYED_LEVEL "KEY_LAST_PLAYED_LEVEL"
#define KEY_TIME_TO_WATCH_ADS_IN_SECOND "KEY_TIME_TO_WATCH_ADS_IN_SECOND"
#define KEY_WAITING_TO_OPEN_INVITE_FACEBOOK "KEY_WAITING_TO_OPEN_INVITE_FACEBOOK"

//--------------------------------------------------------------------------------------------------------- KEYS - Dont change it

//Default value
#define FACEBOOK_INVITE_IMAGE_URL "http://www.cocos2d-x.org/attachments/801/cocos2dx_portrait.png"
#define FACEBOOK_INVITE_APP_URL "https://fb.me/322164761287181"

#define ACTIVE_PACKET_DEFAULT_VALUE 1
#define ACTIVE_RIDDLE_DEFAULT_VALUE 9
#define HINT_NUMBER_DEFAULT_VALUE 10
#define SHOW_FULLSCREEN_ADS_AFTER_WINNING_TIMES 5
#define GIVE_USER_A_HINT_AFTER_WINNING_TIMES 10
#define TIME_TO_WATCH_ADS_IN_SECOND 14400

//IAP info
#define IAP_ANDROID_PACK1_KEY "pack_1"
#define IAP_ANDROID_PACK2_KEY "pack_2"
#define IAP_ANDROID_PACK3_KEY "pack_3"
#define IAP_ANDROID_PACK4_KEY "pack_4"
#define IAP_ANDROID_PACK5_KEY "pack_5"
#define IAP_ANDROID_PACK6_KEY "pack_6"

#define IAP_IOS_PACK1_KEY "coin_package"
#define IAP_IOS_PACK2_KEY "coin_package"
#define IAP_IOS_PACK3_KEY "coin_package"
#define IAP_IOS_PACK4_KEY "coin_package2"
#define IAP_IOS_PACK5_KEY "coin_package2"
#define IAP_IOS_PACK6_KEY "coin_package2"

#define IAP_HINT_NUMBER_TO_GET_PACK1 15
#define IAP_HINT_NUMBER_TO_GET_PACK2 40
#define IAP_HINT_NUMBER_TO_GET_PACK3 75
#define IAP_HINT_NUMBER_TO_GET_PACK4 175
#define IAP_HINT_NUMBER_TO_GET_PACK5 500
#define IAP_HINT_NUMBER_TO_GET_PACK6 -100 //IMPORTANT: -100 means all hints for passing a package

#define IAP_PACK1_NAME "15 hints"
#define IAP_PACK2_NAME "40 hints"
#define IAP_PACK3_NAME "75 hints"
#define IAP_PACK4_NAME "175 hints"
#define IAP_PACK5_NAME "500 hints"
#define IAP_PACK6_NAME "Level Clear"

#define IAP_PACK1_DESCRIPTION ""
#define IAP_PACK2_DESCRIPTION ""
#define IAP_PACK3_DESCRIPTION ""
#define IAP_PACK4_DESCRIPTION "most popular!"
#define IAP_PACK5_DESCRIPTION "best deals"
#define IAP_PACK6_DESCRIPTION "all hints"

//URL
#define s_linkToGooglePlayMoreGame "https://play.google.com/store/apps/developer?id=Khoi+Nguyen+Entertainment"
#define s_linkToAppStoreMoreGame "itms-apps://itunes.apple.com/apps/MySoftSource"
#define s_linkToGooglePlayRating "https://play.google.com/store/apps/details?id=com.khoinguyenentertainment.onetanimal"
#define s_linkToAppStoreRating "itms-apps://itunes.apple.com/apps/MySoftSource"
#define s_linkToFacebookPage "https://www.facebook.com/pages/Bored-Ninjas/804597329582378?ref=br_rs"

#endif
