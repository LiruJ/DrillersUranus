#include "MinigameMenu.h"

// Data includes.
#include "Game.h"

// Utility includes.
#include "SpriteData.h"

/// <summary> Initialises the UI. </summary>
void UserInterface::MinigameMenu::Initialise(const uint16_t _maxTimer)
{
	// Initialise the background UI.
	m_bottomBar = UserInterface::Frame(Point(0, 480), Point(960, 60), SpriteData::UIID::MinigameBar);

	// Initialise the collapse bar.
	m_collapseBar = UserInterface::ProgressBar(Point(0, 512), Point(960, 28), SpriteData::UIID::WallTimer);
	m_collapseBar.SetMax(_maxTimer);
	m_collapseBar.SetValue(0);

	// Initialise the buttons.
	for (int32_t i = 0; i < 3; i++)
	{
		m_toolButtons[i] = UserInterface::Button(Point(i * 32, 480), Point(32, 32), SpriteData::UIID::Pickaxe + i);
		m_toolButtons[i].SetEvent(Events::UserEvent::ChangeTool, i);
		m_toolButtons[i].Initialise();
	}

	// Get the events service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind the tool changed event.
	events.AddUserListener(Events::UserEvent::ChangeTool, std::bind(&MinigameMenu::toolChanged, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the wall mined event.
	events.AddUserListener(Events::UserEvent::MinedWall, std::bind(&MinigameMenu::wallMined, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the minigame starting to this menu showing.
	events.AddUserListener(Events::UserEvent::StartMinigame, std::bind(&MinigameMenu::show, this, std::placeholders::_1, std::placeholders::_2));
	events.AddUserListener(Events::UserEvent::StartMinigame, std::bind(&MinigameMenu::start, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the minigame stopping to this menu hiding.
	events.AddUserListener(Events::UserEvent::StopMinigame, std::bind(&MinigameMenu::hide, this, std::placeholders::_1, std::placeholders::_2));
	events.AddUserListener(Events::UserEvent::StartGame, std::bind(&MinigameMenu::hide, this, std::placeholders::_1, std::placeholders::_2));
}

/// <summary> Draws this menu. </summary>
void UserInterface::MinigameMenu::Draw()
{
	m_bottomBar.Draw();
	m_collapseBar.Draw();
	for (uint8_t i = 0; i < 3; i++) { m_toolButtons[i].Draw(); }
}

/// <summary> Fires when the wall is mined, updates the progress bar. </summary>
/// <param name="_collapseTimer"> The new value of the collapse timer. </param>
/// <param name="_maxTimer"> The max value of the collapse timer. </param>
void UserInterface::MinigameMenu::wallMined(void* _collapseTimer, void* _maxTimer)
{
	// Set the value of the collapse bar.
	m_collapseBar.SetValue((*static_cast<uint16_t*>(_maxTimer) - (*static_cast<uint16_t*>(_collapseTimer))));
}

/// <summary> Sets the active status of all elements. </summary>
/// <param name="_active"> The new active value. </param>
void UserInterface::MinigameMenu::setActive(const bool _active)
{
	m_bottomBar.SetActive(_active);
	m_collapseBar.SetActive(_active);
	for (uint8_t i = 0; i < 3; i++) { m_toolButtons[i].SetActive(_active); }
}
