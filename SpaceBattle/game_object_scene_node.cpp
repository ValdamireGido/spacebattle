#include "StdAfx.hpp"
#include "game_object_scene_node.hpp"

cGameNode::cGameNode ( irr::scene::ISceneManager * _pSceneManager, irr::c8 * _meshPath,
			irr::core::vector3df _position,
			irr::core::vector3df _rotation, 
			irr::core::vector3df _scale,
			irr::scene::ISceneNode * _pParent,
			irr::s32 _id )
	: m_pSceneManager ( _pSceneManager )
{
	setMesh ( _pSceneManager->getMesh ( _meshPath ) );

	setMeshSceneNode ( _pSceneManager->addAnimatedMeshSceneNode ( m_pMesh, _pParent, _id ) );

	m_pMeshSceneNode->setID ( _id );
	m_pMeshSceneNode->setPosition ( _position );
	m_pMeshSceneNode->setRotation ( _rotation );
	m_pMeshSceneNode->setScale ( _scale );
}

void cGameNode::setTexture ( irr::c8 * _texturePath, irr::video::IVideoDriver * _pVideoDriver, int _layer, 
		irr::video::E_MATERIAL_FLAG _materialFlag, bool newValue )
{
	if ( this )
	{
		getMeshSceneNode ()->setMaterialFlag ( _materialFlag, newValue );
		getMeshSceneNode ()->setMaterialTexture ( _layer, _pVideoDriver->getTexture ( _texturePath ) );
	}
}

void cGameNode::setMesh ( irr::scene::IAnimatedMesh * _pMesh )
{
	m_pMesh = _pMesh;
}

irr::scene::IAnimatedMesh * cGameNode::getMesh ()
{
	return m_pMesh;
}

void cGameNode::setMeshSceneNode ( irr::scene::IAnimatedMeshSceneNode * _pMeshSceneNode )
{
	m_pMeshSceneNode = _pMeshSceneNode;
}

irr::scene::IAnimatedMeshSceneNode * cGameNode::getMeshSceneNode ()
{
	return m_pMeshSceneNode;
}

