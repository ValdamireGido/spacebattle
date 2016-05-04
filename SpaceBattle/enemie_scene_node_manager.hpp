#ifndef _ENEMIE_SCENE_NODE_MANAGER_HPP
#define _ENEMIE_SCENE_NODE_MANAGER_HPP

#include "stdafx.hpp"
#include "enemie_scene_node.hpp"

class cEnemieNode;

class cEnemieNodeManager
{
// Fields //
private:

	int m_counter;
	int m_nEnemiesKilled;

	std::vector < std::string > m_vEnemiesTypesPath;
	std::vector < cEnemieNode * > m_vEnemies;

	irr::scene::ISceneManager * m_pSceneManager;
	irr::IrrlichtDevice * m_pDevice;

// Methods //
private:

	int count ();

public:

	cEnemieNodeManager ( irr::IrrlichtDevice * _pDevice, 
			irr::core::vector3df _position = irr::core::vector3df ( 0, 0, 0 ), 
			irr::core::vector3df _rotation = irr::core::vector3df ( 0, 0, 0 ), 
			irr::core::vector3df _scale = irr::core::vector3df ( 1.0f, 1.0f, 1.0f ), 
			irr::scene::ISceneNode * _pParent = nullptr, 
			irr::s32 _id = -1 );

	// Enemies vector
	cEnemieNode * getEnemie ( int _index ) const;

	std::vector < cEnemieNode * > * getVector ();

	int getVectorSize ();

	void push ( cEnemieNode * _pEnemieNode );

	cEnemieNode * newEnemie ();

	// Enemie_type vector
	void addEnemieType ( std::string _pathWithoutExtension ); // Example "..\\test\\filename[no extension]"

	std::string & getEnemieType ( int _index );

	void clearVectors ();

	void clearEnemiesVector ();

	irr::scene::ISceneManager * getSceneManager ();

	int getNEnemiesKilled ();

	void reloadNEnemiesKilled ();

	int increaseNEnemiesKilled ();

	~cEnemieNodeManager ();
};

inline void cEnemieNodeManager::addEnemieType ( std::string _pathWithoutExtension )
{
	m_vEnemiesTypesPath.push_back ( _pathWithoutExtension );
}

inline int cEnemieNodeManager::count ()
{
	return m_counter = m_vEnemies.size ();
}

inline irr::scene::ISceneManager * cEnemieNodeManager::getSceneManager ()
{
	return m_pSceneManager;
}

inline cEnemieNode * cEnemieNodeManager::getEnemie ( int _index ) const
{
	return m_vEnemies[_index];
}

inline std::vector < cEnemieNode * > * cEnemieNodeManager::getVector ()
{
	return & m_vEnemies;
}

inline int cEnemieNodeManager::getVectorSize ()
{
	count ();

	return m_counter;
}

inline void cEnemieNodeManager::push ( cEnemieNode * _pEnemieNode )
{
	m_vEnemies.push_back ( _pEnemieNode );
}

inline void cEnemieNodeManager::clearVectors ()
{
	m_vEnemies.clear ();
	m_vEnemiesTypesPath.clear  ();
}

inline std::string & cEnemieNodeManager::getEnemieType ( int _index )
{
	return m_vEnemiesTypesPath[ _index ];
}

inline int cEnemieNodeManager::getNEnemiesKilled ()
{
	return m_nEnemiesKilled;
}

inline void cEnemieNodeManager::reloadNEnemiesKilled ()
{
	m_nEnemiesKilled = 0;
}

inline int cEnemieNodeManager::increaseNEnemiesKilled ()
{
	return ++m_nEnemiesKilled;
}

#endif // _ENEMIE_SCENE_NODE_MANAGER_HPP