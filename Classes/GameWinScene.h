#ifndef __GAME_WIN_SCENE_H__
#define __GAME_WIN_SCENE_H__

#include "BaseScene.h"

class GameWinScene: public BaseScene{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene(Riddle* riddle);
	CREATE_FUNC(GameWinScene)
};



#endif
