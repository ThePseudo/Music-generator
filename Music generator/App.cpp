#include "pch.h"
#include <iostream>
#include <sstream>
#include "Writer.h"
#include "Reader.h"
#include "App.h"
#include "FileParser.h"


using namespace std;

App app;

int wmain(int argc, wchar_t *argv[])
{
	if (argc > 1)
	{
		app.init(argv[1]);
	}
	else
	{
		app.init(L"");
	}

	app.run();
#ifdef _DEBUG
	system("Pause");
#endif //DEBUG
	return 0;
}

App::App(){}

App::~App(){}

void App::init(const std::wstring toRead)
{

	if (fileToRead.empty())
	{
		fileToRead = L"song.txt";
	}
	std::thread t([this]()
	{
		initOutput();
	});
	loadFile();
	t.join();
}

void App::run()
{
	Writer writer(fileToWrite);
	parser.parseData(fileData);
	fileData = L"";
	channels = parser.getNotes();
	song.setChannels(channels);
	channels.resize(0);
	song.createSong();
	std::vector<sound> s;
	s = song.getSong();
	writer.write(s);

}

void App::loadFile()
{
	fileData = Reader::readFile(fileToRead);
}

void App::initOutput()
{
	fileToWrite = fileToRead.substr(0, fileToRead.find_last_of(L"."));
	fileToWrite.append(L".WAV");
}
