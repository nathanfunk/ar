/*
	Timer.h

		Timer abstract base class.

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://rsn.gamedev.net/pl3d
	Copyright (C)2000, 2001, Brett Porter. All Rights Reserved.
	This source code is released under the LGPL. See license.txt for details.

	Created: 18 July 2000
	Last Edited: 6 February 2001

	Please see the file ChangeLog.html for a revision history.
*/

#ifndef PORTALIB3D_TIMER_H
#define PORTALIB3D_TIMER_H

class Timer
{
	public:
		/*	Constructor. */
		Timer();

		/*	Destructor. */
		virtual ~Timer();

		/*	Reset the timer to zero. */
		virtual void reset() = 0;

		virtual void reset(float initialTime) = 0;
		/*	Retrieve the time in milliseconds since the timer started. */
		virtual double getTime() const = 0;

		/*	Return a new timer. IMPLEMENT THIS IN THE FILE FOR THE DERIVED CLASS. */
		static Timer *getNewTimer();

		/*	Pause this timer. */
		virtual void pause() = 0;

		/*	Unpause this timer. */
		virtual void unpause() = 0;

		/*	Pause all timers. */
		static void pauseAll();

		/*	Unpause all timers. */
		static void unpauseAll();

	private:
		struct TimerLink
		{
			Timer *m_pTimer;
			TimerLink *m_pNext;
		};

		static TimerLink *m_pTimerList;
};

#endif	// PORTALIB3D_TIMER_H
