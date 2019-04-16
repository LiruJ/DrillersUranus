#include "MainMenu.h"

// Service includes.
#include "Game.h"
#include "Screen.h"

/// <summary> Draws the menu. </summary>
void UserInterface::MainMenu::Draw()
{
	// Draw the background first.
	m_backgroundFrame.Draw();

	// Draw the help screen.
	m_helpFrame.Draw();

	// Draw the buttons.
	m_playButton.Draw();
	m_helpButton.Draw();
	m_exitButton.Draw();
	m_backButton.Draw();
}

/// <summary> Binds events. </summary>
void UserInterface::MainMenu::Initialise()
{
	// Initialise the buttons.
	m_playButton.SetEvent(Events::UserEvent::StartGame, 0);
	m_playButton.Initialise();

	m_helpButton.SetEvent(Events::UserEvent::HelpScreen, 0);
	m_helpButton.Initialise();

	m_exitButton.SetEvent(Events::UserEvent::QuitGame, 0);
	m_exitButton.Initialise();

	m_backButton.SetEvent(Events::UserEvent::MainMenu, 0);
	m_backButton.Initialise();

	// Get the events service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind the state events.
	events.AddUserListener(Events::UserEvent::StartGame, std::bind(&MainMenu::disableAll, this, std::placeholders::_1, std::placeholders::_2));
	events.AddUserListener(Events::UserEvent::HelpScreen, std::bind(&MainMenu::showHelp, this, std::placeholders::_1, std::placeholders::_2));
	events.AddUserListener(Events::UserEvent::MainMenu, std::bind(&MainMenu::hideHelp, this, std::placeholders::_1, std::placeholders::_2));
}

/// <summary> Sets all non-background elements to the given active value. </summary>
/// <param name="_active"> The new active value. </param>
void UserInterface::MainMenu::setAllActive(const bool _active)
{
	m_helpFrame.SetActive(_active);

	m_backButton.SetActive(_active);
	m_playButton.SetActive(_active);
	m_helpButton.SetActive(_active);
	m_exitButton.SetActive(_active);
}

/// <summary> Shows the help screen and back button. </summary>
void UserInterface::MainMenu::showHelp(void *, void *)
{
	// Start by disabling all elements.
	setAllActive(false);

	// Enable the back button and the help frame.
	m_helpFrame.SetActive(true);
	m_backButton.SetActive(true);
}

/// <summary> Hides the help screen and reactivates the menu. </summary>
void UserInterface::MainMenu::hideHelp(void *, void *)
{
	// Start by enabling all elements.
	setAllActive(true);

	// Disable the back button and the help frame.
	m_helpFrame.SetActive(false);
	m_backButton.SetActive(false);
}
