#ifndef __RiddleHelper__
#define __RiddleHelper__

#include "cocos2d.h"
#include "../Constants/RiddleResource.h"
#include "../Constants/Constants.h"
#include "../Helper/CppUtils.h"

USING_NS_CC;
using namespace std;
class RiddleHelper {
public:
	RiddleHelper() = delete; //Compiler will not compile constructor -> for optimizing point

	static int getLevelNumberInThePacket(int packetId);
	static bool isPacketActive(int packetId);
	static bool isRiddleActive(int riddleId);
	static vector<Riddle*> getRiddlesOfThePacket(int packetId);
	static Riddle* getRiddleById(int riddleId);
	static Riddle* getNextLevelRiddleAndUnlockIfNeeded(Riddle* currentRiddle);
	static void receiveHints(int numberOfHint);
	static bool consumeAHint();
};

#endif
