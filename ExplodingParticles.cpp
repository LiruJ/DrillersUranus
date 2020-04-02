#include "ExplodingParticles.h"

// Utility includes.
#include <SDL_stdinc.h>

/// <summary> Deletes the stored particles. </summary>
Particles::ExplodingParticles::~ExplodingParticles()
{
	// Delete all active particles.
	std::vector<Particle*>::iterator activeIterator = m_activeParticles.begin();
	while (activeIterator != m_activeParticles.end())
	{
		delete *activeIterator;
		activeIterator = m_activeParticles.erase(activeIterator);
	}

	// Delete all dead particles.
	std::vector<Particle*>::iterator deadIterator = m_deadParticles.begin();
	while (deadIterator != m_deadParticles.end())
	{
		delete *deadIterator;
		deadIterator = m_deadParticles.erase(deadIterator);
	}
}

/// <summary> Updates the particles based on the time that has passed. </summary>
/// <param name="_gameTime"> The current gametime. </param>
void Particles::ExplodingParticles::Update(Time::DeltaTime& _gameTime)
{
	// Update each particle, if any are below 0 scale after updating, move them to the pool.
	std::vector<Particle*>::iterator activeIterator = m_activeParticles.begin();
	while (activeIterator != m_activeParticles.end())
	{
		// Updates the particle.
		(*activeIterator)->Update(_gameTime);

		// If the scale is at or lower than 0, move it to the dead pool.
		if ((*activeIterator)->m_scale <= 0.0f)
		{
			m_deadParticles.push_back(*activeIterator);
			activeIterator = m_activeParticles.erase(activeIterator);
		}
		else { activeIterator++; }
	}
}

/// <summary> Draws all currently active particles. </summary>
/// <param name="_graphics"> The graphical service used to draw. </param>
/// <param name="_screen"> The screen service used to convert the raw positions. </param>
/// <param name="_offset"> The offset from which to draw the particles, defaults to <c>0</c>, <c>0</c>. </param>
void Particles::ExplodingParticles::Draw(Graphics::Graphics& _graphics, Screens::Screen& _screen, const Point _offset)
{
	// Draw each active particle.
	for (uint16_t i = 0; i < m_activeParticles.size(); i++) { m_activeParticles[i]->Draw(m_sheetID, _graphics, _screen, _offset); }
}

/// <summary> Stops all currently living particles. </summary>
void Particles::ExplodingParticles::KillAllAlive()
{
	// Take each particle from the alive list and add them to the dead list.
	std::vector<Particle*>::iterator activeIterator = m_activeParticles.begin();
	while (activeIterator != m_activeParticles.end())
	{
		m_deadParticles.push_back(*activeIterator);
		activeIterator = m_activeParticles.erase(activeIterator);
	}
}

/// <summary> Creates the given amount of particles at the given position, using the given start and end indices for sprite selection. </summary>
/// <param name="_position"> The position at which the particles will start. </param>
/// <param name="_amount"> The amount of particles to add. </param>
/// <param name="_startSpriteIndex"> The minimum value for the sprite index. </param>
/// <param name="_endSpriteIndex"> The maximum value for the sprite index. </param>
void Particles::ExplodingParticles::AddParticles(const Point _position, const uint16_t _amount, const uint16_t _startSpriteIndex, const uint16_t _endSpriteIndex)
{
	// Repeat for the given amount.
	for (uint16_t i = 0; i < _amount; i++)
	{
		// If there is a particle waiting in the pool, take that, otherwise create it.
		Particle* particle;
		if (m_deadParticles.size() > 0)
		{
			particle = m_deadParticles.back();
			m_deadParticles.pop_back();
		}
		else { particle = new Particle(); }

		// Create the particle and set its position and scale.
		particle->m_position = Vector2(_position.x, _position.y);
 		particle->m_scale = 1.0f;
		
		// Randomise its sprite ID.
		particle->m_spriteID = Random::RandomBetween(_startSpriteIndex, _endSpriteIndex);

		// Randomise its rotation.
		particle->m_rotation = (M_PI * 2.0f) * Random::RandomScalar();
		particle->m_rotationSpeed = ((M_PI * 2.0f) - M_PI) * Random::RandomScalar();

		// Randomise its speed.
		particle->m_speed = Random::RandomBetween(64, 128);

		// Randomise its shrink speed.
		particle->m_scaleSpeed = (Random::RandomScalar() / 4.0f) + 0.75f;

		// Set its direction.
		particle->m_direction = Vector2::fromRadians(particle->m_rotation);

		// Add it to the active particles.
		m_activeParticles.push_back(particle);
	}
}
