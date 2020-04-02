#ifndef PARTICLE_H
#define PARTICLE_H

// Data includes.
#include "Vector2.h"

// Service includes.
#include "Time.h"
#include "Graphics.h"
#include "Screen.h"

// Typedef includes.
#include <cmath>
#include <stdint.h>

namespace Particles
{
	/// <summary> Represents a particle that moves every frame. </summary>
	struct Particle
	{
		/// <summary> The ID for the sprite. </summary>
		uint16_t m_spriteID;

		/// <summary> The current position. </summary>
		Vector2 m_position;

		/// <summary> The direction of movement. </summary>
		Vector2 m_direction;

		/// <summary> The speed per second in pixels. </summary>
		uint8_t m_speed;

		/// <summary> The rotation in radians. </summary>
		float_t m_rotation;

		/// <summary> The radians applied to the rotation every second. </summary>
		float_t m_rotationSpeed;

		/// <summary> A value from <c>1</c> to <c>0</c> of how large this particle is. </summary>
		float_t m_scale;

		/// <summary> How much scale is lost per second. </summary>
		float_t m_scaleSpeed;

		void Update(Time::DeltaTime&);

		void Draw(uint16_t, Graphics::Graphics&, Screens::Screen&, Point = Point(0));
	};
}
#endif