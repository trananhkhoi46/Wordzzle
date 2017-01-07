#ifndef _RIDDLE_RESOURCE_H_
#define _RIDDLE_RESOURCE_H_

#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

class RiddlePacket {
public:
	inline static RiddlePacket* create(string riddle_packet_name,
			string riddle_packet_icon_image, int riddle_packet_id) {
		RiddlePacket* result = new RiddlePacket();
		result->riddle_packet_name = riddle_packet_name;
		result->riddle_packet_icon_image = riddle_packet_icon_image;
		result->riddle_packet_id = riddle_packet_id;
		return result;
	}
	string riddle_packet_icon_image;
	string riddle_packet_name;
	int riddle_packet_id;
};
class Riddle {
public:
	inline static Riddle* create(string riddle_hint, string riddle_answer,
			int riddle_packet_id, int riddle_id, int riddle_level,
			vector<vector<string>> riddle_answer_matrix) {
		Riddle* result = new Riddle();
		result->riddle_hint = riddle_hint;
		result->riddle_answer = riddle_answer;
		result->riddle_packet_id = riddle_packet_id;
		result->riddle_id = riddle_id;
		result->riddle_level = riddle_level;
		result->riddle_answer_matrix = riddle_answer_matrix;
		return result;
	}

	vector<vector<string>> riddle_answer_matrix;
	string riddle_hint;
	string riddle_answer;
	int riddle_packet_id;
	int riddle_id;
	int riddle_level;
};
//
//
//
//
//
//
//
//
//Sticker information
/**
 *VERY IMPORTATN: the matrix must be a square matrix
 *EX: the size must be 3x3, 4x4, 5x5. Don't use size 4x5
 *use "_" for a temp letter
 */
