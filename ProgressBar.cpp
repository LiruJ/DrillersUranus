#include "ProgressBar.h"

// Data includes.
#include "Rectangle.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

// Typedef includes.
#include <cmath>

/// <summary> Draws this <see cref="ProgressBar"/> onto the screen. </summary>
void UserInterface::ProgressBar::Draw()
{
	// If this progress bar is not active, do nothing.
	if (!m_isActive) { return; }

	// Get the graphics and screen services.
	Graphics::Graphics& graphics = MainGame::Game::GetService().GetGraphics();
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	// Calculate the window bounds then draw.
	Point windowPosition = screen.ScreenToWindowSpace(m_screenPosition);
	Rectangle destRect = Rectangle(windowPosition.x, windowPosition.y, screen.ScreenToWindowSize((int32_t)((float_t)m_screenSize.x * (m_current / (float_t)m_max))), screen.ScreenToWindowSize(m_screenSize.y));
	Rectangle sourceRect = Rectangle(0, 0, (int32_t)((float_t)m_screenSize.x * (m_current / (float_t)m_max)), m_screenSize.y);
	graphics.Draw(SpriteData::SheetID::UI, m_spriteID, destRect, sourceRect);
}