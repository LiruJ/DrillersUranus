#ifndef GAME_H
#define GAME_H

// Data includes.
#include "World.h"
#include "MiningMinigame.h"

//Service includes.
#include "ServiceProvider.h"
#include "SDLGraphics.h"
#include "SDLEvents.h"
#include "LetterBoxScreen.h"

// Utility includes.
#include <string>

namespace MainGame
{
	/// <summary> Represents the current state of the <see cref="Game"/>. </summary>
	enum GameState { MainMenu, Map, Minigame, Exit, Lost };

	/// <summary> Represents the main game which ties all the components together. </summary>
	class Game
	{
	public:
		Game();

		int32_t Run();

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

		/// <summary> The screen service which allows for resizing. </summary>
		Screens::LetterBoxScreen*	m_letterBoxScreen;

		/// <summary> The events service which allows for events to be pumped. </summary>
		Events::SDLEvents*			m_events;

		/// <summary> The map world. </summary>
		WorldObjects::World			m_world;

		/// <summary> The mining minigame. </summary>
		Minigames::MiningMinigame	m_miningMinigame;

		void draw();

		void update();

		void initialiseServices();

		void initialiseBindings();

		void initialiseGameObjects();

		void loadTextures();

		void startMinigame(void*, void*);

		void stopMinigame(void*, void*);

		/// <summary> Handles the window resize event. </summary>
		/// <param name="_windowX"> The pointer to the new window width. </param>
		/// <param name="_windowY"> The pointer to the new window height. </param>
		void resizeScreen(void* _windowX, void* _windowY) { m_letterBoxScreen->Resize(*static_cast<int32_t*>(_windowX), *static_cast<int32_t*>(_windowY)); }

		/// <summary> Sets the game state to exit so that the game will quit the update loop. </summary>
		/// <param name="_unused"> Unused. </param>
		/// <param name="_unused2"> Unused. </param>
		void exitGame(void* _unused, void* _unused2) { s_currentGameState = GameState::Exit; }

		void loseGame(void*, void*);
	};
}
#endif