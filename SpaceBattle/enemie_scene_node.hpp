#ifndef _ENEMIE_SCENE_NODE_HPP
#define _ENEMIE_SCENE_NODE_HPP

#include "stdafx.hpp"
#include "game_object_scene_node.hpp"
#include "enemie_scene_node_manager.hpp"
#include "rocket_mamager.hpp"

class cGameNode;
class cEnemieNodeManager;
class cRocketManager;

class cEnemieNode
	: public cGameNode
{
// Fields //
private:

	const cEnemieNodeManager * m_pManager;

// Methods //
	cEnemieNode (); // Defaul constructor

	cEnemieNode ( const cEnemieNode & _en );

public:

	cEnemieNode ( irr::scene::ISceneManager * _pSceneManager, irr::c8 * _meshPath,
			cEnemieNodeManager * _pEnemieManager,
			irr::core::vector3df _position = irr::core::vector3df ( 0, 0, 0 ),
			irr::core::vector3df _rotation = irr::core::vector3df ( 0, 0, 0 ), 
			irr::core::vector3df _scale = irr::core::vector3df ( 1.0f, 1.0f, 1.0f ),
			irr::scene::ISceneNode * _pParent = nullptr,
			irr::s32 _id = -1 );


	const cEnemieNodeManager * getEnemieManager () const;

	void launch ( cRocketManager * _pRocketManager, irr::video::IVideoDriver * _pVideoDriver );

};

inline const cEnemieNodeManager * cEnemieNode::getEnemieManager () const
{
	return m_pManager;
}

#endif // _ENEMIE_SCENE_NODE_HPP