#include "stdafx.hpp"
#include "main_menu.h"
#include "main.h"

MainMenu::MainMenu(irr::gui::IGUIEnvironment* environment)
	: MenuInterface(environment)
{
	Init();
	Global::myEventReceiver->AddGuiObserver(this);
}

MainMenu::~MainMenu()
{
	Global::myEventReceiver->RemoveGuiObserver(this);
}

void MainMenu::Init()
{
	using namespace irr;

	_LoadBackground(std::string("export\\background.tga"));

	irr::gui::IGUIFont* font = m_env->getFont("export\\fonthaettenschweiler.bmp");
	if(font)
	{
		m_env->getSkin()->setFont(font);
	}
	else
	{
		m_env->getSkin()->setFont(m_env->getBuiltInFont(), 
			gui::EGDF_TOOLTIP);
	}

	m_env->addButton(core::rect<s32>(X_SIDE / 2, 
									 upBorder, 
									 X_SIDE / 2 + 200,
									 upBorder + 50), 
					 nullptr, 
					 GUI_ID_NEW_GAME, 
					 L"New Game / Continue game", 
					 L"Launches the game");

	m_env->addButton(core::rect<s32>(X_SIDE / 2,
									 upBorder + 100, 
									 X_SIDE / 2 + 200,
									 upBorder + 150),
					 nullptr, 
					 GUI_ID_QUIT_BUTTON, 
					 L"Quit", 
					 L"Quiting the game");

	// Setting up the game level buttons
	int levelButtonsXleft = 15;
	int levelButtonsXright = levelButtonsXleft + 200;
	
	m_levelButtons.resize(4);

	m_levelButtons[LEVEL_1] = m_env->addButton(core::rect<s32>(levelButtonsXleft, 
											   upBorder, 
											   levelButtonsXright, 
											   upBorder + 50)
							 , nullptr
							 , GUI_ID_CHOOSE_LEVEL_1
							 , L"Choose Level 1"
							 , L"Choosing the first game level");

	m_levelButtons[LEVEL_2] = m_env->addButton(core::rect<s32>(levelButtonsXleft, 
											   upBorder + 100, 
											   levelButtonsXright, 
											   upBorder + 150)
							 , nullptr
							 , GUI_ID_CHOOSE_LEVEL_2
							 , L"Choose Level 2"
							 , L"Choosing the second game level");

	m_levelButtons[LEVEL_3] = m_env->addButton(core::rect<s32>(levelButtonsXleft, 
											   upBorder + 200, 
											   levelButtonsXright, 
											  upBorder + 250)
							 , nullptr
							 , GUI_ID_CHOOSE_LEVEL_3
							 , L"Choose Level 3"
							 , L"Choosing the third game level");

	m_levelButtons[LEVEL_4] = m_env->addButton(core::rect<s32>(levelButtonsXleft,
											   upBorder + 300, 
											   levelButtonsXright, 
											   upBorder + 350)
							 , nullptr
							 , GUI_ID_CHOOSE_LEVEL_4
							 , L"Choose Level 4"
							 , L"Choosing the fourth game level");

	m_focusedLevelTargets.resize(4);
	m_focusedLevelTargets[LEVEL_1] = m_env->addImage(Global::spVideoDriver->getTexture("export/target.png"), 
		irr::core::vector2d<s32>(levelButtonsXright + 5, upBorder));
	m_focusedLevelTargets[LEVEL_2] = m_env->addImage(Global::spVideoDriver->getTexture("export/target.png"),
		irr::core::vector2d<s32>(levelButtonsXright + 5, upBorder + 100));
	m_focusedLevelTargets[LEVEL_3] = m_env->addImage(Global::spVideoDriver->getTexture("export/target.png"),
		irr::core::vector2d<s32>(levelButtonsXright + 5, upBorder + 200));
	m_focusedLevelTargets[LEVEL_4] = m_env->addImage(Global::spVideoDriver->getTexture("export/target.png"),
		irr::core::vector2d<s32>(levelButtonsXright + 5, upBorder + 300));

	for(int i = 0; i < m_focusedLevelTargets.size(); ++i)
	{
		m_focusedLevelTargets[i]->setVisible(false);
	}
}

void MainMenu::OnGuiEvent(const irr::SEvent& event)
{
	if(event.EventType != irr::EET_GUI_EVENT ||
		event.GUIEvent.EventType != irr::gui::EGET_BUTTON_CLICKED)
	{
		return;
	}

	switch(event.GUIEvent.Caller->getID())
	{
	case GUI_ID_CHOOSE_LEVEL_1:
		_setLevelButtonActive(GameLevels::LEVEL_1);
		break;

	case GUI_ID_CHOOSE_LEVEL_2:
		_setLevelButtonActive(GameLevels::LEVEL_2);
		break;

	case GUI_ID_CHOOSE_LEVEL_3:
		_setLevelButtonActive(GameLevels::LEVEL_3);
		break;

	case GUI_ID_CHOOSE_LEVEL_4:
		_setLevelButtonActive(GameLevels::LEVEL_4);
		break;
	}
}

void MainMenu::_setLevelButtonActive(GameLevels level)
{
	for(int i = 0; i <= GameLevels::LEVEL_4; ++i)
	{
		if(level != i)
		{
			m_levelButtons[i]->setSprite(
				irr::gui::EGUI_BUTTON_STATE::EGBS_BUTTON_UP, 0);
			m_focusedLevelTargets[i]->setVisible(false);
		}
		else
		{
			m_levelButtons[i]->setSprite(
				irr::gui::EGUI_BUTTON_STATE::EGBS_BUTTON_DOWN, 0);
			m_focusedLevelTargets[i]->setVisible(true);
		}
	}
}