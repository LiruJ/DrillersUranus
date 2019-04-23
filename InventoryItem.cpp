#include "InventoryItem.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

/// <summary> Draws this item at the given position. </summary>
/// <param name="_position"> The screen-position at which to draw. </param>
/// <param name="_services"> The service provider. </param>
void Inventory::InventoryItem::Draw(const Point _position, Services::ServiceProvider& _services) const
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Draw the frame and gem.
	graphics.Draw(SpriteData::SheetID::UI, SpriteData::UIID::InventoryFrame, screen.GetScale(), screen.ScreenToWindowSpace(_position));
	graphics.Draw(SpriteData::SheetID::UI, SpriteData::UIID::RubyIcon + m_gemID, screen.GetScale(), screen.ScreenToWindowSpace(_position));

	// Draw the text.
	graphics.DrawString(SpriteData::FontID::SmallDetail, 'x' + std::to_string(m_stackAmount),
		screen.ScreenToWindowSpace(_position + Point(36, 4)), { 224, 224, 224, 255 });
}
