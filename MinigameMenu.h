#ifndef MINIGAME_MENU_H
#define MINIGAME_MENU_H

// Service includes.
#include "ServiceProvider.h"
#include "Events.h"
#include "EventContext.h"

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

		void Initialise(uint16_t, Events::Events&);

		void Draw(Services::ServiceProvider&) const;
	private:
		/// <summary> The buttom UI behind the buttons and collapse bar. </summary>
		Frame		m_bottomBar;

		/// <summary> The bar of how unstable the wall is. </summary>
		ProgressBar	m_collapseBar;

		/// <summary> The buttons to switch the current tool. </summary>
		Button		m_toolButtons[3];

		/// <summary> Fires when the current tool is changed, hides the tool's button. </summary>
		/// <param name="_context"> The context of the event. </param>
		void toolChanged(Events::EventContext* _context) { for (uint8_t i = 0; i < 3; i++) { m_toolButtons[i].SetActive(*static_cast<uint8_t*>(_context->m_data1) != i); } }

		void wallMined(Events::EventContext*);

		/// <summary> Starts the menu and initialises. </summary>
		void start(Events::EventContext* = NULL) { m_collapseBar.SetValue(0); }

		/// <summary> Shows this menu. </summary>
		void show(Events::EventContext* = NULL) { setActive(true); }

		/// <summary> Hides this menu. </summary>
		void hide(Events::EventContext* = NULL) { setActive(false); }

		void setActive(bool);
	};
}
#endif