#include "Button.h"

// Service includes.
#include "Screen.h"

// Data includes.
#include "Game.h"

UserInterface::Button::Button(const Point _position, const Point _size, const uint16_t _spriteID) : Frame::Frame(_position, _size, _spriteID)
{ }

void UserInterface::Button::Initialise()
{
	// Bind the click function with the mouse click event.
	Game::GetService().GetEvents().AddFrameworkListener(SDL_MOUSEBUTTONDOWN, std::bind(&UserInterface::Button::handleClick, this, std::placeholders::_1, std::placeholders::_2));
}

/// <summary> Finds if this button was clicked based on the mouse position, if it was, fires its event. </summary>
/// <param name="_windowX"> The x position of the mouse relative to the window. </param>
/// <param name="_windowY"> The y position of the mouse relative to the window. </param>
void UserInterface::Button::handleClick(void* _windowX, void* _windowY)
{
	// Get the screen and events services.
	Screen& screen = Game::GetService().GetScreen();
	Events& events = Game::GetService().GetEvents();
	
	// Cast the x and y into a point.
	Point windowPosition(*static_cast<int32_t*>(_windowX), *static_cast<int32_t*>(_windowY));

	// Convert everything into screen-space.
	Point buttonScreenPosition = screen.WindowToScreenSpace(m_windowPosition);
	Point buttonScreenSize = screen.WindowToScreenSize(m_windowSize);

	// Check if the mouse position is within the bounds of this button.
	if (windowPosition.x >= buttonScreenPosition.x && windowPosition.y >= buttonScreenPosition.y &&
		windowPosition.x < buttonScreenPosition.x + buttonScreenSize.x && windowPosition.y < buttonScreenPosition.y + buttonScreenSize.y)
	{
		events.PushEvent(m_eventID, new int32_t(m_data), NULL);
	}
}