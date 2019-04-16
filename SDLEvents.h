#ifndef SDLEVENTS_H
#define SDLEVENTS_H

// Derived includes.
#include "Events.h"

// Framework includes.
#include "SDL.h"

// Utility includes
#include <vector>
#include <map>

namespace Events
{
	/// <summary> Represents an event bus that combines user events with SDL events. </summary>
	class SDLEvents : public Events
	{
	public:
		/// <summary> Creates a new event bus and registers the user events. </summary>
		SDLEvents() : m_functionsBySDLEventID(std::map<uint32_t, std::vector<std::function<void(void*, void*)>>>()), m_startingEventIndex(SDL_RegisterEvents(8)) { }

		void PumpEvents();

		virtual void PushEvent(UserEvent, void*, void*);

		virtual void AddFrameworkListener(uint32_t, std::function<void(void*, void*)>);

		/// <summary> Adds a function that will be called when the given user event is fired. </summary>
		/// <param name="_userEvent"> The user event. </param>
		/// <param name="_function"> The function to be called. </param>
		virtual void AddUserListener(const UserEvent _userEvent, std::function<void(void*, void*)> _function) { AddFrameworkListener(m_startingEventIndex + _userEvent, _function); }
	private:
		/// <summary> The index in SDL's event register of the user-defined events. </summary>
		uint32_t															m_startingEventIndex;

		/// <summary> Vectors of functions keyed by SDLEvent IDs. </summary>
		std::map<uint32_t, std::vector<std::function<void(void*, void*)>>>	m_functionsBySDLEventID;

		void fireEvents(std::vector<std::function<void(void*, void*)>>&, void*, void*);
	};
}
#endif