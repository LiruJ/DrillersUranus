#ifndef MININGMINIGAME_H
#define MININGMINIGAME_H

// UI includes.
#include "ProgressBar.h"
#include "Button.h"

// Data includes.
#include "Direction.h"
#include "Tool.h"
#include "Point.h"

namespace Minigames
{
	class MiningMinigame
	{
	public:
		MiningMinigame() : m_currentToolID(2), m_collapseTimer(c_maxTimer) { }

		void Initialise();

		void Draw();

		void Generate(Point, uint8_t);

	private:
		/// <summary> The tools. </summary>
		static Tool					s_tools[3];

		/// <summary> The width of the wall in tiles. </summary>
		static const uint8_t	c_wallWidth = 120;

		/// <summary> The height of the wall in tiles. </summary>
		static const uint8_t	c_wallHeight = 60;

		const uint16_t		c_maxTimer = 1000;

		/// <summary> The chance for a bump to go down one layer, set really low as this is rolled a lot. <c>0</c> for no chance, <c>1</c> for full chance. </summary>
		const float					c_downChance = 0.001f;

		/// <summary> The most attempts that will be made to place a tile at a given layer. </summary>
		const uint16_t		c_maxAttempts = 20000;

		/// <summary> The max amount of allowed tiles. </summary>
		const uint8_t			c_maxHeight = 13;

		/// <summary> The layer to which the minigame resets. </summary>
		const uint8_t			c_minimumHeight = 3;

		/// <summary> The tile data. </summary>
		uint8_t				m_wallData[c_wallWidth][c_wallHeight];

		/// <summary> The position of the tile on the map. </summary>
		Point						m_tilePosition;

		/// <summary> Starts at <c>1000</c> and goes down every time the player mines, when it reaches <c>0</c> the wall collapses and the minigame ends. </summary>
		uint16_t				m_collapseTimer;

		/// <summary> The index in the tools array of the currently selected tool. </summary>
		uint8_t				m_currentToolID;

		/// <summary> The buttom UI behind the buttons and collapse bar. </summary>
		UserInterface::Frame		m_bottomBar;

		/// <summary> The bar of how unstable the wall is. </summary>
		UserInterface::ProgressBar	m_collapseBar;

		/// <summary> The buttons to switch the current tool. </summary>
		UserInterface::Button		m_toolButtons[3];

		void initialiseGui();

		void generateBump(uint8_t);

		bool isInRange(const Point _position) { return _position.x >= 0 && _position.x < c_wallWidth && _position.y >= 0 && _position.y < c_wallHeight; }

		void changeTool(void*, void*);

		void mineAt(void*, void*);

		void reset();
	};
}
#endif