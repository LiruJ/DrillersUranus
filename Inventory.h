#ifndef INVENTORY_H
#define INVENTORY_H

// Data includes.
#include "InventoryItem.h"
#include "WallGem.h"
#include "Point.h"

// Service includes.
#include "ServiceProvider.h"

// Utility includes.
#include <map>
#include "SpriteData.h"

// Typedef includes.
#include <stdint.h>

namespace Inventory
{
	/// <summary> Represents an inventory of items. </summary>
	class Inventory
	{
	public:
		Inventory() : m_inventoryItems(std::map<SpriteData::GemID, InventoryItem>()) {}

		void AddMinedGem(Minigames::WallGem);

		/// <summary> Completely clears out the inventory. </summary>
		inline void Reset() { m_inventoryItems.clear(); }

		uint32_t CalculateCombinedValue();

		void Draw(Point, Services::ServiceProvider&);
	private:
		/// <summary> The collection of <see cref="InventoryItem"/>s. </summary>
		std::map<SpriteData::GemID, InventoryItem> m_inventoryItems;
	};
}
#endif