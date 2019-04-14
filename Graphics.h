#ifndef GRAPHICS_H
#define GRAPHICS_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"

namespace Graphics
{
	/// <summary> Represents a system that draws loaded sprites to the screen in various ways. </summary>
	class Graphics
	{
	public:
		virtual ~Graphics() {}

		/// <summary> Clears the screen with the given colour. </summary>
		/// <param name="_red"> The <c>0</c> to <c>255</c> value for the red. </param>
		/// <param name="_green"> The <c>0</c> to <c>255</c> value for the green. </param>
		/// <param name="_blue"> The <c>0</c> to <c>255</c> value for the blue. </param>
		virtual void Clear(uint8_t _red, uint8_t _green, uint8_t _blue) = 0;

		/// /// <summary> Clears the screen with the given colour. </summary>
		/// <param name="_red"> The <c>0</c> to <c>255</c> value for the red. </param>
		/// <param name="_green"> The <c>0</c> to <c>255</c> value for the green. </param>
		/// <param name="_blue"> The <c>0</c> to <c>255</c> value for the blue. </param>
		/// <param name="_alpha"> The <c>0</c> to <c>255</c> value for the alpha. </param>
		virtual void Clear(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha) = 0;

		/// <summary> Updates the screen with everything that has been drawn. </summary>
		virtual void Present() = 0;

		/// <summary> Draws the given texture from the given sheet at the given position. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_position"> The position on the window. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Point _position) = 0;

		/// <summary> Draws the given texture from the given sheet at the given position. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_scale"> The amount to which the texture should be scaled. </param>
		/// <param name="_position"> The position on the window. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, float_t _scale, Point _position) = 0;

		/// <summary> Draws the given texture from the given sheet at the given position and rotation. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_position"> The position on the window. </param>
		/// <param name="_rotation"> The rotation in radians. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Point _position, float_t _rotation) = 0;
		
		/// <summary> Draws the given texture from the given sheet at the given destination. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_destination"> The destination <see cref="Rectangle"/>. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Rectangle _destination) = 0;

		/// <summary> Draws the given texture from the given sheet at the given destination and rotation. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_destination"> The destination <see cref="Rectangle"/>. </param>
		/// <param name="_rotation"> The rotation in radians. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Rectangle _destination, float_t _rotation) = 0;

		/// <summary> Draws the given texture from the given sheet at the given destination from the given source. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_destination"> The destination <see cref="Rectangle"/>. </param>
		/// <param name="_source"> The source <see cref="Rectangle"/>. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Rectangle _destination, Rectangle _source) = 0;

		/// <summary> Draws the given texture from the given sheet at the given destination and rotation from the given source. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_destination"> The destination <see cref="Rectangle"/>. </param>
		/// <param name="_source"> The source <see cref="Rectangle"/>. </param>
		/// <param name="_rotation"> The rotation in radians. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Rectangle _destination, Rectangle _source, float_t _rotation) = 0;

		/// <summary> The number of frames drawn in a second. </summary>
		int32_t m_framesPerSecond = 30;
	};
}
#endif