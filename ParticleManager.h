#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

// Data includes.
#include "Point.h"

// Utility includes.
#include "Random.h"

// Typedef includes.
#include <stdint.h>

namespace Particles
{
	/// <summary> Represents a particle manager that allows for particles to be created. </summary>
	class ParticleManager
	{
	public:
		virtual ~ParticleManager() {}

		/// <summary> Creates the given amount of particles at the given position, using the given start and end indices for sprite selection. </summary>
		/// <param name="_position"> The position at which the particles will start. </param>
		/// <param name="_amount"> The amount of particles to add. </param>
		/// <param name="_startSpriteIndex"> The minimum value for the sprite index. </param>
		/// <param name="_endSpriteIndex"> The maximum value for the sprite index. </param>
		virtual void AddParticles(Point _position, uint16_t _amount, uint16_t _startSpriteIndex, uint16_t _endSpriteIndex) = 0;
	};
}
#endif