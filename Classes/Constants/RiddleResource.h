#ifndef _RIDDLE_RESOURCE_H_
#define _RIDDLE_RESOURCE_H_

#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

class RiddlePacket {
public:
	inline static RiddlePacket* create(string riddle_packet_name,
			string riddle_packet_icon_image, string riddle_packet_holder_image,
			int riddle_packet_id) {
		RiddlePacket* result = new RiddlePacket();
		result->riddle_packet_name = riddle_packet_name;
		result->riddle_packet_icon_image = riddle_packet_icon_image;
		result->riddle_packet_holder_image = riddle_packet_holder_image;
		result->riddle_packet_id = riddle_packet_id;
		return result;
	}
	string riddle_packet_icon_image;
	string riddle_packet_name;
	string riddle_packet_holder_image;
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
		RiddlePacket::create("Mango 1", "packetscene/mango.png",
				"packetscene/mango_holder.png", 1),
		//
		RiddlePacket::create("Mango 2", "packetscene/mango.png",
				"packetscene/mango_holder.png", 2),
		//
		RiddlePacket::create("Mango 3", "packetscene/mango.png",
				"packetscene/mango_holder.png", 3),
		//
		RiddlePacket::create("Mango 4", "packetscene/mango.png",
				"packetscene/mango_holder.png", 4),
		//
		RiddlePacket::create("Mango 5", "packetscene/mango.png",
				"packetscene/mango_holder.png", 5),
		//
		RiddlePacket::create("Mango 6", "packetscene/mango.png",
				"packetscene/mango_holder.png", 6),
		//
		RiddlePacket::create("Mango 7", "packetscene/mango.png",
				"packetscene/mango_holder.png", 7)
//
		};
#endif
