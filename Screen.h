#ifndef SCREEN_H
#define SCREEN_H

// Data includes.
#include "Point.h"

class Screen
{
public:
	virtual ~Screen() {};

	virtual Point ToScreenSpace(Point) = 0;
	virtual Point ToWindowSpace(Point) = 0;

	virtual Point ToScreenSize(Point) = 0;
	virtual int ToScreenSize(int) = 0;

	virtual void Resize(int, int) = 0;
};

#endif