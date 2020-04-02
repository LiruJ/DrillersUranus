#ifndef TIME_H
#define TIME_H

// Typedef includes.
#include <cmath>

namespace Time
{
	/// <summary> Represents an interfaced version of a time manager class which allows for access to game time. </summary>
	class DeltaTime
	{
	public:
		virtual ~DeltaTime() {}

		/// <summary> Get the total amount of time that the game has been running in milliseconds. </summary>
		/// <returns> The total amount of milliseconds that the game has been running. </returns>
		virtual double_t GetTotalTimeMS() = 0;

		/// <summary> Get the total amount of time that the game has been running in seconds. </summary>
		/// <returns> The total amount of seconds that the game has been running. </returns>
		virtual double_t GetTotalTimeS() = 0;

		/// <summary> Gets the amount of time that has passed since the last frame in milliseconds. </summary>
		/// <returns> The amount of time that has passed since the last frame in milliseconds. </returns>
		virtual double_t GetDeltaTimeMS() = 0;

		/// <summary> Gets the amount of time that has passed since the last frame in seconds. </summary>
		/// <returns> The amount of time that has passed since the last frame in seconds. </returns>
		virtual double_t GetDeltaTimeS() = 0;
	};
}
#endif