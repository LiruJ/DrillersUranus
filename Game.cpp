#include "Game.h"

// Service includes.
#include "ConsoleLogger.h"
#include "SDLGraphics.h"
#include "KeyboardControls.h"
#include "LetterBoxScreen.h"

/// <summary> Draws the game. </summary>
void Game::draw()
{
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
/// <returns> <c>0</c> if the update loop ran successfully, anything else otherwise. </returns>
int32_t Game::update()
{
	// Pump the events service.
	m_events->PumpEvents();

	// Update the world.
	return m_world.Update();
}

Game::Game()
{
	initialiseServices();

	initialiseBindings();

	initialiseGameObjects();

	loadTextures();
}

/// <summary> Create and initialise each service. </summary>
void Game::initialiseServices()
{
	// Initialise events.
	m_events = new SDLEvents();
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
	s_serviceProvider.SetScreen(*new LetterBoxScreen());
}

void Game::initialiseBindings()
{
	// Bind the minigame start and end.
	m_events->AddUserListener(UserEvent::StartMinigame, std::bind(&Game::startMinigame, this, std::placeholders::_1, std::placeholders::_2));
	m_events->AddUserListener(UserEvent::StopMinigame, std::bind(&Game::stopMinigame, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the window resizing.
	m_events->AddFrameworkListener(SDL_WINDOWEVENT, std::bind(&Game::resizeScreen, this, std::placeholders::_1, std::placeholders::_2));
}

void Game::initialiseGameObjects()
{
	// Initialise the minigame and world.
	m_miningMinigame.Initialise();
	m_world.Initialise();

	// Generate a random map to start with.
	m_world.GenerateRandomMap();
}

/// <summary> Loads all textures to the graphics service. </summary>
void Game::loadTextures()
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

void Game::startMinigame(void* _tilePosition, void* _tileProsperity)
{
	// Cast the data.
	Point tilePosition = *static_cast<Point*>(_tilePosition);
	uint8_t cellProsperity = *static_cast<uint8_t*>(_tileProsperity);

	// Set the current game state to minigame and generate the cave wall.
	s_currentGameState = GameState::Minigame;
	m_miningMinigame.Generate(tilePosition, cellProsperity);
}

void Game::stopMinigame(void* _tilePosition, void* _unused)
{
	// Set the current game state to map.
	s_currentGameState = GameState::Map;
}

/// <summary> Runs the game, starting the update and draw loop. </summary>
/// <returns> <c>0</c> if the game ran correctly, anything else otherwise. </returns>
int32_t Game::Run()
{
	// Update first, if the update fails, fall out to the return, otherwise draw.
	while (!update()) 
	{
		draw();
		SDL_Delay((uint32_t)(1000.0f / (float_t)m_SDLGraphics->m_framesPerSecond));
	}

	// Return 0 to say the game ran successfully.
	return 0;
}

// Initialise the service provider statically.
ServiceProvider Game::s_serviceProvider = ServiceProvider();

// Initialise the game state to the map.
GameState Game::s_currentGameState = GameState::Map;