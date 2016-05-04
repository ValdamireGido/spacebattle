#include "stdafx.hpp"

#include "enemie_scene_node.hpp"
#include "rocket_mamager.hpp"
#include "rocket_scene_node.hpp"

#include <algorithm>

cRocketManager::cRocketManager ( irr::scene::ISceneManager * _pSceneManager, irr::IrrlichtDevice * _pDevice, 
		irr::c8 * _meshPath, irr::scene::IMeshSceneNode * _pWorldBorder, bool _isGood )
	: m_arraySize ( UNIVERSAL_NUMBER )
	, m_nUsed ( 0 )
	, m_nRocketsLaunched ( 0 )
	, m_pManager ( _pSceneManager )
	, m_pDevice ( _pDevice )
{
	setArrayToZero ();
	if ( _isGood )
	{
		
		for ( int i = 0; i < m_arraySize; i++ )
		{
			m_aRockets[i] = new cRocketNode ( m_pManager, _meshPath, m_pDevice->getVideoDriver (), 
				irr::core::vector3df ( 0, UP_BORDER + 100, 0 ) );

			m_aRockets[i]->reload();
		}
	}
	else 
	{
		for ( int i = 0; i < m_arraySize; i++ )
		{
			m_aRockets[i] = new cRocketNode ( m_pManager, _meshPath, m_pDevice->getVideoDriver (), 
				irr::core::vector3df ( 0, DOWN_BORDER - 500, 0 ) );

			m_aRockets[i]->getMeshSceneNode ()
				->setRotation ( m_aRockets[i]->getMeshSceneNode ()->getRotation () 
				+ irr::core::vector3df ( 180, 0, 0 ) );

			m_aRockets[i]->reload();
		}
	}
}

cRocketManager::~cRocketManager ()
{
	for ( int i = 0; i < m_arraySize; i++ )
		m_aRockets[i]->drop ();

	m_nUsed = m_aRockets.size ();

	setArrayToZero ();
}

void cRocketManager::setArrayToZero ()
{
	m_aRockets.resize(m_arraySize);
}

void cRocketManager::addAnimatorsToRockets ( cEnemieNodeManager * _pEnemieManager
	, irr:: scene::IMeshSceneNode * pBorder )
{
	using namespace irr;

	int size = _pEnemieManager->getVectorSize();
	scene::ISceneNodeAnimatorCollisionResponse * pAnimator;

	irr::scene::ITriangleSelector * pSelector = m_pManager->createOctreeTriangleSelector ( pBorder->getMesh(),
		pBorder );

	for ( int i = 0; i < m_arraySize; i++ )
	{
		pAnimator = m_pManager->createCollisionResponseAnimator ( pSelector, m_aRockets[0]->getMeshSceneNode()
			, irr::core::vector3df ( 5, 15, 5 ) // Ellipsoid
			, GRAVITY // Gravity
			);

		m_aRockets[i]->getMeshSceneNode ()->addAnimator ( pAnimator );
		m_aRockets[i]->addAnimator ( pAnimator );

		for ( int j = 0; j < size; j++ )
		{
			pAnimator->drop ();
			
			pAnimator = m_aRockets[i]->calculateAnimator ( _pEnemieManager->getEnemie ( j ), m_pManager );

			m_aRockets[i]->getMeshSceneNode ()->addAnimator ( pAnimator );
			m_aRockets[i]->addAnimator ( pAnimator );
		}

		pAnimator->drop ();
	}
}

void cRocketManager::addAnimatorsToRockets ( cFighterSceneNode * _pFighter
	, irr::scene::IMeshSceneNode * pBorder )
{
	using namespace irr;

	scene::ISceneNodeAnimatorCollisionResponse * pAnimator;

	irr::scene::ITriangleSelector * pSelector = m_pManager->createOctreeTriangleSelector ( pBorder->getMesh(),
		pBorder );

	for ( int i = 0; i < m_arraySize; i++ )
	{
		pAnimator = m_pManager->createCollisionResponseAnimator ( pSelector, m_aRockets[0]->getMeshSceneNode()
			, irr::core::vector3df ( 5, 15, 5 ) // Ellipsoid
			, ENEMIE_GRAVITY // Gravity
			);

		m_aRockets[i]->getMeshSceneNode ()->addAnimator ( pAnimator );
		m_aRockets[i]->addAnimator ( pAnimator );

		pAnimator->drop ();
			
		pAnimator = m_aRockets[i]->calculateAnimator ( _pFighter, m_pManager );

		m_aRockets[i]->getMeshSceneNode ()->addAnimator ( pAnimator );
		m_aRockets[i]->addAnimator ( pAnimator );

		pAnimator->drop ();
	}
}

void cRocketManager::cleareRocketsAnimators ()
{
	int size = m_aRockets.size();

	for ( int i = 0; i < size; i++ )
		m_aRockets[i]->cleareAnimators ();
}

void cRocketManager::reload ()
{
	m_nUsed = 0;

	for ( int i = 0; i < m_arraySize; i++ )
		m_aRockets[i]->reload();
}
