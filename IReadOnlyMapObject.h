#ifndef IREADONLYMAPOBJECT_H
#define IREADONLYMAPOBJECT_H

// Data includes.
#include "Point.h"

// Service includes.
#include "ServiceProvider.h"

namespace GameObjects
{
	/// <summary> An interface which only gives access to getters and drawing functions, nothing that can modify the internal data. </summary>
	class IReadOnlyMapObject
	{
	public:
		virtual ~IReadOnlyMapObject() {}

		/// <summary> Draws this object from the given camera position. </summary>
		/// <param name="_cameraPosition"> The position of the camera. </param>
		/// <param name="_services"> The service provider. </param>
		virtual void Draw(Point _cameraPosition, Services::ServiceProvider& _services) = 0;

		/// <summary> Gets the tile position of this object on the map. </summary>
		/// <returns> The tile position of this object on the map. </returns>
		virtual Point GetTilePosition() = 0;
	};
}
#endif