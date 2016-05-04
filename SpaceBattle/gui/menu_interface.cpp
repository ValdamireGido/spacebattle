#include "stdafx.hpp"
#include "menu_interface.h"
#include "main.h"

using namespace irr;

MenuInterface::MenuInterface(gui::IGUIEnvironment* environment)
	: m_background(nullptr)
	, m_env(environment)
{}

MenuInterface::~MenuInterface()
{}

//////////////////////////////////////////////////////////

void MenuInterface::_LoadBackground(const std::string& path)
{
	m_background = m_env->addImage(Global::spVideoDriver->getTexture(path.c_str()), core::vector2di(0, 0));
	assert(m_background);
}