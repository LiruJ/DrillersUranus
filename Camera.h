#ifndef CAMERA_H
#define CAMERA_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"

// GameObject includes.
#include "IReadOnlyMapObject.h"

// Utility includes.
#include "SpriteData.h"

// UI includes.
#include "Frame.h"

namespace WorldObjects
{
	// Forward declaration.
	class World;
	
	/// /// <summary> Represents a camera that exists within the world and renders what it can see. </summary>
	class Camera
	{
	public:
		/// <summary> Creates an empty <see cref="Camera"/>. </summary>
		Camera() : m_worldPosition(Point(0, 0)), m_worldSize(Point(960, 540)), m_worldBounds(m_worldPosition, m_worldSize) { initialiseGui(); }

		// Prevent copies.
		Camera(Camera&) = delete;
		Camera& operator=(const Camera&) = delete;

		void Draw(World&);

		/// <summary> Centres this <see cref="Camera"/>'s view on the given <see cref="IReadOnlyMapObject"/>. </summary>
		/// <param name="_mapObject"> The object to centre on. </param>
		void CentreOnMapObject(GameObjects::IReadOnlyMapObject& _mapObject) { m_worldPosition = ((_mapObject.GetTilePosition() * SpriteData::c_tileSize) + (SpriteData::c_tileSize / 2)) - (m_worldSize / 2); m_worldBounds.x = m_worldPosition.x; m_worldBounds.y = m_worldPosition.y; }

		/// <summary> Finds if the given <see cref="IReadOnlyMapObject"/> is within the camera's bounds. </summary>
		/// <param name="_mapObject"> The object to check. </param>
		/// <returns> <c>true</c> if the given <see cref="IReadOnlyMapObject"/> is on screen; otherwise, <c>false</c>. </returns>
		bool IsOnScreen(GameObjects::IReadOnlyMapObject& _mapObject) { return (m_worldBounds.IsPointInside(_mapObject.GetTilePosition() * SpriteData::c_tileSize) || m_worldBounds.IsPointInside((_mapObject.GetTilePosition() + 1) * SpriteData::c_tileSize)); }
	private:
		/// <summary> The position of the camera in the world. </summary>
		Point					m_worldPosition;

		/// <summary> The size of the camera in the world. </summary>
		Point					m_worldSize;

		/// <summary> The bounds of the world. </summary>
		Rectangle				m_worldBounds;

		/// <summary> The UI frame. </summary>
		UserInterface::Frame	m_sideBar;

		void			initialiseGui();
	};
}
#endif