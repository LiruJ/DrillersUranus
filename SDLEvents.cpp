#include "SDLEvents.h"

/// <summary> Pumps every event in the queue and fires any bound events. </summary>
/// <param name="_currentGameState"> The current state of the game. </param>
/// <param name="_services"> The service provider. </param>
void Events::SDLEvents::PumpEvents(const MainGame::GameState _currentGameState, Services::ServiceProvider& _services)
{
	// Go through every event in the queue.
	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent))
	{
		// If no functions are bound to this event, skip it.
		if (m_functionsBySDLEventID.count(currentEvent.type) == 0) { continue; }

		// Create an EventContext to hold the data.
		EventContext* eventContext = new EventContext(_currentGameState, _services);

		// Get the functions bound to this event.
		std::vector<std::function<void(EventContext*)>>& eventFunctions = m_functionsBySDLEventID[currentEvent.type];

		// Handle user events then delete the data.
		if (currentEvent.type >= m_startingEventIndex) 
		{
			fireEvents(eventFunctions, eventContext->SetData(currentEvent.user.data1, currentEvent.user.data2));
			delete currentEvent.user.data1;
			delete currentEvent.user.data2;
		}

		//Handle SDL events.
		else 
		{
			switch (currentEvent.type)
			{
			case SDL_QUIT: { fireEvents(eventFunctions, eventContext->SetData(NULL, NULL)); break; }
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP: { fireEvents(eventFunctions, eventContext->SetData(&currentEvent.button.x, &currentEvent.button.y)); break; }
			case SDL_MOUSEMOTION: { fireEvents(eventFunctions, eventContext->SetData(&currentEvent.motion.x, &currentEvent.motion.y)); break; }
			case SDL_KEYDOWN: { fireEvents(eventFunctions, eventContext->SetData(&currentEvent.key.keysym.scancode, &currentEvent.key.keysym.mod)); break; }
			case SDL_WINDOWEVENT: 
			{
				switch (currentEvent.window.event)
				{
				case SDL_WINDOWEVENT_SIZE_CHANGED: { fireEvents(eventFunctions, eventContext->SetData(&currentEvent.window.data1, &currentEvent.window.data2)); break; }
				}
				break;
			}
			}
		}

		// Delete the event context.
		delete eventContext;
		eventContext = NULL;
	}
}

/// <summary> Creates an event with the given ID and data, then pushes it onto SDL's events bus. </summary>
/// <param name="_eventID"> The ID of the user event. </param>
/// <param name="_data1"> The first data to be put into the event. </param>
/// <param name="_data2"> The second data to be put into the event. </param>
/// <remarks> Data is not copied and is used as-is, and will be deleted when the event is read. Due to this, is it recommended to pass a copy of the data in. </remarks>
void Events::SDLEvents::PushEvent(const UserEvent _eventID, void* _data1, void* _data2)
{
	// Create a new event and clear its memory to 0.
	SDL_Event newEvent;
	SDL_memset(&newEvent, 0, sizeof(newEvent));

	// Set the type to the given type.
	newEvent.type = m_startingEventIndex + _eventID;

	// Set the data of the new event then push it onto the event bus.
	newEvent.user.data1 = _data1;
	newEvent.user.data2 = _data2;
	SDL_PushEvent(&newEvent);
}

/// <summary> Adds a function that will be called when the given SDL event is fired. </summary>
/// <param name="_sdlEventID"> The ID of the SDL event. </param>
/// <param name="_function"> The function to be called. </param>
void Events::SDLEvents::AddFrameworkListener(uint32_t _sdlEventID, std::function<void(EventContext*)> _function)
{
	// If the given SDL Event ID does not have any bound functions, initialise the vector with the function.
	if (m_functionsBySDLEventID.count(_sdlEventID) == 0) { m_functionsBySDLEventID.emplace(_sdlEventID, std::vector<std::function<void(EventContext*)>>(1, _function)); }

	// Otherwise, push the function onto the existing vector.
	else { m_functionsBySDLEventID[(SDL_EventType)_sdlEventID].push_back(_function); }
}

/// <summary> Fires every function bound an event with the given data. </summary>
/// <param name="_functions"> The functions bound to the event. </param>
/// <param name="_context"> The context of the event. </param>
void Events::SDLEvents::fireEvents(std::vector<std::function<void(EventContext*)>>& _functions, EventContext& _context) 
{
	for (uint32_t i = 0; i < _functions.size(); i++) { _functions[i](&_context); } 
}
