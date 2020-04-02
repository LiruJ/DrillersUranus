#ifndef GAMETIME_H
#define GAMETIME_H

// Derived includes.
#include "Time.h"

// Framework includes.
#include <SDL.h>

// Typedef includes.
#include <cmath>
#include <stdint.h>

namespace Time
{
	/// <summary> Represents a gametime object using SDL's performance counter. </summary>
	class GameTime : public DeltaTime
	{
	public:
		/// <summary> Updates the gametime for the current frame. </summary>
		inline void Update()							{ m_previousTicks = m_currentTicks; m_currentTicks = SDL_GetPerformanceCounter(); }

		/// <summary> Get the total amount of time that the game has been running in milliseconds. </summary>
		/// <returns> The total amount of milliseconds that the game has been running. </returns>
		inline virtual double_t		GetTotalTimeMS()	{ return GetTotalTimeS() * 1000.0; };

		/// <summary> Get the total amount of time that the game has been running in seconds. </summary>
		/// <returns> The total amount of seconds that the game has been running. </returns>
		virtual double_t			GetTotalTimeS()		{ return (double_t)m_currentTicks / SDL_GetPerformanceFrequency(); }

		/// <summary> Gets the amount of time that has passed since the last frame in milliseconds. </summary>
		/// <returns> The amount of time that has passed since the last frame in milliseconds. </returns>
		virtual double_t			GetDeltaTimeMS()	{ return GetDeltaTimeS() * 1000.0; }

		/// <summary> Gets the amount of time that has passed since the last frame in seconds. </summary>
		/// <returns> The amount of time that has passed since the last frame in seconds. </returns>
		virtual double_t			GetDeltaTimeS()		{ return (double_t)(m_currentTicks - m_previousTicks) / SDL_GetPerformanceFrequency(); }
	private:
		/// <summary> The current amount of SDL ticks since the game started. </summary>
		uint64_t m_currentTicks;

		/// <summary> The amount of SDL ticks since the game started last frame. </summary>
		uint64_t m_previousTicks;
	};
}
#endif