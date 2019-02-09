#include "pch.h"
#include "FileParser.h"
#include "BasicMath.h"

#include <algorithm>
#include <cwchar>
#include <sstream>
#include <iostream>
#include <thread>


#include <windows.h>

using namespace std;

const wchar_t STRING_NOTE_DURATIONS[][20] =
{
	L"time_semibiscroma",
	L"time_biscroma",
	L"time_semicroma",
	L"time_croma",
	L"time_semiminima",
	L"time_minima",
	L"time_semibreve"
};

const wchar_t STRING_NOTE_FREQUENCIES[][3] =
{
	L"c",	// C
	L"c#",	// C#
	L"db",	// Db
	L"d",	// D
	L"d#",	// D#
	L"eb",	// Eb
	L"e",	// E
	L"f",	// F
	L"f#",	// F#
	L"gb",	// Gb
	L"g",	// G
	L"g#",	// G#
	L"ab",	// Ab
	L"a",	// A
	L"a#",	// A#
	L"bb",	// Bb
	L"b",	// B
	L"p"	// DO NOT SOUND
};

FileParser::FileParser()
{
}

void FileParser::parseData(std::wstring &file)
{
	std::wstring data;
	data = purifyFile(file);
	channelsText = divideChannels(data);
	data = L""; // resize data to retrieve memory
	translateChannels();
	/*
	for (auto i = channelNotes[0].begin(); i != channelNotes[0].end(); ++i)
	{
		Beep(i->getFrequency(), i->getDuration()*60000/(120*time_semiminima));
	}
	*/
}

std::wstring FileParser::purifyFile(const std::wstring& data)
{
	std::wstring result;
	std::wstringstream partials;
	wchar_t temp;
	wchar_t *comment;
	for (size_t i = 0; i != data.size(); ++i)
	{
		temp = data[i];
		comment = const_cast<wchar_t*>(&data[i]);
		if (!wcsncmp(comment, L"//", 2))
		{
			while(i < data.size())
			{
				temp = data[++i];
				if (temp == L'\n')
				{
					temp = data[++i];
					break;
				}
			}
		}
		if (temp != L'\t' && temp != L' ')
		{
			partials << temp;
		}
		if (temp == L'\0') 
			break;
	}
	result = partials.str();
	return result;
}

std::list<std::wstring> FileParser::divideChannels(const std::wstring &data)
{
	std::list<std::wstring> result;
	wchar_t* temp;
	wstringstream channelData;
	int ignore = 0;
	for (size_t i = 0; i != data.size(); ++i)
	{
		temp = const_cast<wchar_t*>(&data[i]);
		if (!wcsncmp(temp, L"{", 1))
		{
			temp = const_cast<wchar_t*>(&data[++i]);
			while (!wcsncmp(temp, L"\n", 1)) temp = const_cast<wchar_t*>(&data[++i]);
			++ignore;
			while (ignore)
			{
				while (!wcsncmp(temp, L"{", 1))
				{
					++ignore;
					temp = const_cast<wchar_t*>(&data[++i]);
				}
				while (!wcsncmp(temp, L"}", 1))
				{
					--ignore;
					temp = const_cast<wchar_t*>(&data[++i]);
				}
				if (!ignore)
				{
					break;
				}
				channelData << temp[0];
				temp = const_cast<wchar_t*>(&data[++i]);
			}
			result.push_back(channelData.str());
			channelData.str(L"");
		}
	}

	return result;
}

void FileParser::translateChannels()
{
	channelNotes.resize(channelsText.size());
	int channelNum = 0;
	for (auto i = channelsText.begin(); i != channelsText.end(); ++i)
	{
		translateChannel(*i, channelNum);
		++channelNum;
	}
	channelsText.resize(0);
}

void FileParser::translateChannel(const std::wstring &channel, const int channelNumber)
{
	std::wstring line;
	std::wstring emiLine[2];
	double duration;
	double frequency = 440.00f;
	wstringstream ss(channel);
	int currentLine = 0;
	while (getline(ss, line))
	{
		++currentLine;
		emiLine[0] = line.substr(0, line.find_first_of(L','));
		emiLine[1] = line.substr(line.find_first_of(L',') + 1, line.size());
		emiLine[1] = emiLine[1].substr(0, emiLine[1].find_first_of(L','));
		thread t([this, emiLine, currentLine, channelNumber, &duration]() 
		{
			duration = findNoteDuration(emiLine[1], currentLine, channelNumber);
		});

		//TODO: implement frequency detection based on note
		frequency = findFrequency(emiLine[0], currentLine, channelNumber);

		t.join();
		note n(frequency, duration);
		//TESTING
		//wcout << currentLine << L":\t" << n.getFrequency() << L"\t " << n.getDuration() << endl;
		//TESTING END
		channelNotes[channelNumber].push_back(n);
	}
	
}

double FileParser::findNoteDuration(const std::wstring &duration, const int currentLine, const int channelNumber) const
{
	const double beatSpan = bpsm * 1000.0 / 60.0;
	const double semibreve_duration = beatSpan;
	for (int i = 0; i < sizeof(STRING_NOTE_DURATIONS); ++i)
	{
		if (duration == STRING_NOTE_DURATIONS[i])
		{
			return durations[i] * semibreve_duration;
		}
	}
	wcout << L"ERROR IN DEFINING ONE NOTE DURATION: " << duration << endl
		<< L"LINE: " << currentLine << L"\nOF CHANNEL " << channelNumber << endl;
	system("pause");
	exit(-1);
}

double FileParser::findFrequency(const std::wstring &frequency, const int currentLine, const int channelNumber) const
{
	double result = 0.0f;
	wstring partNotes[2];
	wstring noteName, noteOctaveString;
	int noteOctave = 0;
	partNotes[1] = L"";
	partNotes[0] = frequency.substr(0, 1);
	noteOctaveString = frequency.substr(1, 2);
	if (frequency.length() > 1)
	{
		noteOctave = std::stoi(noteOctaveString);
	}
	if (frequency.length() > 2)
	{
		partNotes[1] = frequency.substr(2, 3);
	}
	noteName = partNotes[0] + partNotes[1];
	for (int i = 0; i < sizeof(STRING_NOTE_FREQUENCIES); ++i)
	{
		if (noteName == STRING_NOTE_FREQUENCIES[i])
		{
			result = octave[i] * math::pow2(noteOctave);
			return result;
		}
	}
	wcout << L"ERROR IN DEFINING THE NOTE: " << frequency << endl
		<< L"LINE: " << currentLine << L"\nOF CHANNEL " << channelNumber << endl;
	system("pause");
	exit(-1);
}
