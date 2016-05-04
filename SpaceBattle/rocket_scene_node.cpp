#include "StdAfx.hpp"
#include "rocket_scene_node.hpp"

#include "stdafx.hpp"
#include "enemie_scene_node_manager.hpp"

#include <string>

using namespace irr;

cRocketNode::cRocketNode ( scene::ISceneManager * _pSceneManager, c8 * _meshPath,
			video::IVideoDriver * _pVideoDriver,
			core::vector3df _position,
			core::vector3df _rotation, 
			core::vector3df _scale,
			scene::ISceneNode * _pParent,
			s32 _id )
	: cGameNode ( _pSceneManager, _meshPath, _position, _rotation, _scale, _pParent, _id )
{
	c8 path [30];

	strcpy ( path, _meshPath );

	path [ strlen ( path ) - 2 ] = '\0';

	strcat ( path, ".tga" );

	setTexture ( path, _pVideoDriver );
}

irr::scene::ISceneNodeAnimatorCollisionResponse * cRocketNode::calculateAnimator ( cEnemieNodeManager * _pEnemies,
	irr::scene::ISceneManager * _pManager )
{
	using namespace irr;
	scene::IMetaTriangleSelector * pEnemiesSelector = _pManager->createMetaTriangleSelector ();

	int eSize = _pEnemies->getVectorSize ();

	for ( int i = 0; i < eSize; i++ )
		pEnemiesSelector->addTriangleSelector ( _pManager->createOctreeTriangleSelector ( 
			_pEnemies->getEnemie ( i )->getMesh ()
			, _pEnemies->getEnemie ( i )->getMeshSceneNode () ) );

	scene::ISceneNodeAnimatorCollisionResponse * pAnimator =_pManager->createCollisionResponseAnimator ( 
		pEnemiesSelector,
		getMeshSceneNode (),
		irr::core::vector3df ( 5, 15, 5 ) // Ellipsoid
		, GRAVITY
		);

	return pAnimator;
}

irr::scene::ISceneNodeAnimatorCollisionResponse * cRocketNode::calculateAnimator ( cEnemieNode * _pEnemie,
	irr::scene::ISceneManager * _pManager )
{
	using namespace irr;

 	scene::ITriangleSelector * pEnemieSelector = _pManager->createTriangleSelector ( _pEnemie->getMeshSceneNode () );

	scene::ISceneNodeAnimatorCollisionResponse * pAnimator =_pManager->createCollisionResponseAnimator ( 
		pEnemieSelector,
		getMeshSceneNode (),
		irr::core::vector3df ( 5, 15, 5 ) // Ellipsoid
		, GRAVITY
		);

	return pAnimator;
}

irr::scene::ISceneNodeAnimatorCollisionResponse * cRocketNode::calculateAnimator ( cFighterSceneNode * _pFighter, 
		irr::scene::ISceneManager * _pManager )
{
	using namespace irr;

	scene::ITriangleSelector * pFighterSelector = _pManager->createTriangleSelector (
		_pFighter->getMeshSceneNode () );

	scene::ISceneNodeAnimatorCollisionResponse * pAnimator = _pManager
		->createCollisionResponseAnimator ( pFighterSelector
			, getMeshSceneNode (), core::vector3df ( 5, 15, 5 )
			, ENEMIE_GRAVITY );

	return pAnimator;
}

void cRocketNode::cleareAnimators ()
{
	getMeshSceneNode()->removeAnimators();

	int size = m_vpAnimators.size ();

	for ( int i = 0; i < size; i++ )
		m_vpAnimators.pop_back();
}

irr::scene::IMetaTriangleSelector * cRocketNode::setSelector ( cEnemieNodeManager * _pEnemies,
	irr::scene::ISceneManager * _pManager )
{
	using namespace irr;

	scene::IMetaTriangleSelector * pEnemiesSelector = _pManager->createMetaTriangleSelector ();

	int eSize = 0;

	for ( int i = 0; i < eSize; i++ )
		pEnemiesSelector->addTriangleSelector ( _pManager->createTriangleSelector ( 
			_pEnemies->getEnemie ( i )->getMeshSceneNode () ) );

	return pEnemiesSelector;
}