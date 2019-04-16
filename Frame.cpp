#include "Frame.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

/// <summary> Draws this <see cref="Frame"/> onto the screen. </summary>
void UserInterface::Frame::Draw()
{
	// If this frame is not active, do nothing.
	if (!m_isActive) { return; }

	// Get the graphics and screen services.
	Graphics::Graphics& graphics = MainGame::Game::GetService().GetGraphics();
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	// Calculate the screen position and draw.
	graphics.Draw(SpriteData::SheetID::UI, m_spriteID, screen.ScreenToWindowBounds(m_screenBounds));
}