#include "Frame.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

// Utility includes.
#include "SpriteData.h"

/// <summary> Draws this <see cref="Frame"/> onto the screen. </summary>
/// <param name="_services"> The service provider. </param>
void UserInterface::Frame::Draw(Services::ServiceProvider& _services) const
{
	// If this frame is not active, do nothing.
	if (!m_isActive) { return; }

	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Calculate the screen position and draw.
	graphics.Draw(SpriteData::SheetID::UI, m_spriteID, screen.ScreenToWindowBounds(m_bounds));
}