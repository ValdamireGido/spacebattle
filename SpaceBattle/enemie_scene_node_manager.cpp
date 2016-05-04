#include "stdafx.hpp"

#include "enemie_scene_node_manager.hpp"
#include "enemie_scene_node.hpp"

#include <algorithm>
#include <ctime>

using namespace irr;

cEnemieNodeManager::cEnemieNodeManager ( irr::IrrlichtDevice * _pDevice, 
			irr::core::vector3df _position, 
			irr::core::vector3df _rotation, 
			irr::core::vector3df _scale, 
			irr::scene::ISceneNode * _pParent, 
			irr::s32 _id )
	: m_pDevice ( _pDevice ), m_pSceneManager ( _pDevice->getSceneManager() ), m_counter ( 0 )
	, m_nEnemiesKilled ( 0 )
{}

cEnemieNode * cEnemieNodeManager::newEnemie ()
{
	std::string objectPath = m_vEnemiesTypesPath [ rand() % m_vEnemiesTypesPath.size () ];

	std::string texturePath = objectPath;

	objectPath += ".X";
	texturePath += ".tga";

	cEnemieNode * pEnemieNode = new cEnemieNode ( m_pSceneManager, ( c8 * ) objectPath.c_str(), this );

	pEnemieNode->setTexture ( ( c8 * ) texturePath.c_str (), m_pDevice->getVideoDriver () );

	push ( pEnemieNode );

	return pEnemieNode;
}

cEnemieNodeManager::~cEnemieNodeManager ()
{
	count ();

	if ( m_counter != 0 )
	{
		for ( int i = 0; i < m_counter; i++ )
		{
			m_vEnemies[i]->drop ();
			//delete m_vEnemies[i];
		}
	}

	clearVectors ();
}

void cEnemieNodeManager::clearEnemiesVector ()
{
	for ( int i = 0; i < m_vEnemies.size (); i++ )
	{	
		m_vEnemies[i]->getMeshSceneNode ()->setVisible ( false );
		m_vEnemies[i]->drop();
	}

	m_nEnemiesKilled = 0;

	m_vEnemies.clear ();
}