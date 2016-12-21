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
			vector<vector<char>> riddle_answer_matrix) {
		Riddle* result = new Riddle();
		result->riddle_hint = riddle_hint;
		result->riddle_answer = riddle_answer;
		result->riddle_packet_id = riddle_packet_id;
		result->riddle_id = riddle_id;
		result->riddle_level = riddle_level;
		result->riddle_answer_matrix = riddle_answer_matrix;
		return result;
	}

	vector<vector<char>> riddle_answer_matrix;
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
static vector<Riddle*> vt_riddles = {
//
		Riddle::create("animal", "cat", 1, 1, 1, {
		//
				{ 'T', '_' },
				////////
				{ 'C', 'A' }
		//
				}),
//
		Riddle::create("like fire", "hot", 1, 2, 2, {
		//
				{ 'H', 'T' },
				////////
				{ 'O', '_' }
		//
				}),
//
		Riddle::create("eaten with bacon", "egg", 1, 3, 3, {
		//
				{ 'E', 'G' },
				////////
				{ 'G', '_' }
		//
				}),
//
		Riddle::create("eaten with bacon", "egg", 1, 4, 4, {
		//
				{ 'E', 'G' },
				////////
				{ 'G', '_' }
		//
				}),
		//
		Riddle::create("eaten with bacon", "egg", 1, 5, 5, {
		//
				{ 'E', 'G' },
				////////
				{ 'G', '_' }
		//
				}),
		//
		Riddle::create("eaten with bacon", "egg", 1, 6, 6, {
		//
				{ 'E', 'G' },
				////////
				{ 'G', '_' }
		//
				}),
//
		Riddle::create("eaten with bacon", "egg", 1, 7, 7, {
		//
				{ 'E', 'G' },
				////////
				{ 'G', '_' }
		//
				}),
		//
		Riddle::create("eaten with bacon", "egg", 1, 8, 8, {
		//
				{ 'E', 'G' },
				////////
				{ 'G', '_' }
		//
				}),
		//
		Riddle::create("eaten with bacon", "egg", 1, 9, 9, {
		//
				{ 'E', 'G' },
				////////
				{ 'G', '_' }
		//
				}),
		//
		Riddle::create("eaten with bacon", "egg", 1, 10, 10, {
		//
				{ 'E', 'G' },
				////////
				{ 'G', '_' }
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
