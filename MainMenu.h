#ifndef MAINMENU_H
#define MAINMENU_H

// Utility includes.
#include "SpriteData.h"

// Service includes.
#include "ServiceProvider.h"
#include "EventContext.h"
#include "Events.h"

// UI includes.
#include "Frame.h"
#include "Button.h"

namespace UserInterface
{
	class MainMenu
	{
	public:
		/// <summary> Creates the default main menu. </summary>
		MainMenu() : m_backgroundFrame(Point(0, 0), Point(960, 540), SpriteData::UIID::MenuBackground),
			m_helpFrame(Point(320, 142), Point(320, 256), SpriteData::UIID::HelpScreen),
			m_playButton(Point(416, 208), Point(128, 32), SpriteData::UIID::PlayButton),
			m_helpButton(Point(416, 256), Point(128, 32), SpriteData::UIID::HelpButton),
			m_exitButton(Point(416, 304), Point(128, 32), SpriteData::UIID::QuitButton),
			m_backButton(Point(323, 363), Point(128, 32), SpriteData::UIID::BackButton)
		{
			// Hide the help screen to start with.
			hideHelp();
		}

		void Draw(Services::ServiceProvider&) const;

		void Initialise(Events::Events&);
	private:
		/// <summary> If the help screen is being displayed. </summary>
		bool m_isInHelpScreen;

		/// <summary> The background title image. </summary>
		Frame m_backgroundFrame;

		/// <summary> The help screen frame. </summary>
		Frame m_helpFrame;

		/// <summary> The button that begins the game. </summary>
		Button m_playButton;

		/// <summary> The button that displays the help screen. </summary>
		Button m_helpButton;

		/// <summary> The button that quits the game. </summary>
		Button m_exitButton;

		/// <summary> The button that takes the player back to the main menu from any sub-menus. </summary>
		Button m_backButton;

		void setAllActive(bool);

		/// <summary> Disables all main elements. </summary>
		void disableAll(Events::EventContext* = NULL) { setAllActive(false); }

		void showHelp(Events::EventContext* = NULL);

		void hideHelp(Events::EventContext* = NULL);
	};
}
#endif