#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//--------------------------------------------------------------------------------------------------------- KEYS - Dont change it

//Keys on Firebase and UserDefault
#define KEY_PROBABILITY_COMMON "common"
#define KEY_PROBABILITY_UNCOMMON "uncommon"
#define KEY_PROBABILITY_RARE "rare"
#define KEY_PROBABILITY_VERYRARE "veryrare"
#define KEY_PROBABILITY_RAREST "rarest"
#define KEY_WORLD_NAME       "FB_Name"
#define KEY_WORLD_ID         "FB_ID"
#define KEY_WORLD_OJECTID    "ObjectID"
#define KEY_WORLD_ALL_STICKERS "All_Stickers"
#define KEY_WORLD_STICKED_STICKERS "Sticked_Stickers"
#define KEY_WORLD_PENDING_REQUEST "Pending_Request"
#define KEY_WORLD_GIVEN_STICKERS "Given_Stickers"

//Admob key (corresponding with .json file in Resources)
#define kAdmobInstitialAds "fullscreen_ads"
#define kChartboostInstitialAds "fullscreen_ads"
#define kVungleInstitialAds "video"
#define kChartboostRewardedAds "rewarded_ads"
#define kVungleRewardedAds "reward"

//Global KEY
#define SOUND "sound"
#define MUSIC "music"
#define ALERT "alert"
#define CURRENT_STICKER "currentsticker"  //An array of gotten sticker id: 1,2,4,6,3,8,5
#define CURRENT_PACKET "currentpacket"  //An array of packet rarity: 1,2,4
#define STICKED_STICKER "stickedsticker"  //An array of gotten sticker id: 1,2,4,6,3,8,5
#define TIME_TO_GET_FREE_STICKER_IN_SECOND "TIME_TO_GET_FREE_STICKER_IN_SECOND"
#define KEY_FACEBOOK_FIRST_TIME_LOGGING_IN "keyfacebookfirsttimeloggingin"
#define ACTIVE_PACKET "ACTIVE_PACKET"
#define ACTIVE_RIDDLE "ACTIVE_RIDDLE"
#define HINT_NUMBER "HINT_NUMBER"

//--------------------------------------------------------------------------------------------------------- KEYS - Dont change it

//Default value
#define SELLING_STICKER_NUMBER_TO_GET_A_PACKET 4 //sacrifice 4 stickers to get a packet
#define TIME_TO_GET_FREE_PACKET_IN_SECOND 300 //300 seconds to get a free packet
#define GIVEN_PACKETS_AT_FIRST_INSTALL "0,1,2,2" //Give user 1 free packet, 1 common packet, 2 uncommon packet when first installed

#define FACEBOOK_INVITE_IMAGE_URL "http://www.cocos2d-x.org/attachments/801/cocos2dx_portrait.png"
#define FACEBOOK_INVITE_APP_URL "https://fb.me/322164761287181"

#define ACTIVE_PACKET_DEFAULT_VALUE "1,2"
#define ACTIVE_RIDDLE_DEFAULT_VALUE "1"

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
