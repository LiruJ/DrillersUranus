#ifndef GRAPHICS_H
#define GRAPHICS_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"
#include "Colour.h"

// Utility includes.
#include <string>

namespace Graphics
{
	/// <summary> Represents a system that draws loaded sprites to the screen in various ways. </summary>
	class Graphics
	{
	public:
		virtual ~Graphics() {}

		/// <summary> Clears the screen with the given colour. </summary>
		/// <param name="_colour"> The colour to which to clear. </param>
		virtual void Clear(Colour _colour) = 0;

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
		/// <param name="_destination"> The destination. <see cref="Rectangle"/>. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Rectangle _destination) = 0;

		/// <summary> Draws the given texture from the given sheet at the given destination. and rotation. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_destination"> The destination. <see cref="Rectangle"/>. </param>
		/// <param name="_rotation"> The rotation in radians. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Rectangle _destination, float_t _rotation) = 0;

		/// <summary> Draws the given texture from the given sheet at the given destination. from the given source. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_destination"> The destination. <see cref="Rectangle"/>. </param>
		/// <param name="_source"> The source <see cref="Rectangle"/>. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Rectangle _destination, Rectangle _source) = 0;

		/// <summary> Draws the given texture from the given sheet at the given destination. and rotation from the given source. </summary>
		/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
		/// <param name="_textureID"> The ID of the texture itself. </param>
		/// <param name="_destination"> The destination. <see cref="Rectangle"/>. </param>
		/// <param name="_source"> The source <see cref="Rectangle"/>. </param>
		/// <param name="_rotation"> The rotation in radians. </param>
		virtual void Draw(uint16_t _sheetID, uint16_t _textureID, Rectangle _destination, Rectangle _source, float_t _rotation) = 0;

		/// <summary> Draws the given string with the given font at the given position and colour. </summary>
		/// <param name="_fontID"> The ID of the font. </param>
		/// <param name="_text"> The text to write. </param>
		/// <param name="_position"> The position. </param>
		/// <param name="_colour"> The colour. </param>
		virtual void DrawString(uint16_t _fontID, std::string _text, Point _position, Colour _colour) = 0;

		/// <summary> Draws the given string with the given font at the given position and colour. </summary>
		/// <param name="_fontID"> The ID of the font. </param>
		/// <param name="_text"> The text to write. </param>
		/// <param name="_destination"> The destination. <see cref="Rectangle"/>. </param>
		/// <param name="_colour"> The colour. </param>
		virtual void DrawString(uint16_t _fontID, std::string _text, Rectangle _destination, Colour _colour) = 0;

		/// <summary> The number of frames drawn in a second. </summary>
		int32_t m_framesPerSecond = 30;
	};
}
#endif