#include "SDLAudio.h"

/// <summary> Initialises the SDL audio systems. </summary>
/// <param name="_logger"> The logger to use for output. </param>
void Audio::SDLAudio::Initialise(Logging::Logger& _logger)
{
	// Try to initialise the mixer.
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) { _logger.Log("SDL_mixer initialisation failed."); }
	else { _logger.Log("SDL_mixer initialisation succeeded!"); }
}

/// <summary> Unloads all loaded sounds and closes the mixer. </summary>
void Audio::SDLAudio::Unload()
{
	// Unload all sounds.
	for (uint16_t i = 0; i < m_soundsByID.size(); i++) 
	{
		Mix_FreeChunk(m_soundsByID[i]);
		m_soundsByID[i] = NULL;
	}

	// Unload all sound varients.
	for (uint16_t i = 0; i < m_soundVariantsByID.size(); i++) 
	{
		for (uint16_t j = 0; j < m_soundVariantsByID[i].size(); j++)
		{
			Mix_FreeChunk(m_soundVariantsByID[i][j]);
			m_soundVariantsByID[i][j] = NULL;
		}
	}

	// Unload all songs.
	for (uint16_t i = 0; i < m_songsByID.size(); i++) 
	{
		Mix_FreeMusic(m_songsByID[i]); 
		m_songsByID[i] = NULL;
	}

	// Unload the mixer.
	Mix_Quit();
}

/// <summary> Plays the sound with the given ID. </summary>
/// <param name="_soundID"> The ID of the sound. </param>
void Audio::SDLAudio::PlaySound(const uint16_t _soundID)
{
	// Get the sound from the ID.
	Mix_Chunk* sound = m_soundsByID[_soundID];

	// Play the sound.
	Mix_PlayChannel(-1, sound, 0);
}

/// <summary> Plays a random sound from the given varied sound ID. </summary>
/// <param name="_variedSoundID"> The ID of the varied sounds. </param>
void Audio::SDLAudio::PlayRandomSound(const uint16_t _variedSoundID)
{
	// Gets a random sound from the given ID.
	Mix_Chunk* sound = m_soundVariantsByID[_variedSoundID][Random::RandomBetween(0, m_soundVariantsByID[_variedSoundID].size() - 1)];

	// Play the sound.
	Mix_PlayChannel(-1, sound, 0);
}

/// <summary> Plays a song from the given song ID. </summary>
/// <param name="_songID"> The ID of the song to play. </param>
void Audio::SDLAudio::PlaySong(const uint16_t _songID)
{
	// Get the song from the given ID.
	Mix_Music* song = m_songsByID[_songID];

	// Play the song.
	Mix_PlayMusic(song, 0);
}

/// <summary> Loads the sound at the given file path to the given ID. </summary>
/// <param name="_soundID"> The ID with which to store the sound. </param>
/// <param name="_fileName"> The path of the file to load. </param>
void Audio::SDLAudio::LoadSoundToID(const uint16_t _soundID, const std::string _fileName)
{
	// If the given ID already has a sound loaded, throw an error.
	if (m_soundsByID.count(_soundID) > 0) { throw std::exception("Sound with given ID has already been loaded."); }

	// Load the sound.
	Mix_Chunk* loadedSound = Mix_LoadWAV(_fileName.c_str());

	// If the loaded sound is null, throw an error.
	if (loadedSound == NULL) { throw std::exception("Given sound does not exist or could not be loaded."); }

	// Store the sound.
	m_soundsByID.emplace(_soundID, loadedSound);
}

/// <summary> Loads the list of file names into a single ID for variations on the same sound ID. </summary>
/// <param name="_soundID"> The sound ID. </param>
/// <param name="_fileNames"> The list of file names. </param>
void Audio::SDLAudio::LoadSoundVariantsToID(const uint16_t _soundID, const std::vector<std::string> _fileNames)
{
	// If the given ID already has sounds loaded, throw an error.
	if (m_soundVariantsByID.count(_soundID) > 0) { throw std::exception("Sounds with given ID have already been loaded."); }

	// Initialise the vector.
	m_soundVariantsByID.emplace(_soundID, std::vector<Mix_Chunk*>(_fileNames.size()));

	// Loads each file name.
	for (uint16_t i = 0; i < _fileNames.size(); i++)
	{
		// Load the sound.
		Mix_Chunk* loadedSound = Mix_LoadWAV(_fileNames[i].c_str());

		// If the loaded sound is null, throw an error.
		if (loadedSound == NULL) { throw std::exception("Given sound does not exist or could not be loaded."); }

		// Store the sound.
		m_soundVariantsByID[_soundID][i] = loadedSound;
	}
}

/// <summary> Loads the song at the given file path to the given ID. </summary>
/// <param name="_songID"> The ID with which to store the song. </param>
/// <param name="_fileName"> The path of the file to load. </param>
void Audio::SDLAudio::LoadSongToID(const uint16_t _songID, const std::string _fileName)
{
	// If the given ID already has a song loaded, throw an error.
	if (m_songsByID.count(_songID) > 0) { throw std::exception("Song with given ID has already been loaded."); }

	// Load the song.
	Mix_Music* loadedSong = Mix_LoadMUS(_fileName.c_str());

	// If the loaded song is null, throw an error.
	if (loadedSong == NULL) { throw std::exception("Given song does not exist or could not be loaded."); }

	// Store the song.
	m_songsByID.emplace(_songID, loadedSong);
}