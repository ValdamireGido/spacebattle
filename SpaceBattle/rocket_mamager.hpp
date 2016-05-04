#ifndef _ROCKET_MANAGER_HPP
#define _ROCKET_MANAGER_HPP

#define UNIVERSAL_NUMBER 21
#define GRAVITY irr::core::vector3df ( 0, 0.3f, 0 )
#define ENEMIE_GRAVITY irr::core::vector3df ( 0, -0.3f, 0 )
#define NO_GRAVITY irr::core::vector3df ( 0, 0, 0 )

#include "stdafx.hpp"
#include "rocket_scene_node.hpp"
#include "enemie_scene_node_manager.hpp"
#include "enemie_scene_node.hpp"
#include "fighet_scene_node.hpp"

#include <vector>

class cRocketNode;
class cEnemieNode;
class cEnemieNodeManager;
class cFighterSceneNode;

class cRocketManager
{
// Fields //
private:

	const int m_arraySize;
	int m_nRocketsLaunched;
	int m_nUsed;

	std::vector < cRocketNode * > m_aRockets;

	irr::scene::ISceneManager * m_pManager;
	irr::IrrlichtDevice * m_pDevice;

// Methods //
private:

	cRocketManager (); // Default constructor

	cRocketManager ( const cRocketManager &  _rocketManager );

public:
	cRocketManager ( irr::scene::ISceneManager * _pSceneManager, irr::IrrlichtDevice * _pDevice, 
		irr::c8 * _meshPath, irr::scene::IMeshSceneNode * _pWorldBorder, bool _isGood = true );
	
	~cRocketManager ();

	int getArraySize () const;

	int getUsed () const;

	void setUsed ( int _nUsed );

	irr::scene::ISceneNodeAnimatorCollisionResponse * calculateAnimator ( cEnemieNode * _pEnemie );

	void addAnimatorsToRockets ( cEnemieNodeManager *_pEnemieManager, irr::scene::IMeshSceneNode * pBorder  );

	void addAnimatorsToRockets ( cFighterSceneNode *_pFighter, irr::scene::IMeshSceneNode * pBorder  );

	void cleareRocketsAnimators ();

	std::vector < cRocketNode * > * getRockets ();

	void setArrayToZero ();

	void increaseUsed ();

	void reload ();
};

inline int cRocketManager::getArraySize () const
{
	return m_arraySize; 
}

inline int cRocketManager::getUsed () const
{
	return m_nUsed;
}

inline std::vector < cRocketNode * > * cRocketManager::getRockets ()
{
	return & m_aRockets;
}

inline void cRocketManager::increaseUsed ()
{
	++m_nUsed;
	++m_nRocketsLaunched;
}

inline void cRocketManager::setUsed ( int _nUsed )
{
	m_nUsed = _nUsed;
}

#endif // _ROCKET_MANAGER_HPP