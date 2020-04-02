#ifndef EXPLODINGPARTICLES_H
#define EXPLODINGPARTICLES_H

// Derived includes.
#include "ParticleManager.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"
#include "Time.h"

// Data includes.
#include "Particle.h"
#include "Point.h"

// Utility includes.
#include <vector>

namespace Particles
{
	/// <summary> Represents a particle manager where the particles explode outwards from their starting point. </summary>
	class ExplodingParticles : public ParticleManager
	{
	public:
		~ExplodingParticles();

		ExplodingParticles() : m_activeParticles(std::vector<Particle*>()), m_deadParticles(std::vector<Particle*>()) { }

		void Update(Time::DeltaTime&);

		void Draw(Graphics::Graphics&, Screens::Screen&, Point = Point(0));

		void KillAllAlive();

		/// <summary> Sets the sheet ID to be used. </summary>
		/// <param name="_sheetID"> The sheet ID. </param>
		inline void SetSheetID(const uint16_t _sheetID) { m_sheetID = _sheetID; }

		virtual void AddParticles(Point, uint16_t, uint16_t, uint16_t);
	private:
		/// <summary> The ID of the sheet where the particles are stored. </summary>
		uint16_t m_sheetID;

		/// <summary> The currently active particles. </summary>
		std::vector<Particle*> m_activeParticles;

		/// <summary> The pool of available particles. </summary>
		std::vector<Particle*> m_deadParticles;
	};
}
#endif