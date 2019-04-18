#ifndef SDLAUDIO_H
#define SDLAUDIO_H

// Derived includes.
#include "Audio.h"

// Framework includes.
#include "SDL_mixer.h"

// Service includes.
#include "Logger.h"

// Utility includes.
#include <string>
#include <map>
#include <vector>

namespace Audio
{
	class SDLAudio : public Audio
	{
	public:
		SDLAudio() : m_soundsByID(std::map<uint16_t, Mix_Chunk*>()), m_songsByID(std::map<uint16_t, Mix_Music*>()), m_soundVariantsByID(std::map<uint16_t, std::vector<Mix_Chunk*>>()) { }

		void Initialise(Logging::Logger&);

		virtual void PlaySound(uint16_t);

		virtual void PlayRandomSound(uint16_t);

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