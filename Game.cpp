#include "Game.h"

// Service includes.
#include "ConsoleLogger.h"
#include "SDLGraphics.h"
#include "KeyboardControls.h"
#include "LetterBoxScreen.h"

// Utility includes.
#include "SpriteData.h"

/// <summary> Draws the game. </summary>
void MainGame::Game::draw()
{
	// If the game is going to exit anyway, do nothing.
	if (m_currentGameState == GameState::Exit) { return; }

	// Clear the window.
	m_SDLGraphics.Clear({ 0, 0, 0, 255 });

	// Handle drawing based on the current state.
	switch (m_currentGameState)
	{
	case MainMenu: { m_mainMenu.Draw(m_serviceProvider); break; }
	case Lost:
	case Won:
	case Map: { m_world.Draw(m_serviceProvider); m_particles.Draw(m_SDLGraphics, m_letterBoxScreen, m_world.GetCamera().GetWorldPosition()); break; }
	case Minigame: { m_miningMinigame.Draw(m_serviceProvider); m_particles.Draw(m_SDLGraphics, m_letterBoxScreen); break; }
	default: { throw std::exception("Invalid gamestate."); }
	}

	// Update the screen with everything that has been drawn.
	m_SDLGraphics.Present();
}

/// <summary> Updates the game. </summary>
void MainGame::Game::update()
{
	// Update the gametime.
	m_gameTime.Update();

	// Pump the events service.
	m_events.PumpEvents(m_currentGameState, m_serviceProvider);

	// Play random music if none is playing.
	if (!m_SDLAudio.IsSongPlaying()) { m_SDLAudio.PlayRandomSong(); }

	// Update the particles.
	m_particles.Update(m_gameTime);

	// Update the screen.
	m_letterBoxScreen.Update(m_gameTime);
}

/// <summary> Creates and initialises the game. </summary>
MainGame::Game::Game()
{
	initialiseServices();

	initialiseBindings();

	initialiseGameObjects();

	loadTextures();

	loadSounds();
}

/// <summary> Creates and initialises each service. </summary>
void MainGame::Game::initialiseServices()
{
	// Initialise events.
	m_serviceProvider.SetService(&m_events, Services::ServiceType::Events);

	// Initialise and add the logger.
	Logging::ConsoleLogger* logger = new Logging::ConsoleLogger();
	m_serviceProvider.SetService(logger, Services::ServiceType::Logger);

	// Initialise and add the graphics.
	m_SDLGraphics.Initialise(960, 540, *logger);
	m_serviceProvider.SetService(&m_SDLGraphics, Services::ServiceType::Graphics);

	// Initialise and add the audio.
	m_SDLAudio.Initialise(*logger);
	m_serviceProvider.SetService(&m_SDLAudio, Services::ServiceType::Audio);

	// Initialise and add the controls.
	Controls::KeyboardControls* keyboardControls = new Controls::KeyboardControls();
	keyboardControls->LoadFromFile(c_contentFolder + '\\' + "Bindings.txt");
	m_serviceProvider.SetService(keyboardControls, Services::ServiceType::Controls);

	// Initialise the screen.
	m_serviceProvider.SetService(&m_letterBoxScreen, Services::ServiceType::Screen);

	// Initialise the time.
	m_serviceProvider.SetService(&m_gameTime, Services::ServiceType::Time);

	// Initialise the particles.
	m_particles.SetSheetID(SpriteData::SheetID::Particles);
	m_serviceProvider.SetService(&m_particles, Services::ServiceType::Particles);
}

/// <summary> Hooks up game events to specific functions. </summary>
void MainGame::Game::initialiseBindings()
{
	// Bind the minigame start and end.
	m_events.AddUserListener(Events::UserEvent::StartMinigame, std::bind(&Game::startMinigame, this, std::placeholders::_1));
	m_events.AddUserListener(Events::UserEvent::StopMinigame, std::bind(&Game::stopMinigame, this, std::placeholders::_1));

	// Bind the window resizing.
	m_events.AddFrameworkListener(SDL_WINDOWEVENT, std::bind(&Game::resizeScreen, this, std::placeholders::_1));

	// Bind the game quit.
	m_events.AddFrameworkListener(SDL_QUIT, std::bind(&Game::exitGame, this, std::placeholders::_1));
	m_events.AddUserListener(Events::UserEvent::QuitGame, std::bind(&Game::exitGame, this, std::placeholders::_1));

	// Bind the lose/win game.
	m_events.AddUserListener(Events::UserEvent::PlayerDied, std::bind(&Game::loseGame, this, std::placeholders::_1));
	m_events.AddUserListener(Events::UserEvent::PlayerWon, std::bind(&Game::winGame, this, std::placeholders::_1));

	// Bind the start game.
	m_events.AddUserListener(Events::UserEvent::StartGame, std::bind(&Game::startGame, this, std::placeholders::_1));

	// Bind the main menu.
	m_events.AddUserListener(Events::UserEvent::MainMenu, std::bind(&Game::endGame, this, std::placeholders::_1));
	m_mainMenu.Initialise(m_events);
}

