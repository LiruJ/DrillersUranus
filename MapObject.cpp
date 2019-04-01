#include "MapObject.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

// Data includes.
#include "Rectangle.h"

/// <summary> Draws this <see cref="MapObject"/> from the given camera position. </summary>
/// <param name="_cameraPosition"> The position of the camera. </param>
void GameObjects::MapObject::Draw(const Point _cameraPosition)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = MainGame::Game::GetService().GetGraphics();
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	// Calculate the screen position and draw.
	graphics.Draw(SpriteData::SheetID::Objects, m_spriteID, Rectangle(screen.ScreenToWindowSpace((m_tilePosition * SpriteData::c_tileSize) - _cameraPosition), screen.ScreenToWindowSize(Point(SpriteData::c_tileSize))));
}
