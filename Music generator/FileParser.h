#pragma once

#include <string>
#include <list>
#include <vector>
#include "music.h"

class FileParser
{
public:
	FileParser();
	void parseData(std::wstring &file);
	inline std::vector<std::list<note>> getNotes() { return channelNotes; }

private:
	std::wstring purifyFile(const std::wstring& data);
	std::list<std::wstring> divideChannels(const std::wstring &data);

	// channel translation
	void translateChannels();
	void translateChannel(const std::wstring &channel, const int channelNumber);

	// util
	double findNoteDuration(const std::wstring &duration, const int currentLine, const int channelNumber) const;
	double findFrequency(const std::wstring &frequency, const int currentLine, const int channelNumber) const;

	// data
	std::vector<std::list<note>> channelNotes;
	std::list<std::wstring> channelsText;
};
