#pragma once

#include <string>
#include <list>
#include <vector>

class note;
class sound;

const double bpsm = 120.0f; //minutes

// DURATIONS (relative tempo)
constexpr double	time_semibiscroma = 1 / 64.0;
constexpr double	time_biscroma = 1 / 32.0;
constexpr double	time_semicroma = 1 / 16.0;
constexpr double	time_croma = 1 / 8.0;
constexpr double	time_semiminima = 1 / 4.0;
constexpr double	time_minima = 1 / 2.0;
constexpr double	time_semibreve = 1.0;

const double durations[]
{
	time_semibiscroma,
	time_biscroma,
	time_semicroma,
	time_croma,
	time_semiminima,
	time_minima,
	time_semibreve
};

//FREQUENCIES (Hz)
//Each octave can be obtained multiplying any note by 2^(octave)
//octave 1
constexpr double	c0 = 16.35;
constexpr double	c0d = 17.32;
constexpr double	d0b = c0d;
constexpr double	d0 = 18.35;
constexpr double	d0d = 19.45;
constexpr double	e0b = d0d;
constexpr double	e0 = 20.60;
constexpr double	f0 = 21.83;
constexpr double	f0d = 32.12;
constexpr double	g0b = f0d;
constexpr double	g0 = 24.50;
constexpr double	g0d = 25.96;
constexpr double	a0b = g0d;
constexpr double	a0 = 27.50;
constexpr double	a0d = 29.14;
constexpr double	b0b = a0d;
constexpr double	b0 = 30.87;

constexpr double	pause = 0.00f; //No sound at all

const double octave[] = 
{
	c0,
	c0d,
	d0b,
	d0,
	d0d,
	e0b,
	e0,
	f0,
	f0d,
	g0b,
	g0,
	g0d,
	a0b,
	a0,
	a0d,
	b0b,
	b0
};


class music
{
public:
	music();
	~music();
	inline void setChannels(std::vector<std::list<note>> &ch) { channels = ch; }
	void createSong();
	inline std::vector<sound> getSong() const { return song; } 
private:
	void compileChannel(std::list<note> &channel);
	size_t findSongNSamples() const;
	// data
	const double samplesPerMs = 44.10000000000000000000;
	const double msPerSample = 0.0227272727272727272727;
	std::vector<sound>				song;
	std::vector<std::list<note>>	channels;
};


class note
{
public:
	note(const double frequency, const double duration);
	inline const double getFrequency() const { return this->frequency; }
	inline const double getDuration() const { return this->duration; }
protected:
	double			frequency;
	double			duration;
private:
	friend class music;
};


class sound
{
public:
	sound();
	inline const int32_t getHeight() const { return height; }
	inline const double getTime() const { return time; }
protected:
	inline void setTime(double time) { this->time = time; }
	inline void setHeight(int16_t height) { this->height = height; }
	inline void addHeight(int16_t height) { this->height += height; }
private:
	double		time;
	int32_t		height;
	
	friend class music;
};