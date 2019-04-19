#ifndef AUDIO_H
#define AUDIO_H

// Typedef includes.
#include <stdint.h>

namespace Audio
{
	/// <summary> Represents an interfaced audio manager which allows only for audio to be played or stopped. </summary>
	class Audio
	{
	public:
		virtual ~Audio() {}

		/// <summary> Plays the sound with the given ID. </summary>
		/// <param name="_soundID"> The ID of the sound to play. </param>
		virtual void PlaySound(uint16_t _soundID) = 0;

		/// <summary> Plays a random sound from the given varied sound ID. </summary>
		/// <param name="_variedSoundID"> The varied sound ID to select from. </param>
		virtual void PlayRandomSound(uint16_t _variedSoundID) = 0;

		/// <summary> Plays a song from the given song ID. </summary>
		/// <param name="_songID"> The ID of the song to play. </param>
		virtual void PlaySong(uint16_t _songID) = 0;

		/// <summary> Plays a random song from the list of loaded songs. </summary>
		virtual void PlayRandomSong() = 0;

		/// <summary> Stops the currently playing song from playing. </summary>
		virtual void StopSong() = 0;

		/// <summary> Gets the value representing the playing state of the music. </summary>
		/// <returns> <c>true</c> if the music is playing; otherwise, false. </returns>
		virtual bool IsSongPlaying() = 0;
	};
}
#endif