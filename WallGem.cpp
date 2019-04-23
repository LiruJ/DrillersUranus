#include "WallGem.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

/// <summary> Draws this <see cref="WallGem"/>. </summary>
/// <param name="_services"> The service provider. </param>
void Minigames::WallGem::Draw(Services::ServiceProvider& _services)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Calculate the screen position and draw.
	graphics.Draw(SpriteData::SheetID::Gems, m_gemID,
		Rectangle(screen.ScreenToWindowSpace(m_wallPosition * SpriteData::c_wallSize), screen.ScreenToWindowSize(Point(m_collider.GetWidth(), m_collider.GetHeight()) * SpriteData::c_wallSize)));
}