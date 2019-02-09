#pragma once

#include <string>
#include <vector>
#include "music.h"


class Writer
{
public:
	Writer();
	Writer(std::wstring &fileName);
	void write(std::vector<sound>& toWrite) const;
private:
	std::wstring fileName;
};

