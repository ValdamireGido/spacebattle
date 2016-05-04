#ifndef GAME_OBJECT_SCENE_NODE_HPP
#define GAME_OBJECT_SCENE_NODE_HPP

#include "stdafx.hpp"

class cGameNode
{
// Fields //
private:
	
	bool m_isAlive;

protected:
	irr::scene::IAnimatedMeshSceneNode * m_pMeshSceneNode;
	irr::scene::IAnimatedMesh * m_pMesh;
	irr::scene::ISceneManager * m_pSceneManager;

// Methods //
	cGameNode (); // Default constructor

	cGameNode ( const cGameNode & _gn );

public:

	cGameNode ( irr::scene::ISceneManager * _pSceneManager, irr::c8 * _meshPath,
			irr::core::vector3df _position = irr::core::vector3df ( 0, 0, 0 ),
			irr::core::vector3df _rotation = irr::core::vector3df ( 0, 0, 0 ), 
			irr::core::vector3df _scale = irr::core::vector3df ( 1.0f, 1.0f, 1.0f ),
			irr::scene::ISceneNode * _pParent = nullptr,
			irr::s32 _id = -1 );

	virtual void setTexture ( irr::c8 * _texturePath, irr::video::IVideoDriver * _pVideoDriver, int _layer = 0, 
		irr::video::E_MATERIAL_FLAG _materialFlag = irr::video::EMF_LIGHTING, bool newValue = false );

	virtual void setMesh ( irr::scene::IAnimatedMesh * _pMesh ); // Mesh Setter 

	virtual irr::scene::IAnimatedMesh * getMesh (); // Mesh getter

	virtual void setMeshSceneNode ( irr::scene::IAnimatedMeshSceneNode * _pMeshSceneNode ); // MeshSceneNode setter

	virtual irr::scene::IAnimatedMeshSceneNode * getMeshSceneNode (); // MeshSceneNode getter

	virtual irr::scene::ISceneManager * getSceneManager ();

	virtual void setSceneManager ( irr::scene::ISceneManager * _pSceneManager );

	virtual void drop ();

	virtual bool isAlive ();

};

inline void cGameNode::drop ()
{
	delete this;
}

inline bool cGameNode::isAlive ()
{
	return m_isAlive;
}

inline irr::scene::ISceneManager * cGameNode::getSceneManager ()
{
	return m_pSceneManager;
}

inline void cGameNode::setSceneManager ( irr::scene::ISceneManager * _pSceneManager )
{
	m_pSceneManager = _pSceneManager;
}

#endif // GAME_OBJECT_SCENE_NODE_HPP