#include "SDLGraphics.h"

// Graphical includes.
#include <SDL_image.h>

/// <summary> Creates the SDL Graphics object. </summary>
Graphics::SDLGraphics::SDLGraphics()
{
	m_sheets = std::map<uint16_t, std::vector<SDL_Texture*>>();
	m_framesPerSecond = 60;
}

/// <summary> Initialise SDL and create the window and renderer. </summary>
/// <param name="_width"> The width of the window. </param>
/// <param name="_height"> The height of the window. </param>
void Graphics::SDLGraphics::Initialise(const int32_t _width, const int32_t _height, Logging::Logger& _logger)
{
	// Try to initialise SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { _logger.Log("SDL initialization failed."); }
	else { _logger.Log("SDL initialization succeeded!"); }

	// Try to initialise SDL's IMG library.
	if (IMG_Init(IMG_INIT_PNG) < 0) { _logger.Log("SDL_Image initialization failed."); }
	else { _logger.Log("SDL_Image initialization succeeded!"); }

	// Create the window.
	m_window = SDL_CreateWindow("Experiment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		throw std::exception(SDL_GetError());
	}

	// Create the renderer.
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
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

/// <summary> Clears the screen with the given colour. </summary>
/// <param name="_red"> The <c>0</c> to <c>255</c> value for the red. </param>
/// <param name="_green"> The <c>0</c> to <c>255</c> value for the green. </param>
/// <param name="_blue"> The <c>0</c> to <c>255</c> value for the blue. </param>
void Graphics::SDLGraphics::Clear(const uint8_t _red, const uint8_t _green, const uint8_t _blue)
{
	SDL_SetRenderDrawColor(m_renderer, _red, _green, _blue, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer);
}

/// /// <summary> Clears the screen with the given colour. </summary>
/// <param name="_red"> The <c>0</c> to <c>255</c> value for the red. </param>
/// <param name="_green"> The <c>0</c> to <c>255</c> value for the green. </param>
/// <param name="_blue"> The <c>0</c> to <c>255</c> value for the blue. </param>
void Graphics::SDLGraphics::Clear(const uint8_t _red, const uint8_t _green, const uint8_t _blue, const uint8_t _alpha)
{
	SDL_SetRenderDrawColor(m_renderer, _red, _green, _blue, _alpha);
	SDL_RenderClear(m_renderer);
}

/// <summary> Updates the screen with everything that has been drawn. </summary>
void Graphics::SDLGraphics::Present()
{
	SDL_RenderPresent(m_renderer);
}

/// <summary> Draws the texture with the given ID to the given position. </summary>
/// <param name="_textureID"> The ID of the texture to draw. </param>
/// <param name="_x"> The X position. </param>
/// <param name="_y"> The Y position. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Point _position)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Create the destination rectangle.
	SDL_Rect destRect = createRectFromTexture(_position.x, _position.y, texture);

	// Draw the texture at the given position.
	SDL_RenderCopy(m_renderer, texture, NULL, &destRect);
}

/// <summary> Draws the texture with the given ID to the given position with the given rotation. </summary>
/// <param name="_textureID"> The ID of the texture to draw. </param>
/// <param name="_x"> The X position. </param>
/// <param name="_y"> The Y position. </param>
/// <param name="_rotation"> The rotation in radians. </param>
void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Point _position, const float _rotation)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Create the destination rectangle.
	SDL_Rect destRect = createRectFromTexture(_position.x, _position.y, texture);

	// Draw the texture at the given position.
	SDL_RenderCopyEx(m_renderer, texture, NULL, &destRect, _rotation * (180 / M_PI), NULL, SDL_FLIP_NONE);
}

void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Rectangle _destination)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Draw the texture at the given position.
	SDL_RenderCopy(m_renderer, texture, NULL, &convertRect(_destination));
}

void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Rectangle _destination, const float _rotation)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Draw the texture at the given position.
	SDL_RenderCopyEx(m_renderer, texture, NULL, &convertRect(_destination), _rotation * (180 / M_PI), NULL, SDL_FLIP_NONE);
}

void Graphics::SDLGraphics::Draw(const uint16_t _sheetID, const uint16_t _textureID, const Rectangle _destination, const Rectangle _source)
{
	// Get the texture from the IDs.
	SDL_Texture* texture = m_sheets[_sheetID][_textureID];

	// Draw the texture at the given position.
	SDL_RenderCopy(m_renderer, texture, &convertRect(_source), &convertRect(_destination));
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



/// <summary> Creates an <see cref="SDL_Rect"/> using the given X and Y positions along with the dimensions of the given <see cref="SDL_Texture"/>. </summary>
/// <param name="_x"> The X position. </param>
/// <param name="_y"> The Y position. </param>
/// <param name="_texture"> The texture from which the dimensions are used. </param>
/// <returns> A calculated <see cref="SDL_Rect"/>. </returns>
SDL_Rect Graphics::SDLGraphics::createRectFromTexture(const int32_t _x, const int32_t _y, SDL_Texture* _texture)
{
	// Get the width and height of the texture.
	int32_t w, h;
	SDL_QueryTexture(_texture, NULL, NULL, &w, &h);

	// Create a rectangle and set each parameter.
	SDL_Rect rectangle;
	rectangle.x = _x;
	rectangle.y = _y;
	rectangle.w = w;
	rectangle.h = h;

	// Return the rectangle.
	return rectangle;
}

SDL_Rect Graphics::SDLGraphics::createRect(const int32_t _x, const int32_t _y, const int32_t _width, const int32_t _height)
{
	SDL_Rect rectangle;
	rectangle.x = _x;
	rectangle.y = _y;
	rectangle.w = _width;
	rectangle.h = _height;

	return rectangle;
}

SDL_Rect Graphics::SDLGraphics::convertRect(const Rectangle _rectangle)
{
	SDL_Rect rectangle;
	rectangle.x = _rectangle.x;
	rectangle.y = _rectangle.y;
	rectangle.w = _rectangle.w;
	rectangle.h = _rectangle.h;

	return rectangle;
}
