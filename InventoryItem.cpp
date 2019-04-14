#include "InventoryItem.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

/// <summary> Draws this item at the given position. </summary>
/// <param name="_position"> The screen-position at which to draw. </param>
void Inventory::InventoryItem::Draw(const Point _position) const
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = MainGame::Game::GetService().GetGraphics();
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	// Draw the frame and gem.
	graphics.Draw(SpriteData::SheetID::UI, SpriteData::UIID::InventoryFrame, screen.GetScale(), screen.ScreenToWindowSpace(_position));
	graphics.Draw(SpriteData::SheetID::UI, SpriteData::UIID::RubyIcon + m_gemID, screen.GetScale(), screen.ScreenToWindowSpace(_position));
}
