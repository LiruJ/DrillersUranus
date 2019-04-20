#ifndef SERVICES_H
#define SERVICES_H

// Service includes.
#include "Logger.h"
#include "Graphics.h"
#include "Controls.h"
#include "Screen.h"
#include "Events.h"
#include "Audio.h"
#include "Time.h"
#include "ParticleManager.h"

/// <summary> Represents a service provider only allowing services to be gotten but not set. </summary>
class Services
{
public:
	virtual ~Services() {}

	/// <summary> Gets the logger. </summary>
	/// <returns> The logger. </returns>
	virtual Logging::Logger&	GetLogger() = 0;

	/// <summary> Gets the graphics. </summary>
	/// <returns> The graphics. </returns>
	virtual Graphics::Graphics&	GetGraphics() = 0;

	/// <summary> Gets the controls. </summary>
	/// <returns> The controls. </returns>
	virtual Controls::Controls&	GetControls() = 0;

	/// <summary> Gets the screen. </summary>
	/// <returns> The screen. </returns>
	virtual Screens::Screen&	GetScreen() = 0;

	/// <summary> Gets the events. </summary>
	/// <returns> The events. </returns>
	virtual Events::Events&		GetEvents() = 0;

	/// <summary> Gets the audio. </summary>
	/// <returns> The audio. </returns>
	virtual Audio::Audio&		GetAudio() = 0;

	/// <summary> Gets the time. </summary>
	/// <returns> The time. </returns>
	virtual Time::Time&	GetTime() = 0;

	/// <summary> Gets the particle manager. </summary>
	/// <returns> The particle manager. </returns>
	virtual Particles::ParticleManager& GetParticles() = 0;
};
#endif