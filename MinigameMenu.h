#ifndef MINIGAME_MENU_H
#define MINIGAME_MENU_H

// UI includes.
#include "ProgressBar.h"
#include "Button.h"
#include "Frame.h"

// Typedef includes.
#include <stdint.h>

namespace UserInterface
{
	/// <summary> Represents the menu for the minigame. </summary>
	class MinigameMenu
	{
	public:
		/// <summary> Creates the basic minigame menu. </summary>
		MinigameMenu() {}

		void Initialise(uint16_t);

		void Draw();
	private:
		/// <summary> The buttom UI behind the buttons and collapse bar. </summary>
		Frame		m_bottomBar;

		/// <summary> The bar of how unstable the wall is. </summary>
		ProgressBar	m_collapseBar;

		/// <summary> The buttons to switch the current tool. </summary>
		Button		m_toolButtons[3];

		/// <summary> Fires when the current tool is changed, hides the tool's button. </summary>
		/// <param name="_toolID"> The new tool ID. </param>
		void toolChanged(void* _toolID, void*) { for (uint8_t i = 0; i < 3; i++) { m_toolButtons[i].SetActive(*static_cast<uint8_t*>(_toolID) != i); } }

		void wallMined(void*, void*);

		/// <summary> Starts the menu and initialises. </summary>
		void start(void*, void*) { m_collapseBar.SetValue(0); }

		/// <summary> Shows this menu. </summary>
		void show(void*, void*) { setActive(true); }

		/// <summary> Hides this menu. </summary>
		void hide(void*, void*) { setActive(false); }

		void setActive(bool);
	};
}
#endif