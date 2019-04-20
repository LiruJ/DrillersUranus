#ifndef SDLGRAPHICS_H
#define SDLGRAPHICS_H

// Derived includes.
#include "Graphics.h"

// Framework includes.
#include "SDL.h"
#include <SDL_ttf.h>

// Data includes.
#include "Rectangle.h"
#include "Point.h"
#include "Colour.h"

// Service includes.
#include "Logger.h"

// Utility includes.
#include <map>
#include <vector>
#include <string>

namespace Graphics
{
	/// <summary> Represents the SDL method of drawing. </summary>
	class SDLGraphics : public Graphics
	{
	public:
		SDLGraphics();

		void Initialise(int32_t, int32_t, Logging::Logger&);
		
		void Unload();

		virtual void Clear(Colour);

		virtual void Present();

		virtual void Draw(uint16_t, uint16_t, Point);

		virtual void Draw(uint16_t, uint16_t, float_t, Point);

		virtual void Draw(uint16_t, uint16_t, Point, float_t, float_t);

		virtual void Draw(uint16_t, uint16_t, Point, float_t);

		virtual void Draw(uint16_t, uint16_t, Rectangle);

		virtual void Draw(uint16_t, uint16_t, Rectangle, float_t);

		virtual void Draw(uint16_t, uint16_t, Rectangle, Rectangle);

		virtual void Draw(uint16_t, uint16_t, Rectangle, Rectangle, float_t);

		virtual void DrawString(uint16_t, std::string, Point, Colour);

		virtual void DrawString(uint16_t, std::string, Rectangle, Colour);

		void LoadSheetToID(std::string, uint16_t, int32_t);

		void LoadSheetToID(std::string, uint16_t, std::vector<Rectangle>);

		void LoadFontToID(std::string, uint16_t, uint8_t);
	private:
		/// <summary> The texture vectors keyed by sheet ID. </summary>
		std::map<uint16_t, std::vector<SDL_Texture*>>	m_sheets;

		/// <summary> The fonts keyed by font ID. </summary>
		std::map<uint16_t, TTF_Font*>					m_fonts;

		/// <summary> The renderer. </summary>
		SDL_Renderer*									m_renderer;

		/// <summary> The window. </summary>
		SDL_Window*										m_window;

		SDL_Rect createRectFromTexture(int32_t, int32_t, SDL_Texture*);
		SDL_Rect createRect(int32_t, int32_t, int32_t, int32_t);
		SDL_Rect convertRect(Rectangle);
	};
}

#endif