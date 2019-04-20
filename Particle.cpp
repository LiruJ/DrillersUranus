#include "Particle.h"

/// <summary> Updates the movement, rotation, and scale of this particle based on the time that has passed. </summary>
/// <param name="_time"> The current gametime. </param>
void Particles::Particle::Update(Time::Time& _gameTime)
{
	// Change the rotation based on the speed.
	m_rotation += m_rotationSpeed * _gameTime.GetDeltaTimeS();

	// Change te position based on the speed.
	m_position += m_direction * m_speed * _gameTime.GetDeltaTimeS();

	// Change the scale.
	m_scale -= m_scaleSpeed * _gameTime.GetDeltaTimeS();
}

/// <summary> Draws this particle. </summary>
/// <param name="_sheetID"> The ID of the sheet that contains the graphic. </param>
/// <param name="_graphics"> The graphics service. </param>
/// <param name="_screen"> The screen service. </param>
void Particles::Particle::Draw(const uint16_t _sheetID, Graphics::Graphics& _graphics, Screens::Screen& _screen, const Point _offset)
{
	// Calculate the window position.
	Point windowPosition = _screen.ScreenToWindowSpace(Point((float_t)m_position.x, (float_t)m_position.y) - _offset);

	// Draw at the calculated position.
	_graphics.Draw(_sheetID, m_spriteID, windowPosition, m_scale * _screen.GetScale(), m_rotation);
}