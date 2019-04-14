#include "Player.h"

// Service includes.
#include "Game.h"
#include "Events.h"

void GameObjects::Player::Initialise()
{
	// Get the event service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind the gem mined event to add it to the list.
	events.AddUserListener(Events::UserEvent::MinedGem, std::bind(&Player::minedGem, this, std::placeholders::_1, std::placeholders::_2));
}

void GameObjects::Player::minedGem(void* _minedGem, void* _unused)
{
	// Get the mined gem.
	Minigames::WallGem minedGem = *static_cast<Minigames::WallGem*>(_minedGem);

	// Add the gem to the inventory.
	m_inventory.AddMinedGem(minedGem);
}
