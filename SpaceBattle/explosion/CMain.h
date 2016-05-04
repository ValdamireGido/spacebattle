#ifndef CMAIN_H
#define CMAIN_H

#include <irrlicht.h>
#include "CParticleSystem.h"
#include "CParticleEmitter.h"
#include "CParticleDrawer.h"

namespace irr
{
    namespace scene
    {
        class CParticleSystem;
    }
}

class ColorAffector 
	: public CParticleAffector
{
public:
    ColorAffector(const irr::video::SColor& targetColor);

    void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff);

    irr::video::SColor Target;

};


class ColorAffectorQ 
	: public CParticleAffector
{
public:
    ColorAffectorQ(const irr::video::SColor& targetColor0, const irr::video::SColor& targetColor1);

    void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff);

    irr::video::SColor Target0;
    irr::video::SColor Target1;

};

class GravityAffector 
	: public CParticleAffector
{
public:
    GravityAffector(const irr::core::vector3df& gravity);

    void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff);

    irr::core::vector3df Gravity;

};

class PlaneCollisionAffector
	: public CParticleAffector
{
public:
    PlaneCollisionAffector(const irr::core::plane3df& plane);

    void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff);

    irr::core::plane3df Plane;
};

class CParticleEmitterPoint 
	: public CParticleEmitter
{
public:
    CParticleEmitterPoint(const irr::core::vector3df& rotation = irr::core::vector3df(0,0,0)
		, const irr::core::vector3df& rotationspeed = irr::core::vector3df(0,0,0)
		, const irr::core::vector3df& speed = irr::core::vector3df(0,1,0)
		, const irr::core::vector3di& maxAngle = irr::core::vector3di(45,0,45)
		, const irr::u32& minPpS = 50, const irr::u32& maxPpS = 100, const irr::u32& maxEmitt = 100
		, const irr::u32& minlifetime = 100, const irr::u32& maxlifetime = 1000
		, const irr::core::vector2df& minsize = irr::core::vector2df(1,1)
		, const irr::core::vector2df& maxsize = irr::core::vector2df(1,1)
		, const irr::core::vector2df& sizespeed = irr::core::vector2df(0,0)
		, const irr::video::SColor& minColor = irr::video::SColor(255,255,255,255)
		, const irr::video::SColor& maxColor = irr::video::SColor(255,255,255,255));
    virtual ~CParticleEmitterPoint(void) {}

    void emitt(const irr::core::matrix4& transform
		, irr::core::list<Particle*>& particles
		, irr::core::list<Particle*>& particlepool
		, irr::u32 timeMs, irr::f32 diff
		, const irr::core::array<SParticleUV>& coords);

};

void addExplosion ( const irr::core::vector3df& pos
	, const irr::core::vector3df& rot
	, const irr::u32& scale
	, irr::scene::ISceneManager* smgr
	, const irr::core::plane3df& p
	, irr::scene::ITriangleSelector* selector );

#endif // CMAIN_H
