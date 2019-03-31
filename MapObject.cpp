#include "MapObject.h"

// Graphical includes.
#include "Graphics.h"
#include "Screen.h"

// Data includes.
#include "Game.h"
#include "Rectangle.h"

void MapObject::Draw(const Point _cameraPosition)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = Game::GetService().GetGraphics();
	Screen& screen = Game::GetService().GetScreen();

	// Calculate the screen position and draw.
	Point screenPosition = screen.WindowToScreenSpace((m_tilePosition * SpriteData::c_tileSize) - _cameraPosition);
	graphics.Draw(SpriteData::SheetID::Objects, m_spriteID, Rectangle(screenPosition, screen.WindowToScreenSize(Point(SpriteData::c_tileSize))));
}
