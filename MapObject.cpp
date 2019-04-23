#include "MapObject.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

// Data includes.
#include "Rectangle.h"

/// <summary> Draws this <see cref="MapObject"/> from the given camera position. </summary>
/// <param name="_cameraPosition"> The position of the camera. </param>
/// <param name="_services"> The service provider. </param>
void GameObjects::MapObject::Draw(const Point _cameraPosition, Services::ServiceProvider& _services)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Calculate the screen position and draw.
	graphics.Draw(SpriteData::SheetID::Objects, m_spriteID, Rectangle(screen.ScreenToWindowSpace((m_tilePosition * SpriteData::c_tileSize) - _cameraPosition), screen.ScreenToWindowSize(Point(SpriteData::c_tileSize))));
}
