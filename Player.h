#ifndef PLAYER_H
#define PLAYER_H

// Inheritance includes.
#include "MapObject.h"

// Data includes.
#include "Direction.h"

class Player :
	public MapObject
{
public:
	Player();
	~Player();

	void MoveInDirection(Directions);

	inline void SetFacing(const Directions _direction)			{ m_facing = Direction(_direction); m_spriteID = SpriteData::PlayerLeft + _direction; }
	inline Direction GetFacing()						const	{ return m_facing; }
private:
	Direction m_facing;
};
#endif