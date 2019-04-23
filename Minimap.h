#ifndef MINIMAP_H
#define MINIMAP_H

// Service includes.
#include "ServiceProvider.h"

// Data includes.
#include "Rectangle.h"

// Forward declaration.
namespace WorldObjects { class World; }

namespace UserInterface
{
	class Minimap
	{
	public:
		Minimap() : m_bounds(Rectangle(0, 0, 0, 0)) {}
		Minimap(const Rectangle _bounds) : m_bounds(_bounds) {}

		void Draw(WorldObjects::World&, Services::ServiceProvider&);
	private:
		/// <summary> The bounds of the minimap on the screen. </summary>
		Rectangle m_bounds;
	};
}
#endif