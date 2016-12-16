#ifndef _STICKER_RESOURCE_H_
#define _STICKER_RESOURCE_H_

#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

class RiddleLevel {
public:
	inline static RiddleLevel* create(string riddle_level_name, string riddle_level_icon_image, Color3B riddle_level_color,
			int sticker_page_id) {
		RiddleLevel* result = new RiddleLevel();
		result->riddle_level_name = riddle_level_name;
		result->riddle_level_icon_image = riddle_level_icon_image;
		result->riddle_level_color = riddle_level_color;
		result->riddle_level_number = riddle_level_number;
		return result;
	}
	string riddle_level_icon_image;
	string riddle_level_name;
	Color3B riddle_level_color;
	int riddle_level_number;
};
class Riddle {
public:
	inline static Sticker* create(string sticker_name, string sticker_image,
			vector<string> sticker_image_animation, Vec2 position,
			string sticker_sound, STICKER_RARITY rarity, int sticker_id,
			int sticker_page_id) {
		Sticker* result = new Sticker();
		result->sticker_image = sticker_image;
		result->sticker_image_animation = sticker_image_animation;
		result->position = position;
		result->sticker_id = sticker_id;
		result->sticker_sound = sticker_sound;
		result->sticker_name = sticker_name;
		result->sticker_page_id = sticker_page_id;
		result->rarity = rarity;
		return result;
	}


	char[2][2] matrix_answer;

	answer[0][0] = 'T';
	answer[0][1] = '';
	answer[1][0] = 'C';
	answer[1][1] = 'A';






	string riddle_hint;
	string riddle_answer;



	int sticker_id;
	int sticker_page_id;
	Vec2 position;
	STICKER_RARITY rarity;
	string sticker_sound;
	string sticker_image;
	string sticker_name;
	vector<string> sticker_image_animation;
};
//
//
//
//
//
//
//
//
//
//Sticker animation list
static vector<string> s_sticker_image_1_animation = {
		"sticker/page1/sticker_1_1.png", "sticker/page1/sticker_1_2.png" };
//
static vector<string> s_sticker_image_2_animation = {
		"sticker/page1/sticker_2_1.png", "sticker/page1/sticker_2_2.png" };
//
static vector<string> s_sticker_image_3_animation = {
		"sticker/page1/sticker_3_1.png", "sticker/page1/sticker_3_2.png" };
//
static vector<string> s_sticker_image_4_animation = {
		"sticker/page1/sticker_4_1.png", "sticker/page1/sticker_4_2.png" };
//
static vector<string> s_sticker_image_5_animation = {
		"sticker/page1/sticker_5_1.png", "sticker/page1/sticker_5_2.png" };
//
//
//
//
//
//
//
//
//
//Sticker information
static vector<Sticker*> vt_stickers = {
//
		Sticker::create("Jaguar","sticker/page1/sticker_1_1.png",
				s_sticker_image_1_animation, Vec2(250, 1350),
				"sticker/page1/sound_1.ogg", STICKER_RARITY::COMMON, 1, 1),
//
		Sticker::create("Tom","sticker/page1/sticker_2_1.png",
				s_sticker_image_2_animation, Vec2(950, 1350),
				"sticker/page1/sound_2.ogg", STICKER_RARITY::UNCOMMON, 2, 1),
//
		Sticker::create("Jerry","sticker/page1/sticker_3_1.png",
				s_sticker_image_3_animation, Vec2(300, 875),
				"sticker/page1/sound_3.ogg", STICKER_RARITY::RARE, 3, 1),
//
		Sticker::create("Harry","sticker/page1/sticker_4_1.png",
				s_sticker_image_4_animation, Vec2(900, 875),
				"sticker/page1/sound_4.ogg", STICKER_RARITY::VERYRARE, 4, 1),
//
		Sticker::create("Monster","sticker/page1/sticker_5_1.png",
				s_sticker_image_5_animation, Vec2(600, 400),
				"sticker/page1/sound_5.ogg", STICKER_RARITY::RAREST, 5, 1),
//
		};
//
//
//
//
//
//
//
//
//
static vector<StickerPage*> vt_sticker_pages = {
//
		StickerPage::create("Jungle 1","sticker/page1/bg_1.png","sticker/page1/icon_1.png", 1),
		StickerPage::create("Jungle 2","sticker/page2/bg_2.png","sticker/page2/icon_2.png", 2),
		StickerPage::create("Jungle 3","sticker/page3/bg_3.png","sticker/page3/icon_3.png", 3),
		StickerPage::create("Jungle 4","sticker/page1/bg_1.png","sticker/page1/icon_1.png", 4),
		StickerPage::create("Jungle 5","sticker/page2/bg_2.png","sticker/page2/icon_2.png", 5),
		StickerPage::create("Jungle 6","sticker/page3/bg_3.png","sticker/page3/icon_3.png", 6),
		StickerPage::create("Jungle 7","sticker/page1/bg_1.png","sticker/page1/icon_1.png", 7),
		StickerPage::create("Jungle 8","sticker/page2/bg_2.png","sticker/page2/icon_2.png", 8),
		StickerPage::create("Jungle 9","sticker/page3/bg_3.png","sticker/page3/icon_3.png", 9),

//
		};
#endif
