#include "MinigameMenu.h"

// Utility includes.
#include "SpriteData.h"

/// <summary> Initialises the UI. </summary>
/// <param name="_maxTimer"> The highest value of the colla[se timer. </param>
/// <param name="_events"> The events bus. </param>
void UserInterface::MinigameMenu::Initialise(const uint16_t _maxTimer, Events::Events& _events)
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
		m_toolButtons[i].Initialise(_events);
	}

	// Bind the tool changed event.
	_events.AddUserListener(Events::UserEvent::ChangeTool, std::bind(&MinigameMenu::toolChanged, this, std::placeholders::_1));

	// Bind the wall mined event.
	_events.AddUserListener(Events::UserEvent::MinedWall, std::bind(&MinigameMenu::wallMined, this, std::placeholders::_1));

	// Bind the minigame starting to this menu showing.
	_events.AddUserListener(Events::UserEvent::StartMinigame, std::bind(&MinigameMenu::show, this, std::placeholders::_1));
	_events.AddUserListener(Events::UserEvent::StartMinigame, std::bind(&MinigameMenu::start, this, std::placeholders::_1));

	// Bind the minigame stopping to this menu hiding.
	_events.AddUserListener(Events::UserEvent::StopMinigame, std::bind(&MinigameMenu::hide, this, std::placeholders::_1));
	_events.AddUserListener(Events::UserEvent::StartGame, std::bind(&MinigameMenu::hide, this, std::placeholders::_1));
}

/// <summary> Draws this menu. </summary>
/// <param name="_services"> The service provider. </param>
void UserInterface::MinigameMenu::Draw(Services::ServiceProvider& _services) const
{
	m_bottomBar.Draw(_services);
	m_collapseBar.Draw(_services);
	for (uint8_t i = 0; i < 3; i++) { m_toolButtons[i].Draw(_services); }
}

/// <summary> Fires when the wall is mined, updates the progress bar. </summary>
/// <param name="_context"> The context of the event. </param>
void UserInterface::MinigameMenu::wallMined(Events::EventContext* _context)
{
	// Set the value of the collapse bar.
	m_collapseBar.SetValue((*static_cast<uint16_t*>(_context->m_data1) - (*static_cast<uint16_t*>(_context->m_data2))));
}

/// <summary> Sets the active status of all elements. </summary>
/// <param name="_active"> The new active value. </param>
void UserInterface::MinigameMenu::setActive(const bool _active)
{
	m_bottomBar.SetActive(_active);
	m_collapseBar.SetActive(_active);
	for (uint8_t i = 0; i < 3; i++) { m_toolButtons[i].SetActive(_active); }
}
