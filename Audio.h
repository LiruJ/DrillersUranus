#ifndef AUDIO_H
#define AUDIO_H

// Typedef includes.
#include <stdint.h>

namespace Audio
{
	class Audio
	{
	public:
		virtual ~Audio() {}

		virtual void PlaySound(uint16_t _soundID) = 0;

		virtual void PlayRandomSound(uint16_t) = 0;

		//virtual void StopSound(uint16_t _soundID) = 0;

		//virtual void PlaySong(uint16_t _songID) = 0;

		//virtual void StopSong() = 0;
	};
}
#endif