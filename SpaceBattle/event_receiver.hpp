#ifndef _EVENT_RECEIVER_HPP
#define _EVENT_RECEIVER_HPP

#include "stdafx.hpp"
#include <algorithm>

// Context application structure //
struct sApplicationContext
{
	irr::IrrlichtDevice * m_pMainDevice;
	irr::s32 m_counter;
	bool isInGame;
	unsigned int currentLevel;
};

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_GAME,
	GUI_ID_GAME_CONTINUE,

	GUI_ID_CHOOSE_LEVEL_1,
	GUI_ID_CHOOSE_LEVEL_2,
	GUI_ID_CHOOSE_LEVEL_3,
	GUI_ID_CHOOSE_LEVEL_4
};

struct EventReceiverGuiObserver
{
	virtual void OnGuiEvent(const irr::SEvent & event) {};
};

class MyEventReceiver 
	: public irr::IEventReceiver
{
private:
	// We use this array to store the current state of each key
	bool KeyIsDown [irr::KEY_KEY_CODES_COUNT];
	sApplicationContext * m_pContext;

	std::vector<EventReceiverGuiObserver*> m_guiObservers;

private:
	void NotifyGuiObservers(const irr::SEvent& event)
	{
		std::vector<EventReceiverGuiObserver*>::iterator it = 
			m_guiObservers.begin();
		for(; it != m_guiObservers.end(); ++it)
		{
			if(*it)
			{
				(*it)->OnGuiEvent(event);
			}
		}
	}

public:
	MyEventReceiver()
	{
		for ( irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i )
			KeyIsDown [i] = false;
	}

	MyEventReceiver( sApplicationContext * _pContext ) 
		: m_pContext ( _pContext )
	{
		for ( irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i )
		{
			KeyIsDown [i] = false;
		}
	}

	// This is the one method that we have to implement
	virtual bool OnEvent ( const irr::SEvent & _event )
	{
		// Remember whether each key is down or up
		if ( _event.EventType == irr::EET_KEY_INPUT_EVENT )
			KeyIsDown [_event.KeyInput.Key] = _event.KeyInput.PressedDown;

		if ( _event.EventType == irr::EET_GUI_EVENT )
		{
			NotifyGuiObservers(_event);

			irr::s32 id = _event.GUIEvent.Caller->getID ();
			irr::gui::IGUIEnvironment * pGUIEnvironment = m_pContext->m_pMainDevice->getGUIEnvironment();

			switch ( _event.GUIEvent.EventType )
			{
			case irr::gui::EGET_BUTTON_CLICKED:
				switch ( id )
				{
				case GUI_ID_QUIT_BUTTON:
					if ( ! m_pContext->isInGame )
					{
						m_pContext->m_pMainDevice->closeDevice ();
						return true;
					}
					return false;

				case GUI_ID_NEW_GAME:
					if ( ! m_pContext->isInGame )
					{
						printf ( "DEBUG: gui_id_new_game button pressed\n" );
						m_pContext->isInGame = true;
						return true;
					}
					return false;

				case GUI_ID_CHOOSE_LEVEL_1:
				case GUI_ID_CHOOSE_LEVEL_2:
				case GUI_ID_CHOOSE_LEVEL_3:
				case GUI_ID_CHOOSE_LEVEL_4:
					if(m_pContext)
					{
						m_pContext->currentLevel = id;
						return true;
					}
					return false;
				}
			}
		}

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown ( irr::EKEY_CODE keyCode ) const
	{
		return KeyIsDown [keyCode];
	}
	
	void AddGuiObserver(EventReceiverGuiObserver* observer)
	{
		assert(observer);
		if(observer)
		{
			m_guiObservers.push_back(observer);
		}
	}

	void RemoveGuiObserver(EventReceiverGuiObserver* observer)
	{
		assert(observer);
		for(int i = 0; i < m_guiObservers.size(); ++i)
		{
			if(m_guiObservers[i] == observer)
			{
				m_guiObservers.erase(m_guiObservers.begin() + i);
				break;
			}
		}
	}
};

#endif //_EVENT_RECEIVER_HPP