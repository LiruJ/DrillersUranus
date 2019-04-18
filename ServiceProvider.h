#ifndef SERVICE_PROVIDER_H
#define SERVICE_PROVIDER_H

// Derived includes.
#include "Services.h"

/// <summary> Represnts a service provider which allows full set and get access. </summary>
class ServiceProvider : public Services
{
public:
	/// <summary> Gets the logger. </summary>
	/// <returns> The logger. </returns>
	inline virtual Logging::Logger&		GetLogger()									{ return *m_logger; }
	
	/// <summary> Sets the logger. </summary>
	/// <param name="_logger"> The logger. </param>
	inline void							SetLogger(Logging::Logger& _logger)			{ m_logger = &_logger; }

	/// <summary> Gets the graphics. </summary>
	/// <returns> The graphics. </returns>
	inline virtual Graphics::Graphics&	GetGraphics()								{ return *m_graphics; }
	
	/// <summary> Sets the graphics. </summary>
	/// <param name="_graphics"> The graphics. </param>
	inline void							SetGraphics(Graphics::Graphics& _graphics)	{ m_graphics = &_graphics; }

	/// <summary> Gets the controls. </summary>
	/// <returns> The controls. </returns>
	inline virtual Controls::Controls&	GetControls()								{ return *m_controls; }
	
	/// <summary> Sets the controls. </summary>
	/// <param name="_controls"> The controls. </param>
	inline void							SetControls(Controls::Controls& _controls)	{ m_controls = &_controls; }

	/// <summary> Gets the screen. </summary>
	/// <returns> The screen. </returns>
	inline virtual Screens::Screen&		GetScreen()									{ return *m_screen; }
	
	/// <summary> Sets the screen. </summary>
	/// <param name="_screen"> The screen. </param>
	inline void							SetScreen(Screens::Screen& _screen)			{ m_screen = &_screen; }

	/// <summary> Gets the events. </summary>
	/// <returns> The events. </returns>
	inline virtual Events::Events&		GetEvents()									{ return *m_events; }
	
	/// <summary> Sets the events. </summary>
	/// <param name="_events"> The events. </param>
	inline void							SetEvents(Events::Events& _events)			{ m_events = &_events; }

	/// <summary> Gets the audio. </summary>
	/// <returns> The audio. </returns>
	inline virtual Audio::Audio&		GetAudio()									{ return *m_audio; }

	/// <summary> Sets the audio. </summary>
	/// <param name="_audio"> The audio. </param>
	inline void							SetAudio(Audio::Audio& _audio)				{ m_audio = &_audio; }
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

	/// <summary> The service used to play audio. </summary>
	Audio::Audio*		m_audio;
};
#endif