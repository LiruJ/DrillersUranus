#include "GameMenu.h"

// Data includes.
#include "World.h"

// Service includes.
#include "Game.h"
#include "Events.h"
#include "Graphics.h"
#include "Screen.h"

/// <summary> Initialises elements and bindings. </summary>
void UserInterface::GameMenu::Initialise()
{
	// Initialise the side bar.
	m_sideBar = UserInterface::Frame(Point(832, 0), Point(128, 540), SpriteData::UIID::SideBar);

	// Initialise the death screen.
	m_endScreen = UserInterface::Frame(Point(384, 222), Point(128, 96), SpriteData::UIID::DeathScreen);
	m_quitButton = UserInterface::Button(Point(384, 286), Point(128, 32), SpriteData::UIID::MenuButton);
	hideDeathScreen();

	// Initialise the minimap.
	m_minimap = Minimap(Rectangle(832, 32, 128, 128));

	// Get the event service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind the menu button to go to the main menu.
	m_quitButton.SetEvent(Events::UserEvent::MainMenu, 0);
	m_quitButton.Initialise();

	// Bind the player dying to the death screen showing.
	events.AddUserListener(Events::UserEvent::PlayerDied, std::bind(&GameMenu::showDeathScreen, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the game starting to the death screen hiding.
	events.AddUserListener(Events::UserEvent::StartGame, std::bind(&GameMenu::hideDeathScreen, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the minigame starting to this menu hiding.
	events.AddUserListener(Events::UserEvent::StartMinigame, std::bind(&GameMenu::hide, this, std::placeholders::_1, std::placeholders::_2));
	events.AddUserListener(Events::UserEvent::MainMenu, std::bind(&GameMenu::hide, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the minigame stopping to this menu showing.
	events.AddUserListener(Events::UserEvent::StopMinigame, std::bind(&GameMenu::show, this, std::placeholders::_1, std::placeholders::_2));
	events.AddUserListener(Events::UserEvent::StartGame, std::bind(&GameMenu::show, this, std::placeholders::_1, std::placeholders::_2));
}

/// <summary> Draws the game menu. </summary>
void UserInterface::GameMenu::Draw(WorldObjects::World& _world)
{
	// Draw the side bar.
	m_sideBar.Draw();

	// Get the graphics and screen services.
	Graphics::Graphics& graphics = MainGame::Game::GetService().GetGraphics();
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	// Draw the player's inventory.
	_world.GetPlayer().GetInventory().Draw(Point(832, 192));

	// Draw the current level and remaining time.
	graphics.DrawString(SpriteData::FontID::SmallDetail,
		"LVL. " + std::to_string(_world.GetCurrentLevel()),
		screen.ScreenToWindowSpace(Point(868, 4)), { 255, 255, 255, 255 });

	graphics.DrawString(SpriteData::FontID::SmallDetail,
		std::to_string(_world.GetCollapseTime()),
		screen.ScreenToWindowSpace(Point(868, 451)),
		{ 255, 128, 128, 255 });

	// Draw the minimap.
	m_minimap.Draw(_world);

	// Draw the death screen.
	m_endScreen.Draw();

	// Draw the quit button.
	m_quitButton.Draw();

	// Draw the player's inventory's worth depending on their alive status.
	Point worthPosition = Point();
	if (m_currentState == MenuState::Alive) { worthPosition = Point(868, 164); }
	else if (m_currentState == MenuState::Dead) { worthPosition = Point(424, 254); }
	graphics.DrawString(SpriteData::FontID::SmallDetail, '$' + std::to_string(_world.GetPlayer().GetInventory().CalculateCombinedValue()), screen.ScreenToWindowSpace(worthPosition), { 255, 255, 255, 255 });
}

/// <summary> Activates or deactivates this menu. </summary>
/// <param name="_active"> The new active value. </param>
void UserInterface::GameMenu::setActive(bool _active)
{
	// Set the active state of all elements.
	m_quitButton.SetActive(_active);
	m_sideBar.SetActive(_active);

	// If the player is still alive, don't activate the end screen.
	if (m_currentState == MenuState::Dead) { m_endScreen.SetActive(_active); }
}
