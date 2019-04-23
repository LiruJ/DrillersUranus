#ifndef AUDIODATA_H
#define AUDIODATA_H

namespace AudioData
{
	/// <summary> The non-variant sounds. </summary>
	enum SoundID { Collapse, GemWallCollapse, PlayerCrushed, Win, GetGem, HitGem, UseExit, UIClick };

	/// <summary> The varied sounds. </summary>
	enum VariedSoundID { Step, Hit, Smash };

	/// <summary> The music. </summary>
	enum SongID { Main, Cave };
}
#endif