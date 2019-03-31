#include "Tile.h"
#include "Game.h"

void Tile::Draw(const Point _tilePosition, const Point _cameraPosition)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = Game::GetService().GetGraphics();
	Screen& screen = Game::GetService().GetScreen();

	uint16_t spriteID = m_ID;

	if (m_prosperity > 0 && m_prosperity <= 64) { spriteID = SpriteData::LowGems; }
	else if (m_prosperity > 65 && m_prosperity <= 128) { spriteID = SpriteData::MediumGems; }
	else if (m_prosperity > 129 && m_prosperity <= 192) { spriteID = SpriteData::HighGems; }
	else if (m_prosperity > 193) { spriteID = SpriteData::MaxGems; }

	// Calculate the screen position and draw.
	Point screenPosition = screen.WindowToScreenSpace((_tilePosition * SpriteData::c_tileSize) - _cameraPosition);
	graphics.Draw(SpriteData::Tiles, spriteID, Rectangle(screenPosition, screen.WindowToScreenSize(SpriteData::c_tileSize)));
}