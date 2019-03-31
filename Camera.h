#ifndef CAMERA_H
#define CAMERA_H

// UI includes.
#include "Frame.h"

// Data includes.
#include "Point.h"

// Object includes.
#include "IReadOnlyMapObject.h"

// Forward declaration.
class World;

class Camera
{
public:
	Camera() : m_worldPosition(Point(0, 0)), m_worldSize(Point(960, 540)) { initialiseGui(); }

	Camera(Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	void			Draw(World&);
	void			CentreOnMapObject(IReadOnlyMapObject&);

	bool			IsOnScreen(IReadOnlyMapObject&);
private:
	/// <summary> The position of the camera in the world. </summary>
	Point			m_worldPosition;

	/// <summary> The size of the camera in the world. </summary>
	Point			m_worldSize;

	UserInterface::Frame m_sideBar;

	void			initialiseGui();
};
#endif