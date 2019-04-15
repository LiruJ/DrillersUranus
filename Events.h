#ifndef EVENTS_H
#define EVENTS_H

// Utility includes.
#include <functional>

namespace Events
{
	/// <summary> The user defined events. </summary>
	enum UserEvent { StartMinigame, StopMinigame, ChangeTool, QuitGame, MinedGem, PlayerDied };

	/// <summary> Represents a generic event bus that combines a framework's events along with user defined events. </summary>
	class Events
	{
	public:
		virtual ~Events() {}

		/// <summary> Creates an event with the given ID and data, then pushes it onto SDL's events bus. </summary>
		/// <param name="_eventID"> The ID of the user event. </param>
		/// <param name="_data1"> The first data to be put into the event. </param>
		/// <param name="_data2"> The second data to be put into the event. </param>
		/// <remarks> Data is not copied and is used as-is, and will be deleted when the event is read. Due to this, is it recommended to pass a copy of the data in. </remarks>
		virtual void PushEvent(UserEvent _eventID, void* _data1, void* _data2) = 0;

		/// <summary> Adds a function that will be called when the given user event is fired. </summary>
		/// <param name="_userEvent"> The user event. </param>
		/// <param name="_function"> The function to be called. </param>
		virtual void AddUserListener(UserEvent _userEvent, std::function<void(void*, void*)> _function) = 0;
		
		/// <summary> Adds a function that will be called when the given framework event is fired. </summary>
		/// <param name="_frameworkEventID"> The ID of the framework event. </param>
		/// <param name="_function"> The function to be called. </param>
		virtual void AddFrameworkListener(uint32_t _frameworkEventID, std::function<void(void*, void*)> _function) = 0;
	};
}
#endif