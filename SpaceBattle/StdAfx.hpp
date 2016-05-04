#ifndef _STDAFX_HPP
#define _STDAFX_HPP

#define nullptr NULL
#define override 
#define final 

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "irrlicht.h"

#ifdef _MSC_VER

#define _CRT_SECURE_NO_WARNINGS

#pragma comment ( lib, "Irrlicht.lib" )
#pragma comment ( lib, "irrKlang.lib" )

#endif

#define MOVEMENT_SPEED 0.5f

#define UP_BORDER 100
#define DOWN_BORDER -100

// Screen size
#define X_SIDE 1024
#define Y_SIDE 768

#endif // _STDAFX_HPP