#include "RiddleHelper.h"

int RiddleHelper::getLevelNumberInThePacket(int packetId) {
	int number = 0;
	for (Riddle* riddle : vt_riddles) {
		if (riddle->riddle_packet_id == packetId) {
			number++;
		}
	}
	return number;
}

bool RiddleHelper::isPacketActive(int packetId) {
	string activePacketString = UserDefault::getInstance()->getStringForKey(
	ACTIVE_PACKET, ACTIVE_PACKET_DEFAULT_VALUE);
	vector < string > splitString = CppUtils::splitStringByDelim(
			activePacketString, ',');
	for (string record : splitString) {
		if (CppUtils::stringToDouble(record) == packetId) {
			return true;
		}
	}

	return false;
}

bool RiddleHelper::isRiddleActive(int riddleId) {
	string activeRiddleString = UserDefault::getInstance()->getStringForKey(
	ACTIVE_RIDDLE, ACTIVE_RIDDLE_DEFAULT_VALUE);
	vector < string > splitString = CppUtils::splitStringByDelim(
			activeRiddleString, ',');
	for (string record : splitString) {
		if (CppUtils::stringToDouble(record) == riddleId) {
			return true;
		}
	}

	return false;
}

vector<Riddle*> RiddleHelper::getRiddlesOfThePacket(int packetId){
	vector<Riddle*> result;
	for(Riddle* riddle: vt_riddles){
		if(riddle->riddle_packet_id == packetId){
			result.push_back(riddle);
		}
	}
	return result;
}
