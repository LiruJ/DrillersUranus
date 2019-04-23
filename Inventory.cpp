#include "Inventory.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

/// <summary> Adds the given gem to the inventory. </summary>
/// <param name="_minedGem"> The gem to add. </param>
void Inventory::Inventory::AddMinedGem(const Minigames::WallGem _minedGem)
{
	// If this gem already exists within the inventory, add it to the stack, otherwise, create a new entry for it.
	if (m_inventoryItems.count(_minedGem.GetID()) > 0) { m_inventoryItems[_minedGem.GetID()].AddToStack(); }
	else { m_inventoryItems.emplace(_minedGem.GetID(), _minedGem); }
}

/// <summary> Caclulates the total worth of every gem in the inventory. </summary>
/// <returns> The total worth. </returns>
uint32_t Inventory::Inventory::CalculateCombinedValue()
{
	// Keep track of the sum.
	uint32_t sum = 0;

	// Go through each item.
	std::map<SpriteData::GemID, InventoryItem>::iterator itemIterator = m_inventoryItems.begin();
	while (itemIterator != m_inventoryItems.end())
	{
		// Add to the sum and increment the iterator.
		sum += itemIterator->second.CalculateStackValue();
		++itemIterator;
	}

	// Return the final sum.
	return sum;
}

/// <summary> Draws the contents of the inventory from the given position on the screen. </summary>
/// <param name="_position"> The position from which to draw. </param>
/// <param name="_services"> The service provider. </param>
void Inventory::Inventory::Draw(const Point _position, Services::ServiceProvider& _services)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Start drawing items at the given position.
	Point currentPosition = _position;
	std::map<SpriteData::GemID, InventoryItem>::iterator itemIterator = m_inventoryItems.begin();
	while (itemIterator != m_inventoryItems.end())
	{
		// Draw the item at the given position.
		itemIterator->second.Draw(currentPosition, _services);

		// Move the position down and increment the iterator.
		currentPosition.y += 32;
		++itemIterator;
	}
}