#include "SDLGraphics.h"

// Framework includes.
#include <SDL_image.h>

/// <summary> Creates the SDL Graphics object. </summary>
Graphics::SDLGraphics::SDLGraphics() : m_sheets(std::map<uint16_t, std::vector<SDL_Texture*>>()), m_fonts(std::map<uint16_t, TTF_Font*>())
{
	m_framesPerSecond = 60;
}

/// <summary> Initialise SDL and create the window and renderer. </summary>
/// <param name="_width"> The width of the window. </param>
/// <param name="_height"> The height of the window. </param>
/// <param name="_logger"> The logger service to use to log the outcome of loading. </param>
void Graphics::SDLGraphics::Initialise(const int32_t _width, const int32_t _height, Logging::Logger& _logger)
{
	// Try to initialise SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { _logger.Log("SDL initialisation failed."); }
	else { _logger.Log("SDL initialisation succeeded!"); }

	// Try to initialise SDL's IMG library.
	if (IMG_Init(IMG_INIT_PNG) < 0) { _logger.Log("SDL_Image initialisation failed."); }
	else { _logger.Log("SDL_Image initialisation succeeded!"); }

	// Try to intialise SDL's TTF library.
	if (TTF_Init() < 0) { _logger.Log("SDL_ttf initialisation failed."); }
	else { _logger.Log("SDL_ttf initialisation succeeded!"); }

	// Create the window.
	m_window = SDL_CreateWindow("Drillers of Uranus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		throw std::exception(SDL_GetError());
	}

	// Create the renderer.
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		throw std::exception(SDL_GetError());
	}

	// Set the blend mode of the renderer.
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

	// Allow the user to resize the window.
	SDL_SetWindowResizable(m_window, SDL_TRUE);
}
/// <summary> Unloads all textures and destroys the window. </summary>
void Graphics::SDLGraphics::Unload()
{
	// Unload textures.
	for (uint16_t i = 0; i < m_sheets.size(); i++)
	{
		for (uint16_t j = 0; j < m_sheets[i].size(); j++)
		{
			SDL_DestroyTexture(m_sheets[i][j]);
			m_sheets[i][j] = NULL;
		}
	}

	// Unload fonts.
	for (uint16_t i = 0; i < m_fonts.size(); i++)
	{
		TTF_CloseFont(m_fonts[i]);
		m_fonts[i] = NULL;
	}

	// Destroy the window.
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = NULL;
	m_window = NULL;

	// Quit each system.
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/// <summary> Clears the screen with the given colour. </summary>
/// <param name="_colour"> The colour to which to clear. </param>
void Graphics::SDLGraphics::Clear(const Colour _colour)
{
	SDL_SetRenderDrawColor(m_renderer, _colour.r, _colour.g, _colour.b, _colour.a);
	SDL_RenderClear(m_renderer);
}

/// <summary> Updates the screen with everything that has been drawn. </summary>
void Graphics::SDLGraphics::Present()
{
	SDL_RenderPresent(m_renderer);
}

/// <summary> Draws the given texture from the given sheet at the given position. </summary>
/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
/// <param name="_textureID"> The ID of the texture itself. </param>
/// <param name="_position"> The position on the window. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Point _position)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Create the destination rectangle.
	SDL_Rect destRect = createRectFromTexture(_position.x, _position.y, texture);

	// Draw the texture at the given position.
	SDL_RenderCopy(m_renderer, texture, NULL, &destRect);
}

/// <summary> Draws the given texture from the given sheet at the given position at the given scale. </summary>
/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
/// <param name="_textureID"> The ID of the texture itself. </param>
/// <param name="_scale"> The amount to which the texture should be scaled. </param>
/// <param name="_position"> The position on the window. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const float_t _scale, const Point _position)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Create and scale the destination rectangle.
	SDL_Rect scaledDest = createRectFromTexture(_position.x, _position.y, texture);
	scaledDest.w = ceil(scaledDest.w * _scale);
	scaledDest.h = ceil(scaledDest.h * _scale);

	// Draw the texture at the given position.
	SDL_RenderCopy(m_renderer, texture, NULL, &scaledDest);
}

