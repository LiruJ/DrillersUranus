#ifndef EVENTS_H
#define EVENTS_H

// Utility includes.
#include <functional>

namespace Events
{
	enum UserEvent
	{
		StartMinigame, StopMinigame, ChangeTool, QuitGame
	};

	class Events
	{
	public:
		virtual ~Events() {}

		virtual void PushEvent(UserEvent, void*, void*) = 0;

		virtual void AddUserListener(UserEvent, std::function<void(void*, void*)>) = 0;
		virtual void AddFrameworkListener(uint32_t, std::function<void(void*, void*)>) = 0;
	};
}
#endif