#include "stdafx.hpp"

#include "enemie_scene_node.hpp"
#include "rocket_mamager.hpp"

using namespace irr;

cEnemieNode::cEnemieNode ( scene::ISceneManager * _pSceneManager, c8 * _meshPath,
			cEnemieNodeManager * _pEnemieManager,
			irr::core::vector3df _position,
			irr::core::vector3df _rotation, 
			irr::core::vector3df _scale,
			irr::scene::ISceneNode * _pParent,
			irr::s32 _id )
	: cGameNode ( _pSceneManager, _meshPath, _position, _rotation, _scale, _pParent, _id )
{
	m_pManager = _pEnemieManager;
}

void cEnemieNode::launch ( cRocketManager * _pRocketManager, irr::video::IVideoDriver * _pVideoDriver )
{
	int count = _pRocketManager->getUsed ();
	
	if ( count == _pRocketManager->getArraySize () )
	{
		_pRocketManager->reload ();
		count = _pRocketManager->getUsed ();
	}

	while ( count < _pRocketManager->getArraySize () )
	{
		if ( ! _pRocketManager->getRockets ()->at ( count )->isLaunched () )
		{
			_pRocketManager->getRockets ()->at ( count )->launch ();
			_pRocketManager->increaseUsed ();

			_pRocketManager->getRockets ()->at ( count )->getMeshSceneNode ()
				->setPosition ( getMeshSceneNode ()->getPosition () );

			std::vector< irr::scene::ISceneNodeAnimatorCollisionResponse * >::iterator it = _pRocketManager->getRockets ()->at ( count )->getAnimators ()->begin ();

			while ( it != _pRocketManager->getRockets ()->at ( count )->getAnimators ()->end () )
			{
				( * it  )->setGravity ( ENEMIE_GRAVITY );
				it++;
			}

			break;
		}
		else 
		{
			++count;

			if ( count == _pRocketManager->getArraySize () )
				_pRocketManager->reload ();
		}
	}
}