static vector<Riddle*> vt_riddles = {
//
		Riddle::create("animal", "cat", 1, 1, 1, {
		//
				{ "T", "_" },
				////////
				{ "C", "A" }
		//
				}),
//
		Riddle::create("like fire", "hot", 1, 2, 2, {
		//
				{ "H", "T" },
				////////
				{ "O", "_" }
		//
				}),
//
		Riddle::create("eaten with bacon", "egg", 1, 3, 3, {
		//
				{ "E", "G" },
				////////
				{ "G", "_" }
		//
				}),
//
		Riddle::create("on your foot", "toe", 1, 4, 4, {
		//
				{ "O", "E" },
				////////
				{ "_", "T" }
		//
				}),
		//
		Riddle::create("rodent", "rat", 1, 5, 5, {
		//
				{ "R", "T" },
				////////
				{ "A", "_" }
		//
				}),
		//
		Riddle::create("winter", "ice", 1, 6, 6, {
		//
				{ "E", "I" },
				////////
				{ "_", "C" }
		//
				}),
//
		Riddle::create("water creature", "eel", 1, 7, 7, {
		//
				{ "E", "_" },
				////////
				{ "E", "L" }
		//
				}),
		//
		Riddle::create("insect", "fly", 1, 8, 8, {
		//
				{ "L", "F" },
				////////
				{ "_", "Y" }
		//
				}),
		//
		Riddle::create("damp", "wet", 1, 9, 9, {
		//
				{ "T", "_" },
				////////
				{ "E", "W" }
		//
				}),
		//
		Riddle::create("tree", "ash", 1, 10, 10, {
		//
				{ "_", "H" },
				////////
				{ "A", "S" }
		//
				}),
		//
		Riddle::create("body of water", "lake", 2, 11, 1, {
		//
				{ "E", "L" },
				////////
				{ "K", "A" }
		//
				}),
		//
		Riddle::create("humorous", "joke", 2, 12, 2, {
		//
				{ "E", "J" },
				////////
				{ "O", "K" }
		//
				}),
//
		Riddle::create("seen at night", "moth", 2, 13, 3, {
		//
				{ "O", "T" },
				////////
				{ "H", "M" }
		//
				}),
		//
		Riddle::create("heavy metal", "iron", 2, 14, 4, {
		//
				{ "N", "I" },
				////////
				{ "R", "O" }
		//
				}),
		//
		Riddle::create("fruit", "lime", 2, 15, 5, {
		//
				{ "E", "L" },
				////////
				{ "I", "M" }
		//
				}),
		//
		Riddle::create("church leader", "pope", 2, 16, 6, {
		//
				{ "P", "O" },
				////////
				{ "P", "E" }
		//
				}),
		//
		Riddle::create("it shines overhead", "moon", 2, 17, 7, {
		//
				{ "N", "O" },
				////////
				{ "O", "M" }
		//
				}),
		//
		Riddle::create("nocturnal predator", "wolf", 2, 18, 8, {
		//
				{ "W", "L" },
				////////
				{ "F", "O" }
		//
				}),
		//
		Riddle::create("untamed feline", "lion", 2, 19, 9, {
		//
				{ "L", "O" },
				////////
				{ "I", "N" }
		//
				}),
		//
		Riddle::create("flower", "iris", 2, 20, 10, {
		//
				{ "R", "I" },
				////////
				{ "S", "I" }
		//
				}),
		//
		Riddle::create("exotic fruit", "kumquat", 3, 21, 1, {
		//
				{ "_", "K", "U" },
				////////
				{ "A", "T", "M" },
				////////
				{ "_", "U", "Q" }
		//
				}),
		//
		Riddle::create("little", "tiny wee", 3, 22, 2, {
		//
				{ "_", "_", "N" },
				////////
				{ "T", "I", "Y" },
				////////
				{ "W", "E", "E" }
		//
				}),
		//
		Riddle::create("dinnerware", "fork cup", 3, 23, 3, {
		//
				{ "U", "P", "K" },
				////////
				{ "C", "R", "F" },
				////////
				{ "_", "O", "_" }
		//
				}),
		//
		Riddle::create("weekday", "tuesday", 3, 24, 4, {
		//
				{ "_", "S", "E" },
				////////
				{ "D", "A", "U" },
				////////
				{ "Y", "_", "T" }
		//
				}),
		//
		Riddle::create("modes of transport", "bus auto", 3, 25, 5, {
		//
				{ "_", "U", "A" },
				////////
				{ "B", "S", "U" },
				////////
				{ "O", "T", "_" }
		//
				}),
		//
		Riddle::create("spring months", "may june", 3, 26, 6, {
		//
				{ "_", "_", "E" },
				////////
				{ "A", "J", "N" },
				////////
				{ "M", "Y", "U" }
		//
				}),
		//
		Riddle::create("beyond earth", "star sun", 3, 27, 7, {
		//
				{ "_", "T", "A" },
				////////
				{ "_", "R", "S" },
				////////
				{ "S", "U", "N" }
		//
				}),
		//
		Riddle::create("sit on it", "lounger", 3, 28, 8, {
		//
				{ "U", "N", "_" },
				////////
				{ "O", "L", "G" },
				////////
				{ "R", "E", "_" }
		//
				}),
		//
		Riddle::create("facial features", "nose brow", 3, 29, 9, {
		//
				{ "N", "W", "O" },
				////////
				{ "_", "O", "R" },
				////////
				{ "E", "S", "B" }
		//
				}),
		//
		Riddle::create("often served at breakfast", "pancake", 3, 30, 10, {
		//
				{ "_", "P", "K" },
				////////
				{ "A", "E", "A" },
				////////
				{ "N", "C", "_" }
		//
				}),
		//
		Riddle::create("at the seashore", "shell sand", 4, 31, 1, {
		//
				{ "D", "L", "E" },
				////////
				{ "N", "L", "H" },
				////////
				{ "A", "S", "S" }
		//
				}),
		//
		Riddle::create("contains three points", "triangle", 4, 32, 2, {
		//
				{ "A", "I", "_" },
				////////
				{ "N", "T", "R" },
				////////
				{ "G", "L", "E" }
		//
				}),
		//
		Riddle::create("colors in the sky", "rainbow", 4, 33, 3, {
		//
				{ "B", "O", "_" },
				////////
				{ "A", "N", "W" },
				////////
				{ "R", "I", "_" }
		//
				}),
		//
		Riddle::create("cheerful", "happy glad", 4, 34, 4, {
		//
				{ "D", "A", "P" },
				////////
				{ "L", "P", "A" },
				////////
				{ "Y", "G", "H" }
		//
				}),
		//
		Riddle::create("human joints", "elbow knee", 4, 35, 5, {
		//
				{ "K", "B", "O" },
				////////
				{ "N", "L", "W" },
				////////
				{ "E", "E", "E" }
		//
				}),
		//
		Riddle::create("at the breakfast table", "coffee egg", 4, 36, 6, {
		//
				{ "O", "C", "G" },
				////////
				{ "F", "E", "G" },
				////////
				{ "E", "F", "E" }
		//
				}),
		//
		Riddle::create("extremities", "arm foot", 4, 37, 7, {
		//
				{ "T", "O", "O" },
				////////
				{ "M", "F", "A" },
				////////
				{ "_", "R", "_" }
		//
				}),
		//
		Riddle::create("worn on the neck", "pendant", 4, 38, 8, {
		//
				{ "N", "E", "_" },
				////////
				{ "A", "D", "P" },
				////////
				{ "T", "N", "_" }
		//
				}),
		//
		Riddle::create("shirt", "tunic tee", 4, 39, 9, {
		//
				{ "T", "I", "_" },
				////////
				{ "C", "E", "N" },
				////////
				{ "E", "T", "U" }
		//
				}),
		//
		Riddle::create("musical insect", "cricket", 4, 40, 10, {
		//
				{ "K", "C", "_" },
				////////
				{ "E", "C", "R" },
				////////
				{ "T", "I", "_" }
		//
				}),
		//
		Riddle::create("before dinner", "appetizer", 5, 41, 1, {
		//
				{ "E", "P", "P" },
				////////
				{ "Z", "T", "A" },
				////////
				{ "I", "E", "R" }
		//
				}),
		//
		Riddle::create("silent", "mute mum", 5, 42, 2, {
		//
				{ "_", "M", "U" },
				////////
				{ "T", "U", "M" },
				////////
				{ "M", "E", "_" }
		//
				}),
		//
		Riddle::create("springtime sights", "flowers", 5, 43, 3, {
		//
				{ "E", "R", "S" },
				////////
				{ "L", "W", "_" },
				////////
				{ "F", "O", "_" }
		//
				}),
		//
		Riddle::create("marsupial", "opossum", 5, 44, 4, {
		//
				{ "_", "M", "_" },
				////////
				{ "O", "O", "U" },
				////////
				{ "P", "S", "S" }
		//
				}),
		//
		Riddle::create("on stage", "rehearsal", 5, 45, 5, {
		//
				{ "E", "A", "L" },
				////////
				{ "H", "A", "R" },
				////////
				{ "R", "E", "S" }
		//
				}),
		//
		Riddle::create("quick cooker", "microwave", 5, 46, 6, {
		//
				{ "A", "W", "O" },
				////////
				{ "E", "V", "R" },
				////////
				{ "M", "I", "C" }
		//
				}),
		//
		Riddle::create("for the birds", "beak worm", 5, 47, 7, {
		//
				{ "_", "W", "O" },
				////////
				{ "B", "E", "R" },
				////////
				{ "A", "K", "M" }
		//
				}),
		//
		Riddle::create("a large animal", "giraffe", 5, 48, 8, {
		//
				{ "F", "I", "R" },
				////////
				{ "F", "A", "G" },
				////////
				{ "_", "E", "_" }
		//
				}),
		//
		Riddle::create("on the work desk", "computer", 5, 49, 9, {
		//
				{ "E", "R", "O" },
				////////
				{ "T", "C", "M" },
				////////
				{ "_", "U", "P" }
		//
				}),
		//
		Riddle::create("inside the body", "organ vein", 5, 50, 10, {
		//
				{ "N", "R", "O" },
				////////
				{ "I", "A", "G" },
				////////
				{ "N", "E", "V" }
		//
				}),

		//
		Riddle::create("winter gear", "coat scarf", 6, 51, 1, {
		//
				{ "C", "A", "S" },
				////////
				{ "O", "R", "C" },
				////////
				{ "A", "T", "F" }
		//
				}),
		//
		Riddle::create("found on a book cover", "subtitle", 6, 52, 2, {
		//
				{ "U", "B", "E" },
				////////
				{ "S", "T", "L" },
				////////
				{ "_", "I", "T" }
		//
				}),
		//
		Riddle::create("on a clock face", "dial time", 6, 53, 3, {
		//
				{ "T", "D", "L" },
				////////
				{ "I", "A", "I" },
				////////
				{ "E", "M", "_" }
		//
				}),
		//
		Riddle::create("at the farm", "farmer hay", 6, 54, 4, {
		//
				{ "R", "H", "M" },
				////////
				{ "A", "E", "R" },
				////////
				{ "Y", "A", "F" }
		//
				}),
		//
		Riddle::create("stereo equipment", "speakers", 6, 55, 5, {
		//
				{ "A", "P", "_" },
				////////
				{ "E", "K", "S" },
				////////
				{ "E", "R", "S" }
		//
				}),
		//
		Riddle::create("drinks for a cold day", "cocoa tea", 6, 56, 6, {
		//
				{ "T", "O", "C" },
				////////
				{ "C", "E", "_" },
				////////
				{ "O", "A", "A" }
		//
				}),
		//
		Riddle::create("on your phone", "cattle hay", 6, 57, 7, {
		//
				{ "L", "T", "Y" },
				////////
				{ "T", "E", "A" },
				////////
				{ "C", "A", "H" }
		//
				}),
		//
		Riddle::create("to toss", "lob heave", 6, 58, 8, {
		//
				{ "_", "V", "E" },
				////////
				{ "A", "B", "O" },
				////////
				{ "E", "H", "L" }
		//
				}),
		//
		Riddle::create("extreme weather", "hurricane", 6, 59, 9, {
		//
				{ "R", "U", "H" },
				////////
				{ "R", "I", "N" },
				////////
				{ "C", "A", "E" }
		//
				}),
		//
		Riddle::create("found in the garden", "pest soil", 6, 60, 10, {
		//
				{ "L", "I", "O" },
				////////
				{ "S", "T", "S" },
				////////
				{ "P", "E", "_" }
		//
				}),

		//
		Riddle::create("sticky food", "honey gum", 7, 61, 1, {
		//
				{ "_", "O", "N" },
				////////
				{ "H", "E", "Y" },
				////////
				{ "G", "U", "M" }
		//
				}),
		//
		Riddle::create("split", "halve cut", 7, 62, 2, {
		//
				{ "_", "C", "H" },
				////////
				{ "U", "A", "V" },
				////////
				{ "T", "E", "L" }
		//
				}),
		//
		Riddle::create("on a fishing pole", "bait line", 7, 63, 3, {
		//
				{ "E", "N", "I" },
				////////
				{ "I", "A", "L" },
				////////
				{ "B", "T", "_" }
		//
				}),
		//
		Riddle::create("in a chess set", "king rook", 7, 64, 4, {
		//
				{ "_", "I", "K" },
				////////
				{ "N", "O", "R" },
				////////
				{ "K", "G", "O" }
		//
				}),
		//
		Riddle::create("on a rooster", "feathers", 7, 65, 5, {
		//
				{ "H", "E", "R" },
				////////
				{ "F", "T", "S" },
				////////
				{ "A", "E", "_" }
		//
				}),
		//
		Riddle::create("lives underground", "gopher rat", 7, 66, 6, {
		//
				{ "T", "R", "G" },
				////////
				{ "A", "O", "E" },
				////////
				{ "P", "H", "R" }
		//
				}),
		//
		Riddle::create("water transportation", "boat raft", 7, 67, 7, {
		//
				{ "T", "A", "_" },
				////////
				{ "F", "B", "O" },
				////////
				{ "T", "A", "R" }
		//
				}),
		//
		Riddle::create("after-dinner treat", "cake tart", 7, 68, 8, {
		//
				{ "_", "E", "T" },
				////////
				{ "C", "K", "A" },
				////////
				{ "A", "T", "R" }
		//
				}),
		//
		Riddle::create("it's said", "verb word", 7, 69, 9, {
		//
				{ "D", "O", "W" },
				////////
				{ "R", "V", "B" },
				////////
				{ "E", "R", "_" }
		//
				}),
		//
		Riddle::create("exercise", "jog squat", 7, 70, 10, {
		//
				{ "_", "G", "S" },
				////////
				{ "T", "O", "Q" },
				////////
				{ "A", "U", "J" }
		//
				}),

		//
		Riddle::create("large instruments", "piano harp", 8, 71, 1, {
		//
				{ "P", "O", "A" },
				////////
				{ "N", "R", "H" },
				////////
				{ "A", "I", "P" }
		//
				}),
		//
		Riddle::create("on a tree", "bark knot", 8, 72, 2, {
		//
				{ "T", "O", "K" },
				////////
				{ "A", "N", "K" },
				////////
				{ "B", "R", "_" }
		//
				}),
		//
		Riddle::create("to cook", "broil bake", 8, 73, 3, {
		//
				{ "E", "K", "B" },
				////////
				{ "A", "R", "I" },
				////////
				{ "B", "L", "O" }
		//
				}),
		//
		Riddle::create("worn in the hair", "barrette", 8, 74, 4, {
		//
				{ "R", "R", "_" },
				////////
				{ "E", "A", "B" },
				////////
				{ "T", "T", "E" }
		//
				}),
		//
		Riddle::create("used in the kitchen", "pan knife", 8, 75, 5, {
		//
				{ "N", "K", "P" },
				////////
				{ "I", "N", "A" },
				////////
				{ "F", "E", "_" }
		//
				}),
		//
		Riddle::create("shoes", "clog boot", 8, 76, 6, {
		//
				{ "O", "O", "_" },
				////////
				{ "B", "O", "T" },
				////////
				{ "L", "C", "G" }
		//
				}),
		//
		Riddle::create("on a ruler", "foot inch", 8, 77, 7, {
		//
				{ "_", "H", "O" },
				////////
				{ "C", "O", "T" },
				////////
				{ "I", "N", "F" }
		//
				}),
		//
		Riddle::create("found at sea", "whale boat", 8, 78, 8, {
		//
				{ "T", "A", "H" },
				////////
				{ "A", "W", "L" },
				////////
				{ "O", "B", "A" }
		//
				}),
		//
		Riddle::create("types of music", "rock opera", 8, 79, 9, {
		//
				{ "A", "R", "P" },
				////////
				{ "C", "E", "O" },
				////////
				{ "K", "O", "R" }
		//
				}),
		//
		Riddle::create("at dusk", "nightfall", 8, 80, 10, {
		//
				{ "L", "A", "F" },
				////////
				{ "L", "T", "G" },
				////////
				{ "N", "I", "H" }
		//
				}),

		//
		Riddle::create("months abrev", "nov jan feb", 9, 81, 1, {
		//
				{ "N", "O", "B" },
				////////
				{ "J", "V", "E" },
				////////
				{ "A", "N", "F" }
		//
				}),
		//
		Riddle::create("orderly", "clean trim", 9, 82, 2, {
		//
				{ "T", "N", "C" },
				////////
				{ "R", "L", "A" },
				////////
				{ "I", "M", "E" }
		//
				}),
		//
		Riddle::create("drink", "guzzle sip", 9, 83, 3, {
		//
				{ "S", "Z", "Z" },
				////////
				{ "I", "U", "L" },
				////////
				{ "P", "E", "G" }
		//
				}),
		//
		Riddle::create("large bird", "ostrich", 9, 84, 4, {
		//
				{ "_", "H", "C" },
				////////
				{ "T", "S", "I" },
				////////
				{ "O", "R", "_" }
		//
				}),
		//
		Riddle::create("young male", "boy lad son", 9, 85, 5, {
		//
				{ "N", "O", "S" },
				////////
				{ "B", "O", "L" },
				////////
				{ "Y", "A", "D" }
		//
				}),
		//
		Riddle::create("verbs that move", "walk go jog", 9, 86, 6, {
		//
				{ "G", "O", "G" },
				////////
				{ "K", "J", "O" },
				////////
				{ "L", "A", "W" }
		//
				}),
		//
		Riddle::create("take a ___", "hike bite", 9, 87, 7, {
		//
				{ "T", "E", "K" },
				////////
				{ "I", "E", "I" },
				////////
				{ "_", "B", "H" }
		//
				}),
		//
		Riddle::create("you can drink out of it", "jar cup can", 9, 88, 8, {
		//
				{ "P", "U", "J" },
				////////
				{ "C", "A", "N" },
				////////
				{ "R", "C", "A" }
		//
				}),
		//
		Riddle::create("internet domains", "net edu org", 9, 89, 9, {
		//
				{ "G", "E", "N" },
				////////
				{ "R", "T", "E" },
				////////
				{ "O", "U", "D" }
		//
				}),
		//
		Riddle::create("it flies", "kite plane", 9, 90, 10, {
		//
				{ "A", "N", "E" },
				////////
				{ "L", "I", "K" },
				////////
				{ "P", "E", "T" }
		//
				}),

		//
		Riddle::create("the passage of time", "week day", 10, 91, 1, {
		//
				{ "_", "A", "_" },
				////////
				{ "D", "E", "Y" },
				////////
				{ "W", "E", "K" }
		//
				}),
		//
		Riddle::create("it's new", "current", 10, 92, 2, {
		//
				{ "R", "R", "U" },
				////////
				{ "N", "E", "C" },
				////////
				{ "T", "_", "_" }
		//
				}),
		//
		Riddle::create("tiny bugs", "gnat ant", 10, 93, 3, {
		//
				{ "T", "A", "_" },
				////////
				{ "N", "T", "_" },
				////////
				{ "G", "A", "N" }
		//
				}),
		//
		Riddle::create("in the family", "mom son dad", 10, 94, 4, {
		//
				{ "D", "A", "D" },
				////////
				{ "S", "O", "M" },
				////////
				{ "N", "M", "O" }
		//
				}),
		//
		Riddle::create("on your computer", "software", 10, 95, 5, {
		//
				{ "A", "R", "E" },
				////////
				{ "W", "O", "F" },
				////////
				{ "S", "T", "_" }
		//
				}),
		//
		Riddle::create("it's placed on your head", "hat pat cap", 10, 96, 6, {
		//
				{ "T", "A", "P" },
				////////
				{ "H", "A", "C" },
				////////
				{ "P", "A", "T" }
		//
				}),
		//
		Riddle::create("onomatopoeia", "thud roar", 10, 97, 7, {
		//
				{ "H", "T", "R" },
				////////
				{ "U", "R", "O" },
				////////
				{ "D", "T", "_" }
		//
				}),
		//
		Riddle::create("turn it", "wind twist", 10, 98, 8, {
		//
				{ "I", "S", "W" },
				////////
				{ "W", "I", "T" },
				////////
				{ "T", "N", "D" }
		//
				}),
		//
		Riddle::create("outer edge", "top tip rim", 10, 99, 9, {
		//
				{ "P", "R", "I" },
				////////
				{ "O", "I", "M" },
				////////
				{ "T", "P", "T" }
		//
				}),
		//
		Riddle::create("young animal", "cub chick", 10, 100, 10, {
		//
				{ "C", "I", "H" },
				////////
				{ "K", "C", "U" },
				////////
				{ "_", "C", "B" }
		//
				}),
		//
		Riddle::create("on a keyboard", "backspace", 11, 101, 1, {
		//
				{ "B", "A", "C" },
				////////
				{ "E", "K", "P" },
				////////
				{ "C", "A", "S" }
		//
				}),
		//
		Riddle::create("comfortable", "cushy snug", 11, 102, 2, {
		//
				{ "G", "U", "C" },
				////////
				{ "Y", "U", "N" },
				////////
				{ "S", "H", "S" }
		//
				}),
		//
		Riddle::create("for the gardener", "rake mower", 11, 103, 3, {
		//
				{ "R", "E", "W" },
				////////
				{ "E", "R", "O" },
				////////
				{ "K", "A", "M" }
		//
				}),
		//
		Riddle::create("in the desert", "sand cacti", 11, 104, 4, {
		//
				{ "A", "C", "T" },
				////////
				{ "C", "I", "S" },
				////////
				{ "D", "N", "A" }
		//
				}),
		//
		Riddle::create("legal professional", "attorney", 11, 105, 5, {
		//
				{ "A", "T", "T" },
				////////
				{ "N", "Y", "O" },
				////////
				{ "E", "R", "_" }
		//
				}),
		//
		Riddle::create("on the map", "road town", 11, 106, 6, {
		//
				{ "N", "W", "O" },
				////////
				{ "D", "A", "T" },
				////////
				{ "O", "R", "_" }
		//
				}),
		//
		Riddle::create("green things", "money leaf", 11, 107, 7, {
		//
				{ "A", "Y", "E" },
				////////
				{ "E", "F", "N" },
				////////
				{ "L", "M", "O" }
		//
				}),
		//
		Riddle::create("in the ear", "wax sound", 11, 108, 8, {
		//
				{ "S", "W", "U" },
				////////
				{ "A", "O", "N" },
				////////
				{ "X", "D", "_" }
		//
				}),
		//
		Riddle::create("during peacetime", "armistice", 11, 109, 9, {
		//
				{ "M", "I", "S" },
				////////
				{ "A", "R", "T" },
				////////
				{ "E", "C", "I" }
		//
				}),
		//
		Riddle::create("back___", "pack stab", 11, 110, 10, {
		//
				{ "_", "K", "B" },
				////////
				{ "P", "C", "A" },
				////////
				{ "A", "T", "S" }
		//
				}),
		//
		Riddle::create("on a car", "hood wheel", 12, 111, 1, {
		//
				{ "H", "O", "L" },
				////////
				{ "H", "E", "O" },
				////////
				{ "E", "W", "D" }
		//
				}),
		//
		Riddle::create("directions", "south west", 12, 112, 2, {
		//
				{ "H", "T", "W" },
				////////
				{ "U", "S", "E" },
				////////
				{ "T", "O", "S" }
		//
				}),
		//
		Riddle::create("winter clothing", "gloves hat", 12, 113, 3, {
		//
				{ "O", "L", "T" },
				////////
				{ "V", "A", "G" },
				////////
				{ "E", "S", "H" }
		//
				}),
		//
		Riddle::create("bodies of fresh water", "lake river", 12, 114, 4, {
		//
				{ "R", "I", "V" },
				////////
				{ "L", "A", "E" },
				////////
				{ "K", "E", "R" }
		//
				}),
		//
		Riddle::create("you can roll it", "dough dice", 12, 115, 5, {
		//
				{ "C", "E", "D" },
				////////
				{ "H", "I", "O" },
				////////
				{ "D", "G", "U" }
		//
				}),
		//
		Riddle::create("summertime", "hot sun", 12, 116, 6, {
		//
				{ "_", "N", "_" },
				////////
				{ "_", "U", "T" },
				////////
				{ "S", "O", "H" }
		//
				}),
		//
		Riddle::create("overly sweet", "cloying", 12, 117, 7, {
		//
				{ "_", "Y", "N" },
				////////
				{ "O", "G", "I" },
				////////
				{ "C", "L", "_" }
		//
				}),
		//
		Riddle::create("playing pool", "stick felt", 12, 118, 8, {
		//
				{ "I", "T", "T" },
				////////
				{ "C", "L", "S" },
				////////
				{ "K", "F", "E" }
		//
				}),
		//
		Riddle::create("in the tree", "nest limb", 12, 119, 9, {
		//
				{ "_", "E", "N" },
				////////
				{ "T", "S", "M" },
				////////
				{ "L", "I", "B" }
		//
				}),
		//
		Riddle::create("in cold weather", "frost ice", 12, 120, 10, {
		//
				{ "_", "R", "I" },
				////////
				{ "O", "F", "C" },
				////////
				{ "S", "T", "E" }
		//
				}),
		//
		Riddle::create("it's on the top", "cap tip lid", 13, 121, 1, {
		//
				{ "I", "D", "P" },
				////////
				{ "L", "A", "I" },
				////////
				{ "P", "T", "C" }
		//
				}),
		//
		Riddle::create("insects", "ant flea", 13, 122, 2, {
		//
				{ "L", "F", "A" },
				////////
				{ "E", "N", "_" },
				////////
				{ "T", "A", "_" }
		//
				}),
		//
		Riddle::create("four-wheeled transportation", "bus car van", 13, 123, 3,
				{
				//
						{ "R", "C", "B" },
						////////
						{ "A", "U", "S" },
						////////
						{ "V", "A", "N" }
				//
				}),
		//
		Riddle::create("up___", "town fair", 13, 124, 4, {
		//
				{ "_", "N", "W" },
				////////
				{ "W", "T", "A" },
				////////
				{ "O", "R", "D" }
		//
				}),
		//
		Riddle::create("honest", "frank fair", 13, 125, 5, {
		//
				{ "F", "I", "R" },
				////////
				{ "A", "A", "R" },
				////////
				{ "K", "N", "F" }
		//
				}),
		//
		Riddle::create("numbers", "six two one", 13, 126, 6, {
		//
				{ "O", "E", "O" },
				////////
				{ "N", "S", "W" },
				////////
				{ "I", "X", "T" }
		//
				}),
		//
		Riddle::create("to contain with your hand", "hold grip", 13, 127, 7, {
		//
				{ "O", "_", "G" },
				////////
				{ "H", "L", "R" },
				////////
				{ "D", "I", "P" }
		//
				}),
		//
		Riddle::create("reach out and \"touch\" someone", "pat hit tap", 13,
				128, 8, {
				//
						{ "T", "A", "T" },
						////////
						{ "P", "A", "P" },
						////////
						{ "H", "I", "T" }
				//
				}),
		//
		Riddle::create("common pets", "fish cat", 13, 129, 9, {
		//
				{ "_", "_", "C" },
				////////
				{ "T", "A", "F" },
				////////
				{ "H", "S", "I" }
		//
				}),
		//
		Riddle::create("in a \"group\"", "band party", 13, 130, 10, {
		//
				{ "B", "N", "Y" },
				////////
				{ "D", "A", "T" },
				////////
				{ "P", "A", "R" }
		//
				}),
		//
		Riddle::create("hold down", "press bind", 14, 131, 1, {
		//
				{ "S", "R", "P" },
				////////
				{ "S", "E", "I" },
				////////
				{ "D", "N", "B" }
		//
				}),
		//
		Riddle::create("go that way", "aft left up", 14, 132, 2, {
		//
				{ "F", "E", "L" },
				////////
				{ "T", "T", "A" },
				////////
				{ "U", "P", "F" }
		//
				}),
		//
		Riddle::create("not good", "poor lousy", 14, 133, 3, {
		//
				{ "O", "S", "Y" },
				////////
				{ "R", "O", "U" },
				////////
				{ "L", "O", "P" }
		//
				}),
		//
		Riddle::create("winter", "cold snow", 14, 134, 4, {
		//
				{ "O", "W", "S" },
				////////
				{ "D", "N", "C" },
				////////
				{ "L", "O", "_" }
		//
				}),
		//
		Riddle::create("\"solo\"", "stag lone", 14, 135, 5, {
		//
				{ "G", "N", "E" },
				////////
				{ "T", "A", "O" },
				////////
				{ "S", "L", "_" }
		//
				}),
		//
		Riddle::create("a dwelling", "pad hut den", 14, 136, 6, {
		//
				{ "D", "N", "T" },
				////////
				{ "A", "E", "U" },
				////////
				{ "D", "P", "H" }
		//
				}),
		//
		Riddle::create("it's connected", "internet", 14, 137, 7, {
		//
				{ "T", "N", "I" },
				////////
				{ "E", "R", "T" },
				////////
				{ "_", "N", "E" }
		//
				}),
		//
		Riddle::create("at sea!", "ship buoy", 14, 138, 8, {
		//
				{ "B", "S", "H" },
				////////
				{ "U", "P", "I" },
				////////
				{ "O", "Y", "_" }
		//
				}),
		//
		Riddle::create("above and around you", "sky sun air", 14, 139, 9, {
		//
				{ "K", "Y", "R" },
				////////
				{ "S", "N", "I" },
				////////
				{ "S", "U", "A" }
		//
				}),
		//
		Riddle::create("quickly", "swift fast", 14, 140, 10, {
		//
				{ "S", "T", "F" },
				////////
				{ "A", "T", "I" },
				////////
				{ "F", "S", "W" }
		//
				}),
		//
		Riddle::create("happens during a ball game", "hit goal block", 15, 141,
				1, {
				//
						{ "_", "_", "L", "K" },
						////////
						{ "_", "A", "C", "_" },
						////////
						{ "O", "O", "I", "B" },
						////////
						{ "G", "T", "L", "H" }
				//
				}),
		//
		Riddle::create("car parts", "door fender trunk", 15, 142, 2, {
		//
				{ "R", "K", "N", "U" },
				////////
				{ "_", "E", "R", "D" },
				////////
				{ "D", "F", "O", "T" },
				////////
				{ "N", "E", "R", "O" }
		//
				}),
		//
		Riddle::create("cutlery", "fork knife spoon", 15, 143, 3, {
		//
				{ "N", "K", "F", "O" },
				////////
				{ "F", "I", "S", "R" },
				////////
				{ "_", "E", "K", "P" },
				////////
				{ "_", "N", "O", "O" }
		//
				}),
		//
		Riddle::create("under___", "wear stand rated", 15, 144, 4, {
		//
				{ "T", "E", "D", "_" },
				////////
				{ "R", "A", "_", "D" },
				////////
				{ "E", "R", "S", "N" },
				////////
				{ "A", "W", "T", "A" }
		//
				}),
		//
		Riddle::create("in a bottle", "wine water ship", 15, 145, 5, {
		//
				{ "T", "E", "E", "I" },
				////////
				{ "A", "R", "N", "W" },
				////////
				{ "W", "P", "_", "S" },
				////////
				{ "_", "_", "I", "H" }
		//
				}),
		//
		Riddle::create("hard work", "tears blood sweat", 15, 146, 6, {
		//
				{ "W", "T", "A", "R" },
				////////
				{ "S", "E", "A", "S" },
				////////
				{ "L", "_", "E", "T" },
				////////
				{ "B", "O", "O", "D" }
		//
				}),
		//
		Riddle::create("medical professions", "physician surgeon", 15, 147, 7, {
		//
				{ "R", "U", "S", "C" },
				////////
				{ "G", "E", "I", "I" },
				////////
				{ "H", "S", "O", "A" },
				////////
				{ "Y", "P", "N", "N" }
		//
				}),
		//
		Riddle::create("telling time", "calendar sundial", 15, 148, 8, {
		//
				{ "_", "N", "U", "S" },
				////////
				{ "D", "I", "A", "L" },
				////////
				{ "A", "C", "N", "R" },
				////////
				{ "L", "E", "A", "D" }
		//
				}),
		//
		Riddle::create("it happens in the brain", "memory thinking", 15, 149, 9,
				{
				//
						{ "_", "N", "I", "K" },
						////////
						{ "G", "R", "I", "N" },
						////////
						{ "O", "E", "Y", "H" },
						////////
						{ "M", "_", "M", "T" }
				//
				}),
		//
		Riddle::create("it covers you", "insurance sheet", 15, 150, 10, {
		//
				{ "_", "E", "E", "T" },
				////////
				{ "H", "S", "U", "E" },
				////////
				{ "N", "S", "R", "C" },
				////////
				{ "_", "I", "N", "A" }
		//
				}),
		//
		Riddle::create("not home", "away gone astray", 16, 151, 1, {
		//
				{ "A", "S", "T", "_" },
				////////
				{ "Y", "R", "A", "_" },
				////////
				{ "O", "N", "A", "W" },
				////////
				{ "G", "Y", "E", "A" }
		//
				}),
		//
		Riddle::create("things that smoke", "fire pipe volcano", 16, 152, 2, {
		//
				{ "I", "P", "N", "_" },
				////////
				{ "E", "P", "A", "O" },
				////////
				{ "V", "R", "L", "C" },
				////////
				{ "E", "O", "I", "F" }
		//
				}),
		//
		Riddle::create("literary genres", "biography romance", 16, 153, 3, {
		//
				{ "R", "O", "M", "A" },
				////////
				{ "H", "Y", "B", "N" },
				////////
				{ "R", "P", "C", "I" },
				////////
				{ "A", "G", "O", "E" }
		//
				}),
		//
		Riddle::create("snack food", "crackers pretzels", 16, 154, 4, {
		//
				{ "Z", "E", "P", "S" },
				////////
				{ "T", "R", "L", "R" },
				////////
				{ "E", "R", "A", "C" },
				////////
				{ "S", "E", "K", "C" }
		//
				}),
		//
		Riddle::create("crustaceans", "lobster crab krill", 16, 155, 5, {
		//
				{ "K", "C", "B", "L" },
				////////
				{ "R", "R", "S", "O" },
				////////
				{ "I", "A", "B", "T" },
				////////
				{ "L", "L", "R", "E" }
		//
				}),
		//
		Riddle::create("found in a church", "priest hymn prayer", 16, 156, 6, {
		//
				{ "P", "R", "I", "N" },
				////////
				{ "P", "E", "H", "M" },
				////////
				{ "R", "E", "S", "Y" },
				////////
				{ "R", "A", "Y", "T" }
		//
				}),
		//
		Riddle::create("in the dairy section", "yogurt swiss cream", 16, 157, 7,
				{
				//
						{ "C", "R", "E", "A" },
						////////
						{ "S", "W", "T", "M" },
						////////
						{ "I", "S", "S", "R" },
						////////
						{ "Y", "O", "G", "U" }
				//
				}),
		//
		Riddle::create("halloween", "treat mask makeup", 16, 158, 8, {
		//
				{ "K", "_", "R", "T" },
				////////
				{ "S", "E", "M", "E" },
				////////
				{ "U", "A", "K", "A" },
				////////
				{ "P", "M", "A", "T" }
		//
				}),
		//
		Riddle::create("sports", "cricket rugby golf", 16, 159, 9, {
		//
				{ "R", "U", "E", "T" },
				////////
				{ "G", "I", "C", "K" },
				////////
				{ "B", "R", "O", "L" },
				////////
				{ "Y", "G", "C", "F" }
		//
				}),
		//
		Riddle::create("spanish-speaking countries", "cuba chile bolivia", 16,
				160, 10, {
				//
						{ "L", "I", "H", "C" },
						////////
						{ "E", "A", "C", "U" },
						////////
						{ "A", "I", "B", "O" },
						////////
						{ "V", "I", "L", "B" }
				//
				})
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
static vector<RiddlePacket*> vt_riddle_packets = {
//
		RiddlePacket::create("Mango", "packetscene/mango.png", 1),
		//
		RiddlePacket::create("Papaya", "packetscene/papaya.png", 2),
		//
		RiddlePacket::create("Sugar Cane", "packetscene/sugarcane.png", 3),
		//
		RiddlePacket::create("Asparagus", "packetscene/asparagus.png", 4),
		//
		RiddlePacket::create("Soursop", "packetscene/soursop.png", 5),
		//
		RiddlePacket::create("Brazil Nut", "packetscene/brazilnut.png", 6),
		//
		RiddlePacket::create("Chocolate Tree", "packetscene/chocolatetree.png",
				7),
		//
		RiddlePacket::create("Blueberry", "packetscene/blueberry.png", 8),
		//
		RiddlePacket::create("Orange", "packetscene/orange.png", 9),
		//
		RiddlePacket::create("Cherries", "packetscene/cherries.png", 10),
		//
		RiddlePacket::create("Ladyfinger", "packetscene/ladyfinger.png", 11),
		//
		RiddlePacket::create("Ice Cream", "packetscene/icecream.png", 12),
		//
		RiddlePacket::create("Pizza", "packetscene/pizza.png", 13),
		//
		RiddlePacket::create("Sandwich", "packetscene/sandwich.png", 14),
		//
		RiddlePacket::create("Nut", "packetscene/nut.png", 15),
		//
		RiddlePacket::create("Olive", "packetscene/olive.png", 16),
		//
		RiddlePacket::create("Peach", "packetscene/peach.png", 17),
		//
		RiddlePacket::create("Peanut", "packetscene/peanut.png", 18),
		//
		RiddlePacket::create("Potato", "packetscene/potato.png", 19),
		//
		RiddlePacket::create("Onion", "packetscene/onion.png", 20),
		//
		RiddlePacket::create("Apple", "packetscene/apple.png", 21),
		//
		RiddlePacket::create("Soy", "packetscene/soy.png", 22),
		//
		RiddlePacket::create("Raspberry", "packetscene/raspberry.png", 23),
		//
		RiddlePacket::create("Radish", "packetscene/radish.png", 24),
		//
		RiddlePacket::create("Pumpkin", "packetscene/pumpkin.png", 25),
		//
		RiddlePacket::create("Lettuce", "packetscene/lettuce.png", 26),
		//
		RiddlePacket::create("Pomegranat", "packetscene/pomegranat.png", 27),
		//
		RiddlePacket::create("Plum", "packetscene/plum.png", 28),
		//
		RiddlePacket::create("Cucumber", "packetscene/cucumber.png", 29),
		//
		RiddlePacket::create("Corn", "packetscene/corn.png", 30),
		//
		RiddlePacket::create("Coconut", "packetscene/coconut.png", 31),
		//
		RiddlePacket::create("Lemon", "packetscene/lemon.png", 32),
		//
		RiddlePacket::create("Chili", "packetscene/chili.png", 33),
		//
		RiddlePacket::create("Eggplant", "packetscene/eggplant.png", 34),
		//
		RiddlePacket::create("Watermelon", "packetscene/watermelon.png", 35),
		//
		RiddlePacket::create("Tomato", "packetscene/tomato.png", 36),
		//
		RiddlePacket::create("Deciduous", "packetscene/deciduous.png", 37),
		//
		RiddlePacket::create("Banana", "packetscene/banana.png", 38),
		//
		RiddlePacket::create("Avocado", "packetscene/avocado.png", 39),
		//
		RiddlePacket::create("Beet", "packetscene/beet.png", 40),
		//
		RiddlePacket::create("Broccoli", "packetscene/broccoli.png", 41),
		//
		RiddlePacket::create("Cabbage", "packetscene/cabbage.png", 42),
		//
		RiddlePacket::create("Capsicum", "packetscene/capsicum.png", 43),
		//
		RiddlePacket::create("Carrot", "packetscene/carrot.png", 44),
		//
		RiddlePacket::create("Leek", "packetscene/leek.png", 45),
		//
		RiddlePacket::create("Kiwi", "packetscene/kiwi.png", 46),
		//
		RiddlePacket::create("Hazelnut", "packetscene/hazelnut.png", 47),
		//
		RiddlePacket::create("Grapes", "packetscene/grapes.png", 48),
		//
		RiddlePacket::create("Garlic", "packetscene/garlic.png", 49)
//
		};
#endif
