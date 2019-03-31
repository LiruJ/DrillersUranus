#include "Frame.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

// Data includes.
#include "Rectangle.h"

void UserInterface::Frame::Draw()
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = Game::GetService().GetGraphics();
	Screen& screen = Game::GetService().GetScreen();

	// Calculate the screen position and draw.
	graphics.Draw(SpriteData::SheetID::UI, m_spriteID, Rectangle(screen.WindowToScreenSpace(m_windowPosition), screen.WindowToScreenSize(m_windowSize)));
}