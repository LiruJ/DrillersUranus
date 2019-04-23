#include "Minimap.h"

// Data includes.
#include "World.h"
#include "IReadOnlyTileMap.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

/// <summary> Draws the minimap based on the given world. </summary>
/// <param name="_world"> The world. </param>
/// <param name="_services"> The service provider. </param>
void UserInterface::Minimap::Draw(WorldObjects::World& _world, Services::ServiceProvider& _services)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Get the tile map.
	WorldObjects::IReadOnlyTileMap& tileMap = _world.GetTileMap();

	// Calculate the x and y size for a single tile on the minimap.
	float_t tileWidth = (float_t)m_bounds.w / tileMap.GetWidth();
	float_t tileHeight = (float_t)m_bounds.h / tileMap.GetHeight();

	// Go over every tile in the map.
	for (uint8_t x = 0; x < tileMap.GetWidth(); x++)
	{
		for (uint8_t y = 0; y < tileMap.GetHeight(); y++)
		{
			// If the tile is not visible, skip it.
			if (!tileMap.GetTileAt(Point(x, y)).m_visibility) { continue; }

			// Calculate the sprite ID.
			uint16_t spriteID = 0;
			if (tileMap.IsCellBlocked(Point(x, y))) 
			{
				spriteID = (tileMap.GetTileAt(Point(x, y)).m_prosperity > 0) ? SpriteData::MinimapID::LowProsp + (tileMap.GetTileAt(Point(x, y)).m_prosperity / 64) : SpriteData::MinimapID::PlainWall;
			}
			else { spriteID = SpriteData::MinimapID::PlainFloor; }

			// Calculate the window bounds.
			Rectangle windowBounds = screen.ScreenToWindowBounds(Rectangle(Point(x * tileWidth, y * tileHeight) + Point(m_bounds.x, m_bounds.y), Point(ceil(tileWidth), ceil(tileHeight))));

			graphics.Draw(SpriteData::SheetID::Minimap, spriteID, windowBounds);
		}
	}

	// Draw the spawn.
	Rectangle windowBounds = screen.ScreenToWindowBounds(Rectangle(Point(_world.GetSpawn().GetTilePosition().x * tileWidth, _world.GetSpawn().GetTilePosition().y * tileHeight) + Point(m_bounds.x, m_bounds.y), Point(ceil(tileWidth), ceil(tileHeight))));
	graphics.Draw(SpriteData::SheetID::Minimap, SpriteData::MinimapID::SpawnIcon, windowBounds);

	// Draw the exit, if it is visible.
	windowBounds = screen.ScreenToWindowBounds(Rectangle(Point(_world.GetExit().GetTilePosition().x * tileWidth, _world.GetExit().GetTilePosition().y * tileHeight) + Point(m_bounds.x, m_bounds.y), Point(ceil(tileWidth), ceil(tileHeight))));
	if (tileMap.GetTileAt(_world.GetExit().GetTilePosition()).m_visibility) { graphics.Draw(SpriteData::SheetID::Minimap, SpriteData::MinimapID::ExitIcon, windowBounds); }

	// Draw the player.
	windowBounds = screen.ScreenToWindowBounds(Rectangle(Point(_world.GetPlayer().GetTilePosition().x * tileWidth, _world.GetPlayer().GetTilePosition().y * tileHeight) + Point(m_bounds.x, m_bounds.y), Point(ceil(tileWidth), ceil(tileHeight))));
	graphics.Draw(SpriteData::SheetID::Minimap, SpriteData::MinimapID::Player, windowBounds);
}
