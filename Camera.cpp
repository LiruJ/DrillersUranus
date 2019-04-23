#include "Camera.h"

// Data includes.
#include "World.h"
#include "IReadOnlyTileMap.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

// Utility includes.
#include "SpriteData.h"

/// <summary> Draws the given world from the <see cref="Camera"/>'s perspective. </summary>
/// <param name="_world"> The world to draw. </param>
/// <param name="_services"> The service provider. </param>
void WorldObjects::Camera::Draw(World& _world, Services::ServiceProvider& _services)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Get the tiledata.
	IReadOnlyTileMap& tileMap = _world.GetTileMap();

	// Centre on the player.
	centreOnMapObject(_world.GetPlayer());

	// Draw the map data based on the visible area of the camera.
	for (int32_t x = std::max(0, m_worldPosition.x / SpriteData::c_tileSize); x < std::min((int32_t)tileMap.GetWidth(), ((m_worldPosition.x + 832) / SpriteData::c_tileSize) + 1); x++)
	{
		for (int32_t y = std::max(0, m_worldPosition.y / SpriteData::c_tileSize); y < std::min((int32_t)tileMap.GetHeight(), ((m_worldPosition.y + m_worldSize.y) / SpriteData::c_tileSize) + 1); y++)
		{
			// If the tile is not visible, skip it.
			if (!tileMap.GetTileAt(Point(x, y)).m_visibility) { continue; }

			// Calculate the window position.
			Point windowPosition = screen.ScreenToWindowSpace((Point(x, y) * SpriteData::c_tileSize) - m_worldPosition);

			// Calculate the sprite ID by the prosperity.
			uint16_t spriteID = tileMap.GetTileAt(Point(x, y)).m_ID;
			if (tileMap.GetTileAt(Point(x, y)).m_prosperity > 0) { spriteID = SpriteData::TileID::LowGems + (tileMap.GetTileAt(Point(x, y)).m_prosperity / 64); }

			// Draw the tile.
			graphics.Draw(SpriteData::SheetID::Tiles, spriteID, Rectangle(windowPosition, screen.ScreenToWindowSize(SpriteData::c_tileSize)));
		}
	}

	// Draw the spawn and exit points if they're on screen.
	if (isOnScreen(_world.GetSpawn())) { _world.GetSpawn().Draw(m_worldPosition, _services); }
	if (isOnScreen(_world.GetExit()) && tileMap.GetTileAt(_world.GetExit().GetTilePosition()).m_visibility) { _world.GetExit().Draw(m_worldPosition, _services); }

	// Draw the player.
	_world.GetPlayer().Draw(m_worldPosition, _services);

	// Draw the UI.
	m_gameMenu.Draw(_world, _services);
}