#include "Inventory.h"

// Service includes.
#include "Game.h"
#include "Graphics.h"
#include "Screen.h"

void Inventory::Inventory::AddMinedGem(const Minigames::WallGem _minedGem)
{
	// If this gem already exists within the inventory, add it to the stack, otherwise, create a new entry for it.
	if (m_inventoryItems.count(_minedGem.GetID()) > 0) { m_inventoryItems[_minedGem.GetID()].AddToStack(); }
	else { m_inventoryItems.emplace(_minedGem.GetID(), _minedGem); }
}

void Inventory::Inventory::Draw(const Point _position)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = MainGame::Game::GetService().GetGraphics();
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	// Start drawing items at the given position.
	Point currentPosition = _position;
	std::map<SpriteData::GemID, InventoryItem>::iterator itemIterator = m_inventoryItems.begin();
	while (itemIterator != m_inventoryItems.end())
	{
		// Draw the item at the given position.
		itemIterator->second.Draw(currentPosition);

		// Move the position down and increment the iterator.
		currentPosition.y += 32;
		++itemIterator;
	}

}