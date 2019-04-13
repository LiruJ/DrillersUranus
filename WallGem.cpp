#include "WallGem.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

/// <summary> Draws this <see cref="WallGem"/>. </summary>
void Minigames::WallGem::Draw()
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = MainGame::Game::GetService().GetGraphics();
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	// Calculate the screen position and draw.
	graphics.Draw(SpriteData::SheetID::Gems, m_gemID,
		Rectangle(screen.ScreenToWindowSpace(m_wallPosition * SpriteData::c_wallSize), screen.ScreenToWindowSize(Point(m_collider.GetWidth(), m_collider.GetHeight()) * SpriteData::c_wallSize)));
}