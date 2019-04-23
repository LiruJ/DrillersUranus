#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

// Data includes.
#include "WallGem.h"
#include "Point.h"

// Service includes.
#include "ServiceProvider.h"

// Utility includes.
#include "SpriteData.h"

// Typedef includes.
#include <stdint.h>

namespace Inventory
{
	/// <summary> Represents a stack of gems in the inventory. </summary>
	class InventoryItem
	{
	public:
		/// <summary> Creates an empty <see cref="InventoryItem"/>. </summary>
		InventoryItem() {}

		/// <summary> Creates a new <see cref="InventoryItem"/> from the given <see cref="WallGem"/>. </summary>
		/// <param name="_gem"> The <see cref="WallGem"/> this <see cref="InventoryItem"/> will represent. </param>
		InventoryItem(const Minigames::WallGem _gem) : m_gemID(_gem.GetID()), m_stackAmount(1), m_singleValue(_gem.GetValue()) {}

		/// <summary> Increments the amount of gems in this stack by <c>1</c>. </summary>
		inline void AddToStack() { m_stackAmount++; }

		/// <summary> Calculates the value of the entire stack. </summary>
		/// <returns> The value of the entire stack. </returns>
		inline uint32_t CalculateStackValue() const { return m_stackAmount * m_singleValue; }

		void Draw(Point, Services::ServiceProvider&) const;
	private:
		/// <summary> The ID of the <see cref="WallGem"/> that this <see cref="InventoryItem"/> represents. </summary>
		SpriteData::GemID m_gemID;

		/// <summary> The quantity of items that this <see cref="InventoryItem"/> represents. </summary>
		uint16_t m_stackAmount;

		/// <summary> The value of a single instance of this <see cref="InventoryItem"/>. </summary>
		uint16_t m_singleValue;
	};
}
#endif