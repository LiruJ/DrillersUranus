#include "KeyboardControls.h"

#include <iostream>
#include <fstream>
#include <sstream>

/// <summary> Loads the given text file into the binding maps. </summary>
/// <param name="_filePath"> The path of the file to load. </param>
void Controls::KeyboardControls::LoadFromFile(const std::string _filePath)
{
	// Open the file and store the stream.
	std::ifstream inputFile(_filePath);

	// If the file was not opened, throw an error.
	if (!inputFile.is_open()) { throw std::exception("Input file was not opened successfully."); }

	// Store the current segment read from the file.
	std::string currentLine;

	// Read everything in the file.
	while (std::getline(inputFile, currentLine, ';'))
	{
		// Create a stream from the current line.
		std::istringstream currentLineStream(currentLine);

		// Read the command name first.
		std::string commandName;
		currentLineStream >> commandName;

		// Read the keycode second.
		int keyCode;
		currentLineStream >> keyCode;

		// Can't switch on strings, so just check to see if the name matches anything.
		if (commandName == "Up") { BindCommandToKey(Command::MoveUp, keyCode); }
		else if (commandName == "Down") { BindCommandToKey(Command::MoveDown, keyCode); }
		else if (commandName == "Left") { BindCommandToKey(Command::MoveLeft, keyCode); }
		else if (commandName == "Right") { BindCommandToKey(Command::MoveRight, keyCode); }
		else if (commandName == "Interact") { BindCommandToKey(Command::Interact, keyCode); }
		else if (commandName == "Swing") { BindCommandToKey(Command::Swing, keyCode); }
	}
}
