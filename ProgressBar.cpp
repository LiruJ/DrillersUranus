#include "ProgressBar.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

// Graphical includes.
#include "Rectangle.h"

// Typedef includes.
#include <cmath>

void UserInterface::ProgressBar::Draw()
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = Game::GetService().GetGraphics();
	Screen& screen = Game::GetService().GetScreen();

	// Calculate the screen position and draw.
	Point screenPosition = screen.WindowToScreenSpace(m_windowPosition);
	Rectangle destRect = Rectangle(screenPosition.x, screenPosition.y, screen.WindowToScreenSize(m_windowSize.x * (int32_t)(m_current / (float_t)m_max)), screen.WindowToScreenSize(m_windowSize.y));
	Rectangle sourceRect = Rectangle(0, 0, m_windowSize.x * (int32_t)(m_current / (float_t)m_max), m_windowSize.y);
	graphics.Draw(SpriteData::SheetID::UI, m_spriteID, destRect, sourceRect);
}