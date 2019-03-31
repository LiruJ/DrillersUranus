#ifndef BUTTON_H
#define BUTTON_H

#include "Frame.h"

// Service includes.
#include "Events.h"

namespace UserInterface
{
	class Button : public Frame
	{
	public:
		Button() : Frame::Frame() {}
		Button(const Point _position, const Point _size, const unsigned short _spriteID);

		void Initialise();

		/// <summary> Sets the event. </summary>
		/// <param name="_userEvent"> The <see cref="UserEvent"/> that should be fired when the button is clicked. </param>
		/// <param name="_data"> The data this button should use. </param>
		inline void SetEvent(const UserEvent _userEvent, const int _data) { m_eventID = _userEvent; m_data = _data; }
	private:
		/// <summary> The ID of the event for this button to fire. </summary>
		UserEvent m_eventID;

		/// <summary> The data of this button. </summary>
		/// <remarks> To avoid messing around with void pointers, this is just an int. This int may refer to many things, indices, sizes, booleans, etc., so a void pointer should not be required. </remarks>
		int m_data;

		void handleClick(void*, void*);
	};
}
#endif