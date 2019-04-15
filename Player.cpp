#include "Player.h"

// Service includes.
#include "Game.h"
#include "Events.h"

/// <summary> Initialises the event bindings. </summary>
void GameObjects::Player::Initialise()
{
	// Get the event service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind the gem mined event to add it to the list.
	events.AddUserListener(Events::UserEvent::MinedGem, std::bind(&Player::minedGem, this, std::placeholders::_1, std::placeholders::_2));
}

/// <summary> Fires when a gem is mined, then adds it to the inventory. </summary>
/// <param name="_minedGem"> The mined gem. </param>
/// <param name="_unused"> Unused. </param>
void GameObjects::Player::minedGem(void* _minedGem, void* _unused)
{
	// Get the mined gem.
	Minigames::WallGem minedGem = *static_cast<Minigames::WallGem*>(_minedGem);

	// Add the gem to the inventory.
	m_inventory.AddMinedGem(minedGem);
}
