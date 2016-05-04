#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "menu_interface.h"
#include "event_receiver.hpp"

class irr::gui::IGUIEnvironment;

class MainMenu
	: public MenuInterface
	, public EventReceiverGuiObserver
{
public:
	enum GameLevels
	{
		  LEVEL_1 = 0
		, LEVEL_2
		, LEVEL_3
		, LEVEL_4
	};

public:
	MainMenu(irr::gui::IGUIEnvironment* environment);
	~MainMenu();

	virtual void Init();
	
	virtual void OnGuiEvent(const irr::SEvent& event);

private:
	void _setLevelButtonActive(GameLevels level);

private:
	std::vector<irr::gui::IGUIButton*> m_levelButtons;
};

#endif //_MAIN_MENU_H_