/// <summary> Sets up the world and mining minigame. </summary>
void MainGame::Game::initialiseGameObjects()
{
	// Initialise the minigame and world.
	m_miningMinigame.Initialise(m_events);
	m_world.Initialise(m_events);
}

/// <summary> Loads all textures to the graphics service. </summary>
void MainGame::Game::loadTextures()
{
	// Load the tileable sprites.
	m_SDLGraphics.LoadSheetToID(c_contentFolder + '\\' + "Tiles.png", SpriteData::SheetID::Tiles, SpriteData::c_tileSize);
	m_SDLGraphics.LoadSheetToID(c_contentFolder + '\\' + "MapObjects.png", SpriteData::SheetID::Objects, SpriteData::c_tileSize);
	m_SDLGraphics.LoadSheetToID(c_contentFolder + '\\' + "CaveWalls.png", SpriteData::SheetID::MineWalls, SpriteData::c_wallSize);
	m_SDLGraphics.LoadSheetToID(c_contentFolder + '\\' + "MinimapIcons.png", SpriteData::SheetID::Minimap, 1);
	m_SDLGraphics.LoadSheetToID(c_contentFolder + '\\' + "Particles.png", SpriteData::SheetID::Particles, 3);

	// Load the UI elements.
	m_SDLGraphics.LoadSheetToID(c_contentFolder + '\\' + "UI.png", SpriteData::SheetID::UI, std::vector<Rectangle>
	{
		Rectangle(0, 0, 128, 540),
		Rectangle(128, 480, 960, 60),
		Rectangle(128, 452, 960, 28),
		Rectangle(128, 420, 32, 32),
		Rectangle(160, 420, 32, 32),
		Rectangle(192, 420, 32, 32),
		Rectangle(128, 192, 128, 32),
		Rectangle(128, 160, 32, 32),
		Rectangle(160, 160, 32, 32),
		Rectangle(192, 160, 32, 32),
		Rectangle(224, 160, 32, 32),
		Rectangle(1088, 0, 960, 540),
		Rectangle(128, 0, 128, 32),
		Rectangle(128, 32, 128, 32),
		Rectangle(128, 64, 128, 32),
		Rectangle(128, 96, 128, 32),
		Rectangle(128, 128, 128, 32),
		Rectangle(256, 0, 560, 448),
		Rectangle(128, 224, 128, 96),
	});

	// Load the gems.
	m_SDLGraphics.LoadSheetToID(c_contentFolder + '\\' + "Gems.png", SpriteData::SheetID::Gems, std::vector<Rectangle>
	{
		Rectangle(0, 0, 80, 80),
		Rectangle(144, 0, 80, 64),
		Rectangle(80, 64, 144, 144),
		Rectangle(224, 0, 160, 160),
	});

	// Load the fonts.
	m_SDLGraphics.LoadFontToID(c_contentFolder + '\\' + "Immortal.ttf", SpriteData::FontID::Menu, 28);
	m_SDLGraphics.LoadFontToID(c_contentFolder + '\\' + "trebuc.ttf", SpriteData::FontID::SmallDetail, 20);
}

