#ifndef EVENTCONTEXT_H
#define EVENTCONTEXT_H

// Service includes.
#include "ServiceProvider.h"

// Utility includes.
#include "GameState.h"

namespace Events
{
	/// <summary> Represents the context of the event that has been fired. </summary>
	struct EventContext
	{
		EventContext() {}

		/// <summary> Creates a new event context with the given game state and event handler. </summary>
		/// <param name="_gameState"> The current state of the game. </param>
		/// <param name="_events"> The events handler. </param>
		EventContext(const MainGame::GameState _gameState, Services::ServiceProvider& _services) : m_gameState(_gameState), m_services(&_services), m_data1(nullptr), m_data2(nullptr) { }

		/// <summary> The state of the game when the event was fired. </summary>
		MainGame::GameState m_gameState;

		/// <summary> The service provider. </summary>
		Services::ServiceProvider* m_services;

		/// <summary> The first data pointer. </summary>
		void* m_data1;

		/// <summary> The second data pointer. </summary>
		void* m_data2;

		/// <summary> Sets the data pointers to the given values. </summary>
		/// <param name="_data1"> The first data. </param>
		/// <param name="_data2"> The second data. </param>
		/// <returns> A reference to this context after setting the data, to allow for easy chaining. </returns>
		EventContext& SetData(void* _data1, void* _data2) { m_data1 = _data1; m_data2 = _data2; return *this; }
	};
}
#endif