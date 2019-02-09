#include "pch.h"
#include "Reader.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

std::wstring Reader::readFile(const std::wstring fileName)
{
	std::wstring result;
	size_t length = 0;
	std::wifstream file;
	file.open(fileName.c_str());
	if (!file.is_open())
	{
		std::wcout << L"Input file not valid: " << fileName << std::endl;
		system("pause");
		exit(-1);
	}
	file.seekg(0, std::ios::end);
	length = file.tellg();
	result.resize(length);
	file.seekg(0, std::ios::beg);
	file.read(&result.at(0), length);
	file.close();
	return result;
}
