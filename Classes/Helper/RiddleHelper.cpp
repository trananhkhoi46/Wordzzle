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
void RiddleHelper::receiveHints(int numberOfHint) {
	if (numberOfHint == -100) {
		UserDefault::getInstance()->setIntegerForKey(HINT_NUMBER, numberOfHint);
		//All hints for passing a package
	} else {
		UserDefault::getInstance()->setIntegerForKey(HINT_NUMBER,
				numberOfHint + UserDefault::getInstance()->getIntegerForKey(
				HINT_NUMBER, HINT_NUMBER_DEFAULT_VALUE));
	}
}

bool RiddleHelper::consumeAHint() {
	int hintNumber = UserDefault::getInstance()->getIntegerForKey(
	HINT_NUMBER, HINT_NUMBER_DEFAULT_VALUE);
	if (hintNumber == -100) {
		return true;
	} else {
		if (hintNumber <= 0) {
			return false;
		} else {
			UserDefault::getInstance()->setIntegerForKey(HINT_NUMBER,
					hintNumber - 1);
		}
	}
	return true;
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

vector<Riddle*> RiddleHelper::getRiddlesOfThePacket(int packetId) {
	vector<Riddle*> result;
	for (Riddle* riddle : vt_riddles) {
		if (riddle->riddle_packet_id == packetId) {
			result.push_back(riddle);
		}
	}
	return result;
}
