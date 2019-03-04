#include "pch.h"
#include "Writer.h"

#include <fstream>

using namespace std;

namespace little_endian_io
{
	template <class Word>
	std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
	{
		for (; size; --size, value >>= 8)
			outs.put(static_cast <char> (value & 0xFF));
		return outs;
	}
}
using namespace little_endian_io;

Writer::Writer() {}

Writer::Writer(std::wstring & fileName)
{
	this->fileName = fileName;
}

void Writer::write(std::vector<sound>& toWrite) const
{
	ofstream output;
	uint32_t chunkSize, subChunk2Size, subChunk1Size;
	const uint16_t channelNum = 1, formatType = 1;
	const uint32_t sampleRate = 44100;
	const uint16_t bitsPerSample = 2 * 8;
	const uint32_t byteRate = bitsPerSample * sampleRate * channelNum / 8;
	const uint16_t blockAlign = bitsPerSample * channelNum / 8;
	subChunk2Size = (uint32_t)toWrite.size() * bitsPerSample;
	chunkSize = subChunk2Size + 36;
	subChunk1Size = 16;

	output.open(fileName, ios::binary);

	// Write the file headers
	output << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
	write_word(output, subChunk1Size, 4);  // no extension data
	write_word(output, formatType, 2);  // PCM - integer samples
	write_word(output, channelNum, 2);  // 1 channel (stereo file)
	write_word(output, sampleRate, 4);  // samples per second (Hz)
	write_word(output, byteRate, 4);  // (Sample Rate * BitsPerSample * Channels) / 8
	write_word(output, blockAlign, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
	write_word(output, bitsPerSample, 2);  // number of bits per sample (use a multiple of 8)
	size_t data_chunk_pos = output.tellp();
	output << "data----";  // (chunk size to be filled in later)
	//Write data

	for (int i = 0; i < toWrite.size(); ++i)
	{
		write_word(output, (int)toWrite[i].getHeight(), 2);
	}

	size_t file_length = output.tellp(); // final size
	//Fix data chunk header
	output.seekp(data_chunk_pos + 4);
	write_word(output, file_length - data_chunk_pos + 8);
	// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
	output.seekp(0 + 4);
	write_word(output, file_length - 8, 4);

	output.close();
}
