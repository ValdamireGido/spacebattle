#ifndef _FIGHTER_SCENE_NODE
#define _FIGHTER_SCENE_NODE

#include "stdafx.hpp"
#include "game_object_scene_node.hpp"
#include "rocket_scene_node.hpp"
#include "rocket_mamager.hpp"

class cRocketManager;

class cFighterSceneNode
	: public cGameNode
{
// Fields //
private:
	float m_lives;
	float m_speed;
	int m_nRocketsLauched;
	
// Methods //
	cFighterSceneNode (); // Dafault constructor

	cFighterSceneNode ( const cFighterSceneNode & _fcn );

public:
	cFighterSceneNode ( irr::scene::ISceneManager * _pSceneManager, irr::c8 * _meshPath,
			float _lives = 3, float _speed = MOVEMENT_SPEED,
			irr::core::vector3df _position = irr::core::vector3df ( 0, 0, 0 ),
			irr::core::vector3df _rotation = irr::core::vector3df ( 0, 0, 0 ), 
			irr::core::vector3df _scale = irr::core::vector3df ( 1.0f, 1.0f, 1.0f ),
			irr::scene::ISceneNode * _pParent = nullptr,
			irr::s32 _id = -1 );

	void setSpeed ( float _speed );

	float getSpeed ();

	void setLives ( float _lives );

	float getLives ();

	int getNRocketsLaunched ();

	void reloadNRocketsLaunched ();

	void launch ( cRocketManager * _pRocket, irr::video::IVideoDriver * _pVideoDriver );
};

inline void cFighterSceneNode::setSpeed ( float _speed )
{
	m_speed = _speed;
}

inline float cFighterSceneNode::getSpeed ()
{
	return m_speed;
}

inline void cFighterSceneNode::setLives ( float _lives )
{
	m_lives	= _lives;
}

inline float cFighterSceneNode::getLives ()
{
	return m_lives;
}

inline int cFighterSceneNode::getNRocketsLaunched ()
{
	return m_nRocketsLauched;
}

inline void cFighterSceneNode::reloadNRocketsLaunched ()
{
	m_nRocketsLauched = 0;
}

#endif //_FIGHTER_SCENE_NODE