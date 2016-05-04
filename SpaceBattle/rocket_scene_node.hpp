#ifndef _ROCKET_SCENE_NODE_HPP
#define _ROCKET_SCENE_NODE_HPP

#include "stdafx.hpp"
#include "game_object_scene_node.hpp"
#include "fighet_scene_node.hpp"
#include "enemie_scene_node.hpp"
#include "enemie_scene_node_manager.hpp"
#include "rocket_mamager.hpp"

class cEnemieNode;
class cEnemieNodeManager;

class cRocketNode 
	: public cGameNode 
{
// Fields //
private:

	bool m_isLaunched;

	std::vector < irr::scene::ISceneNodeAnimatorCollisionResponse * > m_vpAnimators;

// Methods //
private:
	cRocketNode ();

	cRocketNode ( const cRocketNode * _pRn );

public:
	cRocketNode ( irr::scene::ISceneManager * _pSceneManager
			, irr::c8 * _meshPath
			, irr::video::IVideoDriver * _pVideoDriver
			, irr::core::vector3df _position = irr::core::vector3df ( 0, 0, 0 )
			, irr::core::vector3df _rotation = irr::core::vector3df ( 0, 0, 0 )
			, irr::core::vector3df _scale = irr::core::vector3df ( 1.0f, 1.0f, 1.0f )
			, irr::scene::ISceneNode * _pParent = nullptr
			, irr::s32 _id = -1 );

	irr::scene::ISceneNodeAnimatorCollisionResponse * calculateAnimator ( cEnemieNodeManager * _pEnemies
		, irr::scene::ISceneManager * _pManager ); // calculating animator for all enemies with one meta selector

	irr::scene::ISceneNodeAnimatorCollisionResponse * calculateAnimator ( cEnemieNode * _pEnemie
		, irr::scene::ISceneManager * _pManager ); // Creating animator for the enemie

	irr::scene::ISceneNodeAnimatorCollisionResponse * calculateAnimator ( cFighterSceneNode * _pFighter
		, irr::scene::ISceneManager * _pManager ); // Creating animator for the fighter

	irr::scene::IMetaTriangleSelector * setSelector ( cEnemieNodeManager * _pEnemies
		, irr::scene::ISceneManager * _pManager ); // Creating meta selector for enemies

	void addAnimator ( irr::scene::ISceneNodeAnimatorCollisionResponse * _pAnimator );

	std::vector < irr::scene::ISceneNodeAnimatorCollisionResponse * > * getAnimators ();

	void cleareAnimators ();

	bool isLaunched ();

	void launch ();

	void reload ();
};

inline bool cRocketNode::isLaunched ()
{
	return m_isLaunched;
}

inline void cRocketNode::reload ()
{
	m_isLaunched = false;
}

inline void cRocketNode::launch ()
{
	m_isLaunched = true;
} 

inline void cRocketNode::addAnimator ( irr::scene::ISceneNodeAnimatorCollisionResponse * _pAnimator )
{
	m_vpAnimators.push_back ( _pAnimator );
}

inline std::vector < irr::scene::ISceneNodeAnimatorCollisionResponse * > * cRocketNode::getAnimators ()
{
	return & m_vpAnimators;
}
#endif // _ROCKET_SCENE_NODE_HPP