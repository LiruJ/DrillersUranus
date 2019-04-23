#include "Player.h"

/// <summary> Initialises the event bindings. </summary>
/// <param name="_events"> The events service. </param>
void GameObjects::Player::Initialise(Events::Events& _events)
{
	// Bind the gem mined event to add it to the list.
	_events.AddUserListener(Events::UserEvent::MinedGem, std::bind(&Player::minedGem, this, std::placeholders::_1));
}

/// <summary> Fires when a gem is mined, then adds it to the inventory. </summary>
/// <param name="_context"> The context of the event. </param>
void GameObjects::Player::minedGem(Events::EventContext* _context)
{
	// Get the mined gem.
	Minigames::WallGem minedGem = *static_cast<Minigames::WallGem*>(_context->m_data1);

	// Add the gem to the inventory.
	m_inventory.AddMinedGem(minedGem);
}