/// <summary> Draws the given texture from the given sheet at the given position with the given rotation and scale. </summary>
/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
/// <param name="_textureID"> The ID of the texture itself. </param>
/// <param name="_position"> The position on the window. </param>
/// <param name="_scale"> The amount to which the texture should be scaled. </param>
/// <param name="_rotation"> The rotation in radians. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Point _position, const float_t _scale, const float_t _rotation)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Create and scale the destination rectangle.
	SDL_Rect scaledDest = createRectFromTexture(_position.x, _position.y, texture);
	scaledDest.w = ceil(scaledDest.w * _scale);
	scaledDest.h = ceil(scaledDest.h * _scale);

	// Draw the texture at the given position.
	SDL_RenderCopyEx(m_renderer, texture, NULL, &scaledDest, _rotation * (180.0f / M_PI), NULL, SDL_FLIP_NONE);
}

/// <summary> Draws the given texture from the given sheet at the given position and rotation. </summary>
/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
/// <param name="_textureID"> The ID of the texture itself. </param>
/// <param name="_position"> The position on the window. </param>
/// <param name="_rotation"> The rotation in radians. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Point _position, const float_t _rotation)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Create the destination rectangle.
	SDL_Rect destRect = createRectFromTexture(_position.x, _position.y, texture);

	// Draw the texture at the given position.
	SDL_RenderCopyEx(m_renderer, texture, NULL, &destRect, _rotation * (180.0f / M_PI), NULL, SDL_FLIP_NONE);
}

/// <summary> Draws the given texture from the given sheet at the given destination. </summary>
/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
/// <param name="_textureID"> The ID of the texture itself. </param>
/// <param name="_destination"> The destination <see cref="Rectangle"/>. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Rectangle _destination)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Draw the texture at the given position.
	SDL_RenderCopy(m_renderer, texture, NULL, &convertRect(_destination));
}

/// <summary> Draws the given texture from the given sheet at the given destination and rotation. </summary>
/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
/// <param name="_textureID"> The ID of the texture itself. </param>
/// <param name="_destination"> The destination <see cref="Rectangle"/>. </param>
/// <param name="_rotation"> The rotation in radians. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Rectangle _destination, const float_t _rotation)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Draw the texture at the given position.
	SDL_RenderCopyEx(m_renderer, texture, NULL, &convertRect(_destination), _rotation * (180.0f / M_PI), NULL, SDL_FLIP_NONE);
}

/// <summary> Draws the given texture from the given sheet at the given destination from the given source. </summary>
/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
/// <param name="_textureID"> The ID of the texture itself. </param>
/// <param name="_destination"> The destination <see cref="Rectangle"/>. </param>
/// <param name="_source"> The source <see cref="Rectangle"/>. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Rectangle _destination, const Rectangle _source)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Draw the texture at the given position.
	SDL_RenderCopy(m_renderer, texture, &convertRect(_source), &convertRect(_destination));
}

/// <summary> Draws the given texture from the given sheet at the given destination and rotation from the given source. </summary>
/// <param name="_sheetID"> The ID of the sheet from which the texture is stored. </param>
/// <param name="_textureID"> The ID of the texture itself. </param>
/// <param name="_destination"> The destination <see cref="Rectangle"/>. </param>
/// <param name="_source"> The source <see cref="Rectangle"/>. </param>
/// <param name="_rotation"> The rotation in radians. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Rectangle _destination, const Rectangle _source, const float_t _rotation)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Draw the texture at the given position.
	SDL_RenderCopyEx(m_renderer, texture, &convertRect(_source), &convertRect(_destination), _rotation * (180.0f / M_PI), NULL, SDL_FLIP_NONE);
}

/// <summary> Draws the given string with the given font at the given position and colour. </summary>
/// <param name="_fontID"> The ID of the font. </param>
/// <param name="_text"> The text to write. </param>
/// <param name="_position"> The position. </param>
/// <param name="_colour"> The colour. </param>
void Graphics::SDLGraphics::DrawString(uint16_t _fontID, std::string _text, Point _position, Colour _colour)
{
	// Get the font.
	TTF_Font* font = m_fonts[_fontID];

	// Render the text to a surface then turn that into a texture.
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, _text.c_str(), { _colour.r, _colour.g, _colour.b });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

	// Create the destination rect.
	SDL_Rect destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	TTF_SizeText(font, _text.c_str(), &destRect.w, &destRect.h);

	// Draw the text.
	SDL_RenderCopy(m_renderer, textTexture, NULL, &destRect);

	// Release the surface and texture.
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

