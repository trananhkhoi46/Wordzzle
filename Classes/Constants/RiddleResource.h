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
				{ "_", "K", "U" },
				////////
				{ "A", "T", "M" },
				////////
				{ "_", "U", "Q" }
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
				{ "E", "R", "_" }
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
