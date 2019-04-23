#include "ProgressBar.h"

// Data includes.
#include "Rectangle.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

// Utility includes.
#include "SpriteData.h"

// Typedef includes.
#include <cmath>

/// <summary> Draws this <see cref="ProgressBar"/> onto the screen. </summary>
/// <param name="_services"> The service provider. </param>
void UserInterface::ProgressBar::Draw(Services::ServiceProvider& _services) const
{
	// If this progress bar is not active, do nothing.
	if (!m_isActive) { return; }

	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Calculate the window bounds then draw.
	Point windowPosition = screen.ScreenToWindowSpace(m_position);
	Rectangle destRect = Rectangle(windowPosition.x, windowPosition.y, screen.ScreenToWindowSize((int32_t)((float_t)m_size.x * (m_current / (float_t)m_max))), screen.ScreenToWindowSize(m_size.y));
	Rectangle sourceRect = Rectangle(0, 0, (int32_t)((float_t)m_size.x * (m_current / (float_t)m_max)), m_size.y);
	graphics.Draw(SpriteData::SheetID::UI, m_spriteID, destRect, sourceRect);
}