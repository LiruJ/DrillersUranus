#include "MainMenu.h"

/// <summary> Draws the menu. </summary>
/// <param name="_services"> The service provider. </param>
void UserInterface::MainMenu::Draw(Services::ServiceProvider& _services) const
{
	// Draw the background first.
	m_backgroundFrame.Draw(_services);

	// Draw the help screen.
	m_helpFrame.Draw(_services);

	// Draw the buttons.
	m_playButton.Draw(_services);
	m_helpButton.Draw(_services);
	m_exitButton.Draw(_services);
	m_backButton.Draw(_services);
}

/// <summary> Binds events. </summary>
void UserInterface::MainMenu::Initialise(Events::Events& _events)
{
	// Initialise the buttons.
	m_playButton.SetEvent(Events::UserEvent::StartGame, 0);
	m_playButton.Initialise(_events);

	m_helpButton.SetEvent(Events::UserEvent::HelpScreen, 0);
	m_helpButton.Initialise(_events);

	m_exitButton.SetEvent(Events::UserEvent::QuitGame, 0);
	m_exitButton.Initialise(_events);

	m_backButton.SetEvent(Events::UserEvent::MainMenu, 0);
	m_backButton.Initialise(_events);

	// Bind the state events.
	_events.AddUserListener(Events::UserEvent::StartGame, std::bind(&MainMenu::disableAll, this, std::placeholders::_1));
	_events.AddUserListener(Events::UserEvent::HelpScreen, std::bind(&MainMenu::showHelp, this, std::placeholders::_1));
	_events.AddUserListener(Events::UserEvent::MainMenu, std::bind(&MainMenu::hideHelp, this, std::placeholders::_1));
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
void UserInterface::MainMenu::showHelp(Events::EventContext*)
{
	// Start by disabling all elements.
	setAllActive(false);

	// Enable the back button and the help frame.
	m_helpFrame.SetActive(true);
	m_backButton.SetActive(true);
}

/// <summary> Hides the help screen and reactivates the menu. </summary>
void UserInterface::MainMenu::hideHelp(Events::EventContext*)
{
	// Start by enabling all elements.
	setAllActive(true);

	// Disable the back button and the help frame.
	m_helpFrame.SetActive(false);
	m_backButton.SetActive(false);
}
