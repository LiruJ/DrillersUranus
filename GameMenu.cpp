#include "GameMenu.h"

// Data includes.
#include "World.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

/// <summary> Initialises elements and bindings. </summary>
/// <param name="_events"> The events bus. </param>
void UserInterface::GameMenu::Initialise(Events::Events& _events)
{
	// Initialise the side bar.
	m_sideBar = UserInterface::Frame(Point(832, 0), Point(128, 540), SpriteData::UIID::SideBar);

	// Initialise the death screen.
	m_endScreen = UserInterface::Frame(Point(384, 222), Point(128, 96), SpriteData::UIID::DeathScreen);
	m_quitButton = UserInterface::Button(Point(384, 286), Point(128, 32), SpriteData::UIID::MenuButton);
	hideDeathScreen();

	// Initialise the minimap.
	m_minimap = Minimap(Rectangle(832, 32, 128, 128));

	// Bind the menu button to go to the main menu.
	m_quitButton.SetEvent(Events::UserEvent::MainMenu, 0);
	m_quitButton.Initialise(_events);

	// Bind the player dying to the death screen showing.
	_events.AddUserListener(Events::UserEvent::PlayerDied, std::bind(&GameMenu::showDeathScreen, this, std::placeholders::_1));

	// Bind the game starting to the death screen hiding.
	_events.AddUserListener(Events::UserEvent::StartGame, std::bind(&GameMenu::hideDeathScreen, this, std::placeholders::_1));

	// Bind the minigame starting to this menu hiding.
	_events.AddUserListener(Events::UserEvent::StartMinigame, std::bind(&GameMenu::hide, this, std::placeholders::_1));
	_events.AddUserListener(Events::UserEvent::MainMenu, std::bind(&GameMenu::hide, this, std::placeholders::_1));

	// Bind the minigame stopping to this menu showing.
	_events.AddUserListener(Events::UserEvent::StopMinigame, std::bind(&GameMenu::show, this, std::placeholders::_1));
	_events.AddUserListener(Events::UserEvent::StartGame, std::bind(&GameMenu::show, this, std::placeholders::_1));
}

/// <summary> Draws the game menu. </summary>
/// <param name="_world"> The world data. </param>
/// <param name="_services"> The service provider. </param>
void UserInterface::GameMenu::Draw(WorldObjects::World& _world, Services::ServiceProvider& _services)
{
	// Draw the side bar.
	m_sideBar.Draw(_services);

	// Get the graphics and screen services.
	Graphics::Graphics& graphics = _services.GetService<Graphics::Graphics>(Services::ServiceType::Graphics);
	Screens::Screen& screen = _services.GetService<Screens::Screen>(Services::ServiceType::Screen);

	// Draw the player's inventory.
	_world.GetPlayer().GetInventory().Draw(Point(832, 192), _services);

	// Draw the current level and remaining time.
	graphics.DrawString(SpriteData::FontID::SmallDetail,
		"LVL. " + std::to_string(_world.GetCurrentLevel()),
		screen.ScreenToWindowSpace(Point(868, 4)), { 255, 255, 255, 255 });

	graphics.DrawString(SpriteData::FontID::SmallDetail,
		std::to_string(_world.GetCollapseTime()),
		screen.ScreenToWindowSpace(Point(868, 451)),
		{ 255, 128, 128, 255 });

	// Draw the minimap.
	m_minimap.Draw(_world, _services);

	// Draw the death screen.
	m_endScreen.Draw(_services);

	// Draw the quit button.
	m_quitButton.Draw(_services);

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
