#ifndef MININGMINIGAME_H
#define MININGMINIGAME_H

// Data includes.
#include "Direction.h"
#include "Tool.h"
#include "Point.h"
#include "WallData.h"
#include "WallGem.h"

// Service includes.
#include "ServiceProvider.h"
#include "Events.h"
#include "EventContext.h"

// Utility includes.
#include <vector>

// UI includes.
#include "MinigameMenu.h"

// Typedef includes.
#include <stdint.h>

namespace Minigames
{
	/// <summary> Represents the minigame where the player mines for gems. </summary>
	class MiningMinigame
	{
	public:
		/// <summary> Creates the initial minigame. </summary>
		MiningMinigame() : m_collapseTimer(c_maxTimer), m_wallData(120, 60), m_wallGems() { }

		void Initialise(Events::Events&);

		void Draw(Services::ServiceProvider&);

		void Prepare(Services::ServiceProvider&, Point, uint8_t);
	private:
		/// <summary> The tools. </summary>
		static Tool					s_tools[3];

		/// <summary> The maximum timer value. </summary>
		const uint16_t				c_maxTimer = 1500;

		/// <summary> The tile data. </summary>
		WallData					m_wallData;

		/// <summary> The gems within the wall. </summary>
		std::vector<WallGem>		m_wallGems;

		/// <summary> The position of the tile on the map. </summary>
		Point						m_tilePosition;

		/// <summary> Starts at <c>1500</c> and goes down every time the player mines, when it reaches <c>0</c> the wall collapses and the minigame ends. </summary>
		uint16_t					m_collapseTimer;

		/// <summary> The index in the tools array of the currently selected tool. </summary>
		uint8_t						m_currentToolID;

		/// <summary> The menu for the minigame. </summary>
		UserInterface::MinigameMenu m_minigameMenu;

		void placeGems(uint8_t);

		void changeTool(Events::EventContext*);

		void hotkeyTool(Events::EventContext*);

		void mineAt(Events::EventContext*);

		void mined(Events::EventContext*);
	};
}
#endif