/// <summary> Loads all required audio files. </summary>
void MainGame::Game::loadSounds()
{
	m_SDLAudio.LoadSoundToID(AudioData::SoundID::Collapse, c_contentFolder + '\\' + "Collapse.wav");
	m_SDLAudio.LoadSoundToID(AudioData::SoundID::GemWallCollapse, c_contentFolder + '\\' + "GemWallCollapse.wav");
	m_SDLAudio.LoadSoundToID(AudioData::SoundID::GetGem, c_contentFolder + '\\' + "GetGem.wav");
	m_SDLAudio.LoadSoundToID(AudioData::SoundID::HitGem, c_contentFolder + '\\' + "GemHit.wav");
	m_SDLAudio.LoadSoundToID(AudioData::SoundID::PlayerCrushed, c_contentFolder + '\\' + "PlayerCrushed.wav");
	m_SDLAudio.LoadSoundToID(AudioData::SoundID::UseExit, c_contentFolder + '\\' + "UseExit.wav");
	m_SDLAudio.LoadSoundToID(AudioData::SoundID::UIClick, c_contentFolder + '\\' + "UIClick.wav");
	m_SDLAudio.LoadSoundToID(AudioData::SoundID::Win, c_contentFolder + '\\' + "Win.wav");

	// Load the music.
	m_SDLAudio.LoadSongToID(AudioData::SongID::Main, c_contentFolder + '\\' + "Music1.wav");
	m_SDLAudio.LoadSongToID(AudioData::SongID::Cave, c_contentFolder + '\\' + "Music2.wav");

	// Load the step sounds.
	m_SDLAudio.LoadSoundVariantsToID(AudioData::VariedSoundID::Step, std::vector<std::string>
	{
		c_contentFolder + '\\' + "Step1.wav",
		c_contentFolder + '\\' + "Step2.wav",
		c_contentFolder + '\\' + "Step3.wav",
		c_contentFolder + '\\' + "Step4.wav",
		c_contentFolder + '\\' + "Step5.wav",
		c_contentFolder + '\\' + "Step6.wav",
	});

	// Load the hit sounds.
	m_SDLAudio.LoadSoundVariantsToID(AudioData::VariedSoundID::Hit, std::vector<std::string>
	{
		c_contentFolder + '\\' + "Hit1.wav",
		c_contentFolder + '\\' + "Hit2.wav",
		c_contentFolder + '\\' + "Hit3.wav",
		c_contentFolder + '\\' + "Hit4.wav",
	});

	// Load the smash sounds.
	m_SDLAudio.LoadSoundVariantsToID(AudioData::VariedSoundID::Smash, std::vector<std::string>
	{
		c_contentFolder + '\\' + "Smash1.wav",
		c_contentFolder + '\\' + "Smash2.wav",
		c_contentFolder + '\\' + "Smash3.wav",
		c_contentFolder + '\\' + "Smash4.wav",
	});
}

/// <summary> Unloads and destroys anything SDL related. </summary>
void MainGame::Game::unload()
{
	m_SDLAudio.Unload();
	m_SDLGraphics.Unload();
}

/// <summary> Starts the mining minigame. </summary>
/// <param name="_context"> The context of the event. </param>
void MainGame::Game::startMinigame(Events::EventContext* _context)
{
	// Cast the data.
	Point tilePosition = *static_cast<Point*>(_context->m_data1);
	uint8_t cellProsperity = *static_cast<uint8_t*>(_context->m_data2);

	// Set the current game state to minigame and generate the cave wall.
	m_currentGameState = GameState::Minigame;
	m_miningMinigame.Prepare(m_serviceProvider, tilePosition, cellProsperity);

	// Kill particles.
	m_particles.KillAllAlive();

	// Stop shaking.
	m_letterBoxScreen.ShakeScreen(0);
}

/// <summary> Stops the mining minigame. </summary>
void MainGame::Game::stopMinigame(Events::EventContext*)
{
	// Set the current game state to map.
	m_currentGameState = GameState::Map;

	// Kill particles.
	m_particles.KillAllAlive();

	// Stop shaking.
	m_letterBoxScreen.ShakeScreen(0);
}

/// <summary> Fires when the player is crushed or otherwise dies, shows the game over screen until they choose to go back. </summary>
void MainGame::Game::loseGame(Events::EventContext*)
{
	// Set the current game state to lost.
	m_currentGameState = GameState::Lost;

	// Kill particles.
	m_particles.KillAllAlive();
}

/// <summary> Fires when the player makes it to level 10, does the same as the death screen but says "won" instead. </summary>
void MainGame::Game::winGame(Events::EventContext*)
{
	// Set the current game state to won.
	m_currentGameState = GameState::Won;

	// Kill particles.
	m_particles.KillAllAlive();
}

/// <summary> Starts the game. </summary>
void MainGame::Game::startGame(Events::EventContext*)
{
	// Reset the world.
	m_world.Reset();

	// Set the game state to ingame.
	m_currentGameState = GameState::Map;
}

/// <summary> Goes back to the main menu. </summary>
void MainGame::Game::endGame(Events::EventContext*)
{
	// Set the game state to menu.
	m_currentGameState = GameState::MainMenu;

	// Stop shaking.
	m_letterBoxScreen.ShakeScreen(0);
}

/// <summary> Runs the game, starting the update and draw loop. </summary>
void MainGame::Game::Run()
{
	// Keep running for as long as the game state is not exit.
	while (m_currentGameState != GameState::Exit)
	{
		// Update the game state.
		update();

		// Draw the current game state.
		draw();

		// Wait based on the fps.
		SDL_Delay((uint32_t)(1000.0f / (float_t)m_SDLGraphics.m_framesPerSecond));
	}

	// Unload before quitting.
	unload();
}