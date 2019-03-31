#include "Camera.h"
#include "SpriteData.h"
#include "World.h"
#include "Game.h"

void Camera::Draw(World& _world)
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = Game::GetService().GetGraphics();
	Screen& screen = Game::GetService().GetScreen();

	// Get the tiledata.
	TileMap& tileMap = _world.GetTileMap();

	// Centre on the player.
	CentreOnMapObject(_world.GetPlayer());

	// Draw the map data.
	for (int32_t x = std::max(0, m_worldPosition.x / SpriteData::c_tileSize); x < std::min((int32_t)tileMap.GetWidth(), ((m_worldPosition.x + 832) / SpriteData::c_tileSize) + 1); x++)
	{
		for (int32_t y = std::max(0, m_worldPosition.y / SpriteData::c_tileSize); y < std::min((int32_t)tileMap.GetHeight(), ((m_worldPosition.y + m_worldSize.y) / SpriteData::c_tileSize) + 1); y++)
		{
			tileMap.GetTileAt(Point(x, y)).Draw(Point(x, y), m_worldPosition);
		}
	}

	// Draw the spawn and exit points if they're on screen.
	if (IsOnScreen(_world.GetSpawn())) { _world.GetSpawn().Draw(m_worldPosition); }
	if (IsOnScreen(_world.GetExit())) { _world.GetExit().Draw(m_worldPosition); }

	// Draw the player.
	_world.GetPlayer().Draw(m_worldPosition);

	// Draw the UI.
	m_sideBar.Draw();
}

bool Camera::IsOnScreen(IReadOnlyMapObject& _mapObject)
{
	// Calculate the max bounds of the camera and game object.
	Point cameraMax		= m_worldPosition + m_worldSize;
	Point objectWorldPosition = _mapObject.GetTilePosition() * SpriteData::c_tileSize;
	Point positionMax	= objectWorldPosition + SpriteData::c_tileSize;

	// Return true if the game object is within bounds, false otherwise.
	return (positionMax.x > m_worldPosition.x && positionMax.y > m_worldPosition.y && objectWorldPosition.x < cameraMax.x && objectWorldPosition.y < cameraMax.y);
}

void Camera::initialiseGui()
{
	m_sideBar = UserInterface::Frame(Point(832, 0), Point(128, 540), SpriteData::UIID::SideBar);
}

void Camera::CentreOnMapObject(IReadOnlyMapObject& _mapObject)
{
	// Find the centre of the subject.
	Point subjectCentre = (_mapObject.GetTilePosition() * SpriteData::c_tileSize) + (SpriteData::c_tileSize / 2);

	// Centre the view.
	m_worldPosition = subjectCentre - (m_worldSize / 2);
}