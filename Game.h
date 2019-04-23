#ifndef GAME_H
#define GAME_H

// Data includes.
#include "World.h"
#include "MiningMinigame.h"

//Service includes.
#include "ServiceProvider.h"
#include "SDLGraphics.h"
#include "SDLAudio.h"
#include "SDLEvents.h"
#include "LetterBoxScreen.h"
#include "GameTime.h"
#include "ExplodingParticles.h"
#include "EventContext.h"

// Utility includes.
#include <string>
#include "AudioData.h"

// UI includes.
#include "MainMenu.h"

namespace MainGame
{
	/// <summary> Represents the main game which ties all the components together. </summary>
	class Game
	{
	public:
		Game();

		void Run();
	private:
		/// <summary> The folder in which the content is stored. </summary>
		const std::string			c_contentFolder = "Content";

		/// <summary> The service provider. </summary>
		Services::ServiceProvider	m_serviceProvider;

		/// <summary> The current state of the game. </summary>
		GameState					m_currentGameState;

		/// <summary> The graphical service which allows for textures to be loaded. </summary>
		Graphics::SDLGraphics		m_SDLGraphics;

		/// <summary> The audio service which allows for sounds to be loaded. </summary>
		Audio::SDLAudio				m_SDLAudio;

		/// <summary> The screen service which allows for resizing. </summary>
		Screens::LetterBoxScreen	m_letterBoxScreen;

		/// <summary> The events service which allows for events to be pumped. </summary>
		Events::SDLEvents			m_events;

		/// <summary> The time service which allows for updating. </summary>
		Time::GameTime				m_gameTime;

		/// <summary> The particles service which allows for updating. </summary>
		Particles::ExplodingParticles m_particles;

		/// <summary> The main menu. </summary>
		UserInterface::MainMenu		m_mainMenu;

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

		void loadSounds();

		void unload();

		void startMinigame(Events::EventContext*);

		void stopMinigame(Events::EventContext* = NULL);

		/// <summary> Handles the window resize event. </summary>
		/// <param name="_context"> The context of the event. </param>
		void resizeScreen(Events::EventContext* _context) { m_letterBoxScreen.Resize(*static_cast<int32_t*>(_context->m_data1), *static_cast<int32_t*>(_context->m_data2)); }

		/// <summary> Sets the game state to exit so that the game will quit the update loop. </summary>
		void exitGame(Events::EventContext* = NULL) { m_currentGameState = GameState::Exit; }

		void loseGame(Events::EventContext* = NULL);

		void startGame(Events::EventContext* = NULL);
	
		void endGame(Events::EventContext* = NULL);
	};
}
#endif