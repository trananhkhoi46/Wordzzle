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
	int activePacket = UserDefault::getInstance()->getIntegerForKey(
	ACTIVE_PACKET, ACTIVE_PACKET_DEFAULT_VALUE);
	return activePacket >= packetId;
}

Riddle* RiddleHelper::getNextLevelRiddleAndUnlockIfNeeded(
		Riddle* currentRiddle) {
	if(getRiddleById(currentRiddle->riddle_packet_id + 1) == nullptr){
		return nullptr;
	}

	int maxUnlockedRiddleId = UserDefault::getInstance()->getIntegerForKey(
	ACTIVE_RIDDLE, ACTIVE_RIDDLE_DEFAULT_VALUE);
	int maxUnlockedRiddlePacketId =
			UserDefault::getInstance()->getIntegerForKey(
			ACTIVE_PACKET, ACTIVE_PACKET_DEFAULT_VALUE);

	//Increase active packet if riddle level = numberOfLevelInThePacket
	if (currentRiddle->riddle_level
			>= getLevelNumberInThePacket(currentRiddle->riddle_packet_id)
			&& currentRiddle->riddle_packet_id + 1
					> maxUnlockedRiddlePacketId) {
		UserDefault::getInstance()->setIntegerForKey(ACTIVE_PACKET,
				currentRiddle->riddle_packet_id + 1);

		//Passed a packet, if user is in full hint mode, disable it (fullhintmode = mode that has enough hint for passing a packet)
		int hintNumber = UserDefault::getInstance()->getIntegerForKey(
		HINT_NUMBER, HINT_NUMBER_DEFAULT_VALUE);
		if (hintNumber == -100) {
			UserDefault::getInstance()->setIntegerForKey(
			HINT_NUMBER, 0);
		}
	}

	//Increase active riddle
	if (currentRiddle->riddle_id + 1 > maxUnlockedRiddleId) {
		UserDefault::getInstance()->setIntegerForKey(ACTIVE_RIDDLE,
				currentRiddle->riddle_id + 1);
	}

	return getRiddleById(currentRiddle->riddle_id + 1);
}

Riddle* RiddleHelper::getRiddleById(int id) {
	for (Riddle* riddle : vt_riddles) {
		if (riddle->riddle_id == id) {
			return riddle;
		}
	}
	return nullptr;
}
RiddlePacket* RiddleHelper::getPacketById(int id) {
	for (RiddlePacket* packet : vt_riddle_packets) {
		if (packet->riddle_packet_id == id) {
			return packet;
		}
	}
	return nullptr;
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
	int activeRiddle = UserDefault::getInstance()->getIntegerForKey(
	ACTIVE_RIDDLE, ACTIVE_RIDDLE_DEFAULT_VALUE);
	return activeRiddle >= riddleId;
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
