#ifndef SDLAUDIO_H
#define SDLAUDIO_H

// Derived includes.
#include "Audio.h"

// Framework includes.
#include <SDL_mixer.h>

// Service includes.
#include "Logger.h"

// Utility includes.
#include "Random.h"
#include <string>
#include <map>
#include <vector>

namespace Audio
{
	/// <summary> Represents an audio system for SDL. </summary>
	class SDLAudio : public Audio
	{
	public:
		SDLAudio() : m_soundsByID(std::map<uint16_t, Mix_Chunk*>()), m_songsByID(std::map<uint16_t, Mix_Music*>()), m_soundVariantsByID(std::map<uint16_t, std::vector<Mix_Chunk*>>()) { }

		void Initialise(Logging::Logger&);

		void Unload();

		virtual void PlaySound(uint16_t);

		virtual void PlayRandomSound(uint16_t);

		virtual void PlaySong(uint16_t);

		/// <summary> Plays a random song from the list of loaded songs. </summary>
		virtual void PlayRandomSong() { Mix_PlayMusic(m_songsByID[Random::RandomBetween(0, m_songsByID.size() - 1)], 0); }

		/// <summary> Stops the currently playing song from playing. </summary>
		virtual void StopSong() { Mix_HaltMusic(); }

		/// <summary> Gets the value representing the playing state of the music. </summary>
		/// <returns> <c>true</c> if the music is playing; otherwise, false. </returns>
		virtual bool IsSongPlaying() { return Mix_PlayingMusic(); };

		void LoadSoundToID(uint16_t, std::string);

		void LoadSoundVariantsToID(uint16_t, std::vector<std::string>);

		void LoadSongToID(uint16_t, std::string);
	private:
		/// <summary> The sound effects by ID. </summary>
		std::map<uint16_t, Mix_Chunk*>				m_soundsByID;

		/// <summary> Lists of sounds by ID. </summary>
		std::map<uint16_t, std::vector<Mix_Chunk*>> m_soundVariantsByID;

		/// <summary> The songs by ID. </summary>
		std::map<uint16_t, Mix_Music*>				m_songsByID;
	};
}
#endif