/// <summary> Draws the given string with the given font at the given position and colour. </summary>
/// <param name="_fontID"> The ID of the font. </param>
/// <param name="_text"> The text to write. </param>
/// <param name="_destination"> The destination. <see cref="Rectangle"/>. </param>
/// <param name="_colour"> The colour. </param>
void Graphics::SDLGraphics::DrawString(uint16_t _fontID, std::string _text, Rectangle _destination, Colour _colour)
{
	// Get the font.
	TTF_Font* font = m_fonts[_fontID];

	// Render the text to a surface then turn that into a texture.
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, _text.c_str(), { _colour.r, _colour.g, _colour.b });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

	// Draw the text.
	SDL_RenderCopy(m_renderer, textTexture, NULL, &convertRect(_destination));

	// Release the surface and texture.
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

/// <summary> Loads the texture with the given filename to the given sheet ID. </summary>
/// <param name="_fileName"> The path of the texture. </param>
/// <param name="_sheetID"> The ID to with which the sheet should be saved. </param>
/// <param name="_tileSize"> The width/height of a single tile. </param>
void Graphics::SDLGraphics::LoadSheetToID(const std::string _fileName, const uint16_t _sheetID, const int32_t _tileSize)
{
	// If the given ID already has a sheet loaded, throw an error.
	if (m_sheets.count(_sheetID) > 0) { throw std::exception("Spritesheet with given ID has already been loaded."); }

	// Load the texture.
	SDL_Texture* loadedTexture = IMG_LoadTexture(m_renderer, _fileName.c_str());

	// If the loaded texture is null, throw an error.
	if (loadedTexture == nullptr) { throw std::exception("Given texture does not exist or could not be loaded."); }

	// Get the dimensions and format of the spritesheet.
	int32_t w, h;
	SDL_QueryTexture(loadedTexture, NULL, NULL, &w, &h);

	// Calculate the width and height of the sheet in tiles.
	int32_t widthInTiles = w / _tileSize;
	int32_t heightInTiles = h / _tileSize;

	// Create a new vector to hold the textures.
	m_sheets.emplace(_sheetID, std::vector<SDL_Texture*>(widthInTiles * heightInTiles));

	// Go over each tile in the sheet and add it to the vector.
	for (int32_t x = 0; x < widthInTiles; x++)
	{
		for (int32_t y = 0; y < heightInTiles; y++)
		{
			// Create a new texture for this sprite.
			SDL_Texture* spriteTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _tileSize, _tileSize);

			// Set the render target to the new texture.
			SDL_SetRenderTarget(m_renderer, spriteTexture);
			SDL_SetTextureBlendMode(spriteTexture, SDL_BLENDMODE_BLEND);

			// Draw the source from the spritesheet into the sprite texture.
			SDL_RenderCopy(m_renderer, loadedTexture, &createRect(x * _tileSize, y * _tileSize, _tileSize, _tileSize), &createRect(0, 0, _tileSize, _tileSize));

			// Save the sprite to the vector.
			m_sheets[_sheetID][x + y * widthInTiles] = spriteTexture;
		}
	}

	// Reset the render target.
	SDL_SetRenderTarget(m_renderer, NULL);

	// Destroy the original loaded texture, also set the pointer to null to prevent a dangling pointer in case this function is to be expanded upon.
	SDL_DestroyTexture(loadedTexture);
	loadedTexture = NULL;
}

