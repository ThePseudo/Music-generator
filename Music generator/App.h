#pragma once

#include <string>
#include "FileParser.h"
#include "music.h"
#include <Thread>
#include <list>
#include <vector>

class App
{
public:
	App();
	~App();

	void init(const std::wstring toRead);
	void run();

private:
	void loadFile();
	void initOutput();

	FileParser						parser;
	std::vector<std::list<note>>	channels;
	music							song;
	// Files
	std::wstring fileToRead;
	std::wstring fileData;
	std::wstring fileToWrite;
	std::wstring outputToWrite;
};