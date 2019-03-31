#ifndef SDLGRAPHICS_H
#define SDLGRAPHICS_H

// Graphical includes.
#include "Graphics.h"
#include "SDL.h"

// Data includes.
#include "Rectangle.h"
#include "Point.h"
#include <string>

// Logging includes.
#include "Logger.h"

// Collection includes.
#include <map>
#include <vector>

namespace Graphics
{
	class SDLGraphics : public Graphics
	{
	public:
		SDLGraphics();
		void Initialise(int32_t, int32_t, Logging::Logger&);
		
		virtual void Clear(uint8_t, uint8_t, uint8_t);
		virtual void Clear(uint8_t, uint8_t, uint8_t, uint8_t);
		virtual void Present();

		virtual void Draw(uint16_t, uint16_t, Point);
		virtual void Draw(uint16_t, uint16_t, Point, float);

		virtual void Draw(uint16_t, uint16_t, Rectangle);
		virtual void Draw(uint16_t, uint16_t, Rectangle, float);

		virtual void Draw(uint16_t, uint16_t, Rectangle, Rectangle);

		void LoadSheetToID(std::string, uint16_t, int32_t);
		void LoadSheetToID(std::string, uint16_t, std::vector<Rectangle>);

	private:
		std::map<uint16_t, std::vector<SDL_Texture*>>	m_sheets;

		SDL_Renderer*							m_renderer;
		SDL_Window*								m_window;

		SDL_Rect createRectFromTexture(int32_t, int32_t, SDL_Texture*);
		SDL_Rect createRect(int32_t, int32_t, int32_t, int32_t);
		SDL_Rect convertRect(Rectangle);
	};
}

#endif