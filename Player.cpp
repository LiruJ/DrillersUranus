#include "Player.h"



Player::Player() : m_facing(Direction(Directions::Up))
{
	m_spriteID = SpriteData::ObjectID::PlayerUp;
}


Player::~Player()
{
}

void Player::MoveInDirection(const Directions _direction)
{
	// Move and face in the direction.
	SetFacing(_direction);
	m_tilePosition += m_facing.GetNormal();


}
