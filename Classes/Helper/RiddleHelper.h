#ifndef __RiddleHelper__
#define __RiddleHelper__

#include "cocos2d.h"
#include "../Constants/RiddleResource.h"
#include "../Constants/Constants.h"
#include "../Helper/CppUtils.h"
#include "../Trading/FirebaseHandler/FirebaseHandler.h"

USING_NS_CC;
using namespace std;
class RiddleHelper {
public:
	RiddleHelper() = delete; //Compiler will not compile constructor -> for optimizing point

	static int getLevelNumberInThePacket(int packetId);
	static bool isPacketActive(int packetId);
};

#endif
