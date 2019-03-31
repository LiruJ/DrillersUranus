#include "ProgressBar.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

// Graphical includes.
#include "Rectangle.h"

void UserInterface::ProgressBar::Draw()
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = Game::GetService().GetGraphics();
	Screen& screen = Game::GetService().GetScreen();

	// Calculate the screen position and draw.
	Point screenPosition = screen.ToScreenSpace(m_windowPosition);
	Rectangle destRect = Rectangle(screenPosition.x, screenPosition.y, screen.ToScreenSize(m_windowSize.x * (m_current / (float)m_max)), screen.ToScreenSize(m_windowSize.y));
	Rectangle sourceRect = Rectangle(0, 0, m_windowSize.x * (m_current / (float)m_max), m_windowSize.y);
	graphics.Draw(SpriteData::SheetID::UI, m_spriteID, destRect, sourceRect);
}