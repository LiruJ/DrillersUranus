#ifndef IREADONLYMAPOBJECT_H
#define IREADONLYMAPOBJECT_H

// Data includes.
#include "Point.h"

/// <summary> An interface which only gives access to getters and drawing functions, nothing that can modify the internal data. </summary>
class IReadOnlyMapObject
{
public:
	virtual ~IReadOnlyMapObject() {}

	virtual void Draw(Point) = 0;

	virtual Point GetTilePosition() = 0;
};
#endif