#ifndef GAMEMENU_H
#define GAMEMENU_H

// Service includes.
#include "ServiceProvider.h"
#include "Events.h"
#include "EventContext.h"

// Data includes.
#include "Point.h"

// UI includes.
#include "Frame.h"
#include "Button.h"
#include "Minimap.h"

// Forward declaration.
namespace WorldObjects { class World; }

namespace UserInterface
{
	/// <summary> Represents the UI for the main game. </summary>
	class GameMenu
	{
	public:
		/// <summary> Creates the basic game menu. </summary>
		GameMenu() : m_currentState(MenuState::Alive) {}

		void Initialise(Events::Events&);

		void Draw(WorldObjects::World& _world, Services::ServiceProvider&);
	private:
		/// <summary> The different states of the menu. </summary>
		enum MenuState { Alive, Dead, Escaped };

		/// <summary> The state of the menu currently. </summary>
		MenuState	m_currentState;

		/// <summary> The frame at appaears at the right side of the screen. </summary>
		Frame		m_sideBar;

		/// <summary> The button that takes the player back to the main menu. </summary>
		Button		m_quitButton;

		/// <summary> The end screen that shows when the player dies. </summary>
		Frame		m_endScreen;
		
		/// <summary> The minimap. </summary>
		Minimap		m_minimap;

		void setActive(bool);

		/// <summary> Hides this menu. </summary>
		void hide(Events::EventContext* = NULL) { setActive(false); }

		/// <summary> Shows this menu. </summary>
		void show(Events::EventContext* = NULL) { setActive(true); }

		/// <summary> Shows the lost screen. </summary>
		void showLostScreen(Events::EventContext* = NULL) { m_currentState = MenuState::Dead; m_endScreen.SetActive(true); m_quitButton.SetPosition(Point(384, 286)); }

		/// <summary> Shows the won screen. </summary>
		void showWonScreen(Events::EventContext* = NULL) { m_currentState = MenuState::Escaped; m_endScreen.SetActive(true); m_quitButton.SetPosition(Point(384, 286)); }

		/// <summary> Hides the end screen. </summary>
		void hideEndScreen(Events::EventContext* = NULL) { m_currentState = MenuState::Alive; m_endScreen.SetActive(false); m_quitButton.SetPosition(Point(832, 508)); }
	};
}
#endif