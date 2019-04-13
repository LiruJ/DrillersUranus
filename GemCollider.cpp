#include "GemCollider.h"

// Data includes.
#include "Rectangle.h"

bool Minigames::GemCollider::CollidesWith(const Point _position, const GemCollider _other) const
{
	// If the two gems don't intersect at all regardless of data, there is no collision.
	if (!Rectangle(0, 0, m_width, m_height).Intersects(Rectangle(_position, Point(_other.m_width, _other.m_height)))) { return false; }

	// Only check the x range of the intersecting area of the rectangles.
	for (uint32_t x = std::max(0, _position.x), otherX = std::abs(std::min(0, _position.x)); x < std::min((int32_t)m_width, _position.x + _other.m_width); x++, otherX++)
	{
		// If the two starts and heights intersect at all, there is a collision.
		if (CollidesWith(Point(x, _other.getColumnStart(otherX) + _position.y)) || _other.CollidesWith(Point(otherX, getColumnStart(x) - _position.y))) { return true; }
	}

	// If no collision was found, return false.
	return false;
}

bool Minigames::GemCollider::IsFullyCovered(const Point _position, const uint8_t _layer, WallData& _wallData) const
{
	// Go over each tile within the collider, if any are below the given layer, return false
	for (uint8_t x = 0; x < m_width; x++)
	{
		for (uint8_t y = getColumnStart(x); y < getColumnHeight(x); y++)
		{
			if (_wallData.GetValueAt(_position.x + x, _position.y + y) < _layer) { return false; }
		}
	}

	// Since no uncovered tile was found, return true.
	return true;
}

bool Minigames::GemCollider::IsFullyUncovered(const Point _position, const uint8_t _layer, WallData& _wallData) const
{
	// Go over each tile within the collider, if any are above or at the given layer, return false
	for (uint8_t x = 0; x < m_width; x++)
	{
		for (uint8_t y = getColumnStart(x); y < getColumnHeight(x); y++)
		{
			if (_wallData.GetValueAt(_position.x + x, _position.y + y) >= _layer) { return false; }
		}
	}

	// Since no covered tile was found, return true.
	return true;
}

// Initialise the colliders.
Minigames::GemCollider::colliders Minigames::GemCollider::s_colliders = Minigames::GemCollider::colliders();