#ifndef BUTTON_H
#define BUTTON_H

// Derived includes.
#include "Frame.h"

// Service includes.
#include "Events.h"

namespace UserInterface
{
	/// <summary> Represents a button that fires an event when clicked. </summary>
	class Button : public Frame
	{
	public:
		/// <summary> Creates an empty <see cref="Button"/>. </summary>
		Button() : Frame::Frame() {}

		/// <summary> Creates a <see cref="Button"/> at the given position with the given size and sprite ID. </summary>
		/// <param name="_position"> The position. </param>
		/// <param name="_size"> the size. </param>
		/// <param name="_spriteID"> The sprite ID. </param>
		Button(const Point _position, const Point _size, const uint16_t _spriteID) : Frame::Frame(_position, _size, _spriteID) { }

		void Initialise();

		/// <summary> Sets the event. </summary>
		/// <param name="_userEvent"> The <see cref="UserEvent"/> that should be fired when the button is clicked. </param>
		/// <param name="_data"> The data this button should use. </param>
		inline void SetEvent(const Events::UserEvent _userEvent, const int32_t _data) { m_eventID = _userEvent; m_data = _data; }
	private:
		/// <summary> The ID of the event for this button to fire. </summary>
		Events::UserEvent m_eventID;

		/// <summary> The data of this button. </summary>
		/// <remarks> To avoid messing around with void pointers, this is just an int32_t. This int32_t may refer to many things, indices, sizes, booleans, etc., so a void pointer should not be required. </remarks>
		int32_t m_data;

		void handleClick(void*, void*);
	};
}
#endif