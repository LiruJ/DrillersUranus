#ifndef SERVICES_H
#define SERVICES_H

#include "Logger.h"
#include "Graphics.h"
#include "Controls.h"
#include "Screen.h"
#include "Events.h"

class Services
{
public:
	virtual ~Services() {}

	virtual Logging::Logger&				GetLogger() = 0;
	virtual Graphics::Graphics&				GetGraphics() = 0;
	virtual Controls::Controls&				GetControls() = 0;
	virtual Screen&							GetScreen() = 0;
	virtual Events&							GetEvents() = 0;
};
#endif