/// <summary> Loads the texture with the given filename to the given sheet ID using the given rectangles as bounds. </summary>
/// <param name="_fileName"> The path of the texture. </param>
/// <param name="_sheetID"> The ID to with which the sheet should be saved. </param>
/// <param name="_textureBounds"> The bounds of each texture. </param>
void Graphics::SDLGraphics::LoadSheetToID(const std::string _fileName, const uint16_t _sheetID, const std::vector<Rectangle> _textureBounds)
{
	// If the given ID already has a sheet loaded, throw an error.
	if (m_sheets.count(_sheetID) > 0) { throw std::exception("Spritesheet with given ID has already been loaded."); }

	// Load the texture.
	SDL_Texture* loadedTexture = IMG_LoadTexture(m_renderer, _fileName.c_str());

	// If the loaded texture is null, throw an error.
	if (loadedTexture == nullptr) { throw std::exception("Given texture does not exist or could not be loaded."); }

	// Get the dimensions and format of the spritesheet.
	int32_t w, h;
	SDL_QueryTexture(loadedTexture, NULL, NULL, &w, &h);

	// Create a new vector to hold the textures.
	m_sheets.emplace(_sheetID, std::vector<SDL_Texture*>(_textureBounds.size()));

	// Go over each given bound and add it to the vector.
	for (uint32_t i = 0; i < _textureBounds.size(); i++)
	{
		// Create a new texture for this sprite.
		SDL_Texture* spriteTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _textureBounds[i].w, _textureBounds[i].h);

		// Set the render target to the new texture.
		SDL_SetRenderTarget(m_renderer, spriteTexture);
		SDL_SetTextureBlendMode(spriteTexture, SDL_BLENDMODE_BLEND);

		// Draw the source from the spritesheet into the sprite texture.
		SDL_RenderCopy(m_renderer, loadedTexture, &createRect(_textureBounds[i].x, _textureBounds[i].y, _textureBounds[i].w, _textureBounds[i].h), &createRect(0, 0, _textureBounds[i].w, _textureBounds[i].h));

		// Save the sprite to the vector.
		m_sheets[_sheetID][i] = spriteTexture;
	}

	// Reset the render target.
	SDL_SetRenderTarget(m_renderer, NULL);

	// Destroy the original loaded texture, also set the pointer to null to prevent a dangling pointer in case this function is to be expanded upon.
	SDL_DestroyTexture(loadedTexture);
	loadedTexture = NULL;
}

/// <summary> Loads the font from the given path to the given ID at the given font size in points. </summary>
/// <param name="_fileName"> The path of the font. </param>
/// <param name="_fontID"> The ID to which the font should be loaded. </param>
/// <param name="_pointSize"> The size of the font in points. </param>
void Graphics::SDLGraphics::LoadFontToID(const std::string _fileName, const uint16_t _fontID, const uint8_t _pointSize)
{
	// If the given ID has already been loaded, throw an error.
	if (m_fonts.count(_fontID) > 0) { throw std::exception("Font with given ID has already been loaded."); }

	// Load the font.
	TTF_Font* loadedFont = TTF_OpenFont(_fileName.c_str(), _pointSize);

	// If the font has not loaded correctly, throw an error.
	if (loadedFont == nullptr) { throw std::exception("Given font does not exist or could not be loaded."); }

	// Add the font to the map.
	m_fonts.emplace(_fontID, loadedFont);
}

/// <summary> Creates an <see cref="SDL_Rect"/> using the given X and Y positions along with the dimensions of the given <see cref="SDL_Texture"/>. </summary>
/// <param name="_x"> The X position. </param>
/// <param name="_y"> The Y position. </param>
/// <param name="_texture"> The texture from which the dimensions are used. </param>
/// <returns> A calculated <see cref="SDL_Rect"/>. </returns>
SDL_Rect Graphics::SDLGraphics::createRectFromTexture(const int32_t _x, const int32_t _y, SDL_Texture* _texture)
{
	// Create a rectangle and set each parameter.
	SDL_Rect rectangle;
	rectangle.x = _x;
	rectangle.y = _y;
	SDL_QueryTexture(_texture, NULL, NULL, &rectangle.w, &rectangle.h);

	// Return the rectangle.
	return rectangle;
}

/// <summary> Creates an <see cref="SDL_Rect"/> from the given values. </summary>
/// <param name="_x"> The x position. </param>
/// <param name="_y"> The y position. </param>
/// <param name="_width"> The width. </param>
/// <param name="_height"> The height. </param>
/// <returns> An <see cref="SDL_Rect"/>. </returns>
SDL_Rect Graphics::SDLGraphics::createRect(const int32_t _x, const int32_t _y, const int32_t _width, const int32_t _height)
{
	SDL_Rect rectangle;
	rectangle.x = _x;
	rectangle.y = _y;
	rectangle.w = _width;
	rectangle.h = _height;

	return rectangle;
}

/// <summary> Converts a <see cref="Rectangle"/> into an <see cref="SDL_Rect"/>. </summary>
/// <param name="_rectangle"> THe <see cref="Rectangle"/> to convert. </param>
/// <returns> The converted <see cref="SDL_Rect"/>. </returns>
SDL_Rect Graphics::SDLGraphics::convertRect(const Rectangle _rectangle)
{
	SDL_Rect rectangle;
	rectangle.x = _rectangle.x;
	rectangle.y = _rectangle.y;
	rectangle.w = _rectangle.w;
	rectangle.h = _rectangle.h;

	return rectangle;
}