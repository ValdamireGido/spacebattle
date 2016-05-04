#include "stdafx.hpp"
#include "fighet_scene_node.hpp"

#include "rocket_scene_node.hpp"

using namespace irr;

cFighterSceneNode::cFighterSceneNode ( irr::scene::ISceneManager * _pSceneManager, irr::c8 * _meshPath,
			float _lives, float _speed,
			irr::core::vector3df _position,
			irr::core::vector3df _rotation, 
			irr::core::vector3df _scale,
			irr::scene::ISceneNode * _pParent,
			irr::s32 _id )
		: cGameNode ( _pSceneManager, _meshPath, _position, _rotation, _scale, _pParent, _id ),
		m_lives ( _lives ), m_speed ( _speed ), m_nRocketsLauched ( 0 )
{}

void cFighterSceneNode::launch ( cRocketManager * _pRockets, video::IVideoDriver * _pVideoDriver )
{
	++m_nRocketsLauched;

	int count = _pRockets->getUsed ();

	while ( count < _pRockets->getArraySize () )
	{
		if ( ! _pRockets->getRockets ()->at ( count )->isLaunched () )
		{
			_pRockets->getRockets ()->at ( count )->launch();
			_pRockets->increaseUsed ();

			_pRockets->getRockets()->at ( count )->getMeshSceneNode()->setPosition ( 
				irr::core::vector3df ( getMeshSceneNode()->getPosition () ) );
		
			std::vector< irr::scene::ISceneNodeAnimatorCollisionResponse * >::iterator it = _pRockets->getRockets()->at ( count )->getAnimators()->begin();
			
			while ( it != _pRockets->getRockets()->at ( count )->getAnimators()->end() )
			{
				( * it )->setGravity ( GRAVITY );
				it++;
			}

			break;
		}
		else 
		{
			++count;

			if ( count == UNIVERSAL_NUMBER )
			{
				_pRockets->reload ();

				count = 0;
			}
		}
	}
}
