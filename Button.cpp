#include "Button.h"

// Framework includes.
#include <SDL_events.h>

// Service includes.
#include "Audio.h"
#include "Screen.h"

// Utility includes.
#include "AudioData.h"

/// <summary> Initialises this <see cref="Button"/>'s click binding. </summary>
/// <param name="_events"> The events bus. </param>
void UserInterface::Button::Initialise(Events::Events& _events)
{
	_events.AddFrameworkListener(SDL_MOUSEBUTTONDOWN, std::bind(&UserInterface::Button::handleClick, this, std::placeholders::_1));
}

/// <summary> Finds if this button was clicked based on the mouse position, if it was, fires its event. </summary>
/// <param name="_context"> The context of the event. </param>
void UserInterface::Button::handleClick(Events::EventContext* _context)
{
	// If this button is not active, do nothing.
	if (!m_isActive) { return; }
	
	// Cast the x and y into a point.
	Point windowPosition(*static_cast<int32_t*>(_context->m_data1), *static_cast<int32_t*>(_context->m_data2));

	// Check if the mouse position is within the bounds of this button, if it is, push the event and play the sound.
	if (m_bounds.IsPointInside(_context->m_services->GetService<Screens::Screen>(Services::ServiceType::Screen).WindowToScreenSpace(windowPosition)))
	{
		_context->m_services->GetService<Events::Events>(Services::ServiceType::Events).PushEvent(m_eventID, new int32_t(m_data), NULL);
		_context->m_services->GetService<Audio::Audio>(Services::ServiceType::Audio).PlaySound(AudioData::SoundID::UIClick);
	}
}