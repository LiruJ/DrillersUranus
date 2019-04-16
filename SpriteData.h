#ifndef SPRITEDATA_H
#define SPRITEDATA_H

// Utility includes.
#include "Random.h"

/// <summary> Represents data about the sprite sheets used by the game. </summary>
namespace SpriteData
{
	/// <summary> The width and height of a tile. </summary>
	const int32_t c_tileSize = 16;

	/// <summary> The width and height of a minigame wall tile. </summary>
	const int32_t c_wallSize = 8;

	/// <summary> The ID of each sprite sheet. </summary>
	enum SheetID { Tiles = 0, Inventory, Objects, MineWalls, UI, Gems };

	/// <summary> The ID of each map object. </summary>
	enum ObjectID { Exit = 0, Spawn, PlayerLeft = 4, PlayerUp, PlayerRight, PlayerDown };

	/// <summary> The ID of each UI element. </summary>
	enum UIID { SideBar = 0, MinigameBar, WallTimer, Pickaxe, Shovel, Hammer, InventoryFrame, RubyIcon, DiamondIcon, SapphireIcon, EmeraldIcon, MenuBackground, PlayButton, HelpButton, QuitButton, BackButton, MenuButton, HelpScreen, DeathScreen };

	/// <summary> The ID of each font. </summary>
	enum FontID { Menu = 0, SmallDetail };

	/// <summary> The ID of the tiles. </summary>
	enum TileID { Wall1 = 0, Wall2, Wall3, Wall4, LowGems, MediumGems, HighGems, MaxGems, Floor1, Floor2, Floor3, Floor4 };

	/// <summary> The ID of each gem in the minigame. </summary>
	enum GemID { Ruby = 0, Diamond, Sapphire, Emerald };

	/// <summary> Finds if the given ID is that of any type of wall. </summary>
	/// <param name="_ID"> The ID of the tile to check. </param>
	/// <returns> <c>true</c> if the tile is a wall, <c>false</c> otherwise. </returns>
	inline bool		IsWall(const uint16_t _ID)		{ return _ID >= (int32_t)TileID::Wall1		&& _ID <= (int32_t)TileID::HighGems; }

	/// <summary> Finds if the given ID is that of a plain wall. </summary>
	/// <param name="_ID"> The ID of the tile to check. </param>
	/// <returns> <c>true</c> if the tile is a plain wall, <c>false</c> otherwise. </returns>
	inline bool		IsPlainWall(const uint16_t _ID)	{ return _ID >= (int32_t)TileID::Wall1		&& _ID <= (int32_t)TileID::Wall4; }

	/// <summary> Finds if the given ID is that of a gem wall. </summary>
	/// <param name="_ID"> The ID of the tile to check. </param>
	/// <returns> <c>true</c> if the tile is a gem wall, <c>false</c> otherwise. </returns>
	inline bool		IsGemWall(const uint16_t _ID)		{ return _ID >= (int32_t)TileID::LowGems	&& _ID <= (int32_t)TileID::HighGems; }

	/// <summary> Finds if the given ID is that of a floor. </summary>
	/// <param name="_ID"> The ID of the tile to check. </param>
	/// <returns> <c>true</c> if the tile is a floor, <c>false</c> otherwise. </returns>
	inline bool		IsFloor(const uint16_t _ID)		{ return _ID >= (int32_t)TileID::Floor1		&& _ID <= (int32_t)TileID::Floor4; }

	/// <summary> Gets a randomly generated plain wall. </summary>
	/// <returns> A randomly generated plain wall. </returns>
	inline TileID	GetRandomPlainWall()					{ return (TileID)((int32_t)TileID::Wall1 + Random::RandomBetween(0, (int32_t)TileID::Wall4)); }

	/// <summary> Gets a randomly generated floor. </summary>
	/// <returns> A randomly generated floor. </returns>
	inline TileID	GetRandomFloor()						{ return (TileID)(TileID::Floor1 + Random::RandomBetween(0, (int32_t)TileID::Wall4)); }
}
#endif