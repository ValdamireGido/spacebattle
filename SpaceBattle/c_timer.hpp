#ifndef C_TIMER_HPP
#define C_TIMER_HPP

#include "stdafx.hpp"

class cTimer
{
private:
	int m_time;
	int m_currentTime;
	int m_deltaTime;

	irr::IrrlichtDevice * m_pDevice;

private:
	cTimer ( const cTimer & _timer );
	cTimer ( cTimer & _timer );

public:
	cTimer ();
	cTimer ( irr::IrrlichtDevice * _pDevice );

	int getTime ();

	int getDeltaTime ();
	
	int getCurrentTime ();

	int calculateTime ();

	int calculateCurrentTime ();

	int calculateDeltaTime ();
};

inline cTimer::cTimer ( irr::IrrlichtDevice * _pDevice )
	: m_pDevice ( _pDevice ), m_deltaTime ( 0 ), m_currentTime ( 0 )
{
	m_time = calculateTime ();
}

inline int cTimer::getTime ()
{
	return m_time;
}

inline int cTimer::getDeltaTime ()
{
	return m_deltaTime;
}

inline int cTimer::getCurrentTime ()
{
	return m_currentTime;
}

inline int cTimer::calculateTime ()
{
	return m_time = m_pDevice->getTimer ()->getTime ();
}

inline int cTimer::calculateCurrentTime ()
{
	return m_currentTime = m_pDevice->getTimer ()->getTime ();
}

inline int cTimer::calculateDeltaTime ()
{
	calculateCurrentTime ();
	return m_deltaTime = m_currentTime - m_time;
}

#endif // C_TIMER_HPP