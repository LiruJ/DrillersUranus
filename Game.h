#ifndef GAME_H
#define GAME_H

//Service includes.
#include "ServiceProvider.h"
#include "SDLGraphics.h"
#include "SDLEvents.h"

// Data includes.
#include "World.h"
#include "MiningMinigame.h"

/// <summary> Represents the current state of the game. </summary>
enum GameState { MainMenu, Map, Minigame };

class Game
{
public:
	Game();

	int Run();

	/// <summary> Gets the current service provider. </summary>
	/// <returns> The current service provider. </returns>
	static inline Services&		GetService() { return s_serviceProvider; }

	/// <summary> Gets the current game state. </summary>
	/// <returns> The current game state. </returns>
	static inline GameState		GetGameState() { return s_currentGameState; }

private:
	/// <summary> The service provider. </summary>
	static ServiceProvider		s_serviceProvider;

	/// <summary> The current state of the game. </summary>
	static GameState			s_currentGameState;

	/// <summary> The folder in which the content is stored. </summary>
	const std::string			c_contentFolder = "Content";

	/// <summary> The graphical service which allows for textures to be loaded. </summary>
	Graphics::SDLGraphics*		m_SDLGraphics;

	/// <summary> The events service which allows for events to be pumped. </summary>
	SDLEvents*					m_events;

	/// <summary> The map world. </summary>
	World						m_world;

	/// <summary> The mining minigame. </summary>
	Minigames::MiningMinigame	m_miningMinigame;

	void draw();

	int update();

	void initialiseServices();
	void initialiseBindings();
	void initialiseGameObjects();
	void loadTextures();

	void startMinigame(void*, void*);
	void stopMinigame(void*, void*);

	void resizeScreen(void* _windowX, void* _windowY) { GetService().GetScreen().Resize(*static_cast<int*>(_windowX), *static_cast<int*>(_windowY)); }
};
#endif