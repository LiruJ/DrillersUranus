#ifndef GAMEMENU_H
#define GAMEMENU_H

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

		void Initialise();

		void Draw(WorldObjects::World& _world);
	private:
		/// <summary> The different states of the menu. </summary>
		enum MenuState { Alive, Dead };

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
		void hide(void*, void*) { setActive(false); }

		/// <summary> Shows this menu. </summary>
		void show(void*, void*) { setActive(true); }

		/// <summary> Shows the death screen. </summary>
		void showDeathScreen(void* _unused = NULL, void* _unused2 = NULL) { m_currentState = MenuState::Dead; m_endScreen.SetActive(true); m_quitButton.SetPosition(Point(384, 286)); }

		/// <summary> Hides the death screen. </summary>
		void hideDeathScreen(void* _unused = NULL, void* _unused2 = NULL) { m_currentState = MenuState::Alive; m_endScreen.SetActive(false); m_quitButton.SetPosition(Point(832, 508)); }
	};
}
#endif