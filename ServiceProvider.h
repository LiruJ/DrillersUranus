#ifndef SERVICE_PROVIDER_H
#define SERVICE_PROVIDER_H

#include "Services.h"

class ServiceProvider : public Services
{
public:
	virtual inline Logging::Logger&										GetLogger()														{ return *m_logger; }
	inline void															SetLogger(Logging::Logger& _logger)								{ m_logger = &_logger; }

	virtual inline Graphics::Graphics&									GetGraphics()													{ return *m_graphics; }
	inline void															SetGraphics(Graphics::Graphics& _graphics)						{ m_graphics = &_graphics; }

	virtual inline Controls::Controls&									GetControls()													{ return *m_controls; }
	inline void															SetControls(Controls::Controls& _controls)						{ m_controls = &_controls; }

	virtual inline Screens::Screen&										GetScreen()														{ return *m_screen; }
	inline void															SetScreen(Screens::Screen& _screen)								{ m_screen = &_screen; }

	virtual inline Events::Events&										GetEvents()														{ return *m_events; }
	inline void															SetEvents(Events::Events& _events)								{ m_events = &_events; }
private:
	/// <summary> The service used for logging game data. </summary>
	Logging::Logger*	m_logger;

	/// <summary> The service used for holding and drawing graphical information. </summary>
	Graphics::Graphics* m_graphics;

	/// <summary> The service used for remapping and holding keys. </summary>
	Controls::Controls* m_controls;

	/// <summary> The service used for positioning the graphics onto the screen. </summary>
	Screens::Screen*	m_screen;

	/// <summary> The service used for pushing events onto the event bus. </summary>
	Events::Events*		m_events;
};
#endif