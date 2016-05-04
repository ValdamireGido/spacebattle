#ifndef _MAIN_H_
#define _MAIN_H_

#define GAME_LEVEL_1_ENEMIES_COUNT 8
#define GAME_LEVEL_2_ENEMIES_COUNT 16
#define GAME_LEVEL_3_ENEMIES_COUNT 24
#define GAME_LEVEL_4_ENEMIES_COUNT 32

static irr::f32 leftBorder = 0;
static irr::f32 rightBorder = 0;
static irr::f32 upBorder = UP_BORDER;
static irr::f32 downBorder = DOWN_BORDER;

class cRocketManager;
class cEnemieNodeManager;
class sApplicationContext;
class MyEventReceiver;

int collisionChek(cRocketManager * _pRockets, bool isGood = true);

void setEnemiesFleeet(std::vector < irr::scene::ISceneNodeAnimator * > * _pAnimators,
					  cEnemieNodeManager * _pEnemieManager, 
					  irr::scene::ISceneManager * _pSceneMager,
					  sApplicationContext * _pContext);

struct Global
{
	static MyEventReceiver* myEventReceiver;
	static irr::video::IVideoDriver* spVideoDriver;
};

#endif // _MAIN_H_