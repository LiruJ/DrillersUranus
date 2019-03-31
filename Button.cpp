#include "Button.h"

// Service includes.
#include "Game.h"
#include "Screen.h"

/// <summary> Initialises this <see cref="Button"/>'s click binding. </summary>
void UserInterface::Button::Initialise()
{
	MainGame::Game::GetService().GetEvents().AddFrameworkListener(SDL_MOUSEBUTTONDOWN, std::bind(&UserInterface::Button::handleClick, this, std::placeholders::_1, std::placeholders::_2));
}

/// <summary> Finds if this button was clicked based on the mouse position, if it was, fires its event. </summary>
/// <param name="_windowX"> The x position of the mouse relative to the window. </param>
/// <param name="_windowY"> The y position of the mouse relative to the window. </param>
void UserInterface::Button::handleClick(void* _windowX, void* _windowY)
{
	// Get the screen and events services.
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();
	Events::Events& events = MainGame::Game::GetService().GetEvents();
	
	// Cast the x and y into a point.
	Point windowPosition(*static_cast<int32_t*>(_windowX), *static_cast<int32_t*>(_windowY));

	// Check if the mouse position is within the bounds of this button, if it is, push the event.
	if (m_screenBounds.IsPointInside(screen.WindowToScreenSpace(windowPosition))) { events.PushEvent(m_eventID, new int32_t(m_data), NULL); }
}