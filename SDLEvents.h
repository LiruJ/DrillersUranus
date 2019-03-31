#ifndef SDLEVENTS_H
#define SDLEVENTS_H

#include "Events.h"
#include "SDL.h"

#include <vector>
#include <map>

class SDLEvents : public Events
{
public:
	SDLEvents() : 
		m_functionsBySDLEventID(std::map<uint32_t, std::vector<std::function<void(void*, void*)>>>()),
		m_startingEventIndex(SDL_RegisterEvents(4)) { }

	void PumpEvents();

	virtual void PushEvent(UserEvent, void*, void*);

	virtual void AddFrameworkListener(uint32_t, std::function<void(void*, void*)>);
	virtual void AddUserListener(const UserEvent _userEvent, std::function<void(void*, void*)> _function) { AddFrameworkListener(m_startingEventIndex + _userEvent, _function); }
private:
	/// <summary> The index in SDL's event register of the user-defined events. </summary>
	uint32_t m_startingEventIndex;

	/// <summary> Vectors of functions keyed by SDLEvent IDs. </summary>
	std::map<uint32_t, std::vector<std::function<void(void*, void*)>>> m_functionsBySDLEventID;

	void fireEvents(std::vector<std::function<void(void*, void*)>>&, void*, void*);
};
#endif