#include "Game.h"

// Service includes.
#include "ConsoleLogger.h"
#include "SDLGraphics.h"
#include "KeyboardControls.h"
#include "LetterBoxScreen.h"

/// <summary> Draws the game. </summary>
void MainGame::Game::draw()
{
	// If the game is going to exit anyway, do nothing.
	if (s_currentGameState == GameState::Exit) { return; }

	// Get the graphics service.
	Graphics::Graphics& graphics = GetService().GetGraphics();

	// Clear the window.
	graphics.Clear(0, 0, 0);

	// Handle drawing based on the current state.
	switch (s_currentGameState)
	{
	case MainMenu: { break; }
	case Map: { m_world.Draw(); break; }
	case Minigame: { m_miningMinigame.Draw(); break; }
	default: { throw std::exception("Invalid gamestate."); }
	}

	// Update the screen with everything that has been drawn.
	graphics.Present();
}

/// <summary> Updates the game. </summary>
void MainGame::Game::update()
{
	// Pump the events service.
	m_events->PumpEvents();

	// Update the world.
	m_world.Update();
}

/// <summary> Creates and initialises the game. </summary>
MainGame::Game::Game()
{
	initialiseServices();

	initialiseBindings();

	initialiseGameObjects();

	loadTextures();
}

/// <summary> Creates and initialises each service. </summary>
void MainGame::Game::initialiseServices()
{
	// Initialise events.
	m_events = new Events::SDLEvents();
	s_serviceProvider.SetEvents(*m_events);

	// Initialise and add the logger.
	Logging::ConsoleLogger* logger = new Logging::ConsoleLogger();
	s_serviceProvider.SetLogger(*logger);

	// Initialise and add the graphics.
	m_SDLGraphics = new Graphics::SDLGraphics();
	m_SDLGraphics->Initialise(960, 540, *logger);
	s_serviceProvider.SetGraphics(*m_SDLGraphics);

	// Initialise and add the controls.
	Controls::KeyboardControls* keyboardControls = new Controls::KeyboardControls();
	keyboardControls->LoadFromFile(c_contentFolder + '\\' + "Bindings.txt");
	s_serviceProvider.SetControls(*keyboardControls);

	// Initialise the screen.
	m_letterBoxScreen = new Screens::LetterBoxScreen();
	s_serviceProvider.SetScreen(*m_letterBoxScreen);
}

/// <summary> Hooks up game events to specific functions. </summary>
void MainGame::Game::initialiseBindings()
{
	// Bind the minigame start and end.
	m_events->AddUserListener(Events::UserEvent::StartMinigame, std::bind(&Game::startMinigame, this, std::placeholders::_1, std::placeholders::_2));
	m_events->AddUserListener(Events::UserEvent::StopMinigame, std::bind(&Game::stopMinigame, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the window resizing.
	m_events->AddFrameworkListener(SDL_WINDOWEVENT, std::bind(&Game::resizeScreen, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the game quit.
	m_events->AddFrameworkListener(SDL_QUIT, std::bind(&Game::exitGame, this, std::placeholders::_1, std::placeholders::_2));
}

/// <summary> Sets up the world and mining minigame. </summary>
void MainGame::Game::initialiseGameObjects()
{
	// Initialise the minigame and world.
	m_miningMinigame.Initialise();
	m_world.Initialise();

	// Generate a random map to start with.
	m_world.GenerateRandomMap();
}

/// <summary> Loads all textures to the graphics service. </summary>
void MainGame::Game::loadTextures()
{
	// Load the tileable sprites.
	m_SDLGraphics->LoadSheetToID(c_contentFolder + '\\' + "Tiles.png", SpriteData::SheetID::Tiles, SpriteData::c_tileSize);
	m_SDLGraphics->LoadSheetToID(c_contentFolder + '\\' + "MapObjects.png", SpriteData::SheetID::Objects, SpriteData::c_tileSize);
	m_SDLGraphics->LoadSheetToID(c_contentFolder + '\\' + "CaveWalls.png", SpriteData::SheetID::MineWalls, SpriteData::c_wallSize);

	// Load the UI elements.
	m_SDLGraphics->LoadSheetToID(c_contentFolder + '\\' + "UI.png", SpriteData::SheetID::UI, std::vector<Rectangle>
	{
		Rectangle(0, 0, 128, 540),
		Rectangle(128, 480, 960, 60),
		Rectangle(128, 452, 960, 28),
		Rectangle(128, 420, 32, 32),
		Rectangle(160, 420, 32, 32),
		Rectangle(192, 420, 32, 32),
	});
}

/// <summary> Starts the mining minigame. </summary>
/// <param name="_tilePosition"> The position of the tile to mine. </param>
/// <param name="_tileProsperity"> The prosperity of the tile. </param>
void MainGame::Game::startMinigame(void* _tilePosition, void* _tileProsperity)
{
	// Cast the data.
	Point tilePosition = *static_cast<Point*>(_tilePosition);
	uint8_t cellProsperity = *static_cast<uint8_t*>(_tileProsperity);

	// Set the current game state to minigame and generate the cave wall.
	s_currentGameState = GameState::Minigame;
	m_miningMinigame.Generate(tilePosition, cellProsperity);
}

/// <summary> Stops the mining minigame. </summary>
/// <param name="_tilePosition"> The position of the tile. </param>
/// <param name="_unused"> Unused. </param>
void MainGame::Game::stopMinigame(void* _tilePosition, void* _unused)
{
	// Set the current game state to map.
	s_currentGameState = GameState::Map;
}

/// <summary> Runs the game, starting the update and draw loop. </summary>
/// <returns> <c>0</c> if the game ran correctly, anything else otherwise. </returns>
int32_t MainGame::Game::Run()
{
	// Keep running for as long as the game state is not exit.
	while (s_currentGameState != GameState::Exit)
	{
		// Update the game state.
		update();

		// Draw the current game state.
		draw();

		// Wait based on the fps.
		SDL_Delay((uint32_t)(1000.0f / (float_t)m_SDLGraphics->m_framesPerSecond));
	}

	// Return 0 to say the game ran successfully.
	return 0;
}

// Initialise the service provider statically.
ServiceProvider MainGame::Game::s_serviceProvider = ServiceProvider();

// Initialise the game state to the map.
MainGame::GameState MainGame::Game::s_currentGameState = MainGame::GameState::Map;