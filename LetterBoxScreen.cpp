#include "LetterBoxScreen.h"

// Framework includes.
#include <SDL_stdinc.h>

// Utility includes.
#include "Random.h"

/// <summary> Shakes the screen with the given strength in pixels. </summary>
/// <param name="_strength"> The maximum amount in pixels that the screen will move. </param>
void Screens::LetterBoxScreen::ShakeScreen(const uint16_t _strength)
{
	// If the given strength is below the minimum, stop shaking; otherwise, start shaking at the given strength.
	if (_strength <= c_minimumStrength)
	{
		m_currentStrength = 0;
		m_offset = Point(0);
	}
	else
	{
		// Set the current strenth to the given value.
		m_currentStrength = _strength;

		// Create a random direction and store it.
		m_currentDirection = M_PI * 2.0f * Random::RandomScalar();
	}
}

/// <summary> Updates the screen and the shake effect. </summary>
/// <param name="_gameTime"> The current game time. </param>
void Screens::LetterBoxScreen::Update(Time::Time& _gameTime)
{
	// If there is no strength, don't shake the screen at all.
	if (m_currentStrength <= 0) { return; }

	// Set the offset based on the current direction.
	Vector2 calculatedOffset = Vector2::fromRadians(m_currentDirection) * m_currentStrength;
	m_offset = Point((float_t)calculatedOffset.x, (float_t)calculatedOffset.y);

	// Create a random direction based off the previous.
	m_currentDirection += (M_PI * 0.75f) + ((M_PI / 2.0f) * Random::RandomScalar());

	// Reduce the strength per second.
	m_currentStrength *= 1.0f - (c_strengthDecay *_gameTime.GetDeltaTimeS());

	// if the strength is below a certain point, set it to 0.
	if (m_currentStrength <= c_minimumStrength)
	{
		m_currentStrength = 0;
		m_offset = Point(0);
	}
}

/// <summary> Changes the size of the <see cref="Screen"/> based on the new size of the window. </summary>
/// <param name="_newX"> The new width of the window. </param>
/// <param name="_newY"> The new height of the window. </param>
void Screens::LetterBoxScreen::Resize(const int32_t _newX, const int32_t _newY)
{
	// Divide the new screen size by the aspect ratio.
	float_t ratioX = _newX / (float_t)c_aspectRatio.x;
	float_t ratioY = _newY / (float_t)c_aspectRatio.y;

	// Resize the output, rescale, and reposition based on the smallest dimension of the screen relative to the aspect ratio.
	if (ratioX < ratioY)
	{
		m_size = Point((float_t)_newX, ratioX * c_aspectRatio.y);
		m_scale = ratioX / (c_designDimensions.x / (float_t)c_aspectRatio.x);
		m_position = Point(0, (_newY - m_size.y) / 2);
	}
	else
	{
		m_size = Point(ratioY * c_aspectRatio.x, (float_t)_newY);
		m_scale = ratioY / (c_designDimensions.y / (float_t)c_aspectRatio.y);
		m_position = Point((_newX - m_size.x) / 2, 0);
	}
}