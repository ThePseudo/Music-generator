#include "pch.h"
#include "music.h"
#include "BasicMath.h"

#include <sstream>
#include <iostream>

using namespace std;


const int32_t sineBase = 0;
const int32_t sineTable[] =
{
-8,
-4,
4,
4,
12,
16,
20,
22,
28,
36,
40,
48,
54,
60,
76,
80,
100,
124,
136,
144,
160,
168,
176,
196,
208,
220,
236,
240,
248,
252,
264,
268,
272,
284,
292,
300,
308,
316,
324,
328,
332,
344,
348,
356,
364,
368,
372,
376,
388,
392,
396,
404,
408,
416,
420,
424,
436,
440,
444,
448,
456,
458,
460,
464,
468,
464,
468,
472,
476,
480,
488,
492,
496,
500,
512,
516,
518,
520,
528,
532,
536,
544,
552,
556,
562,
568,
574,
580,
584,
588,
592,
596,
600,
604,
608,
611,
614,
617,
620,
626,
632,
638,
644,
648,
652,
656,
664,
668,
676,
684,
696,
700,
704,
708,
712,
716,
720,
725,
731,
736,
740,
744,
748,
753,
759,
764,
770,
776,
784,
792,
808,
814,
820,
828,
836,
841,
847,
852,
860,
868,
874,
880,
888,
896,
904,
912,
920,
928,
933,
939,
944,
950,
956,
962,
968,
984,
992,
1000,
1008,
1016,
1024,
1032,
1040,
1048,
1056,
1064,
1071,
1077,
1084,
1100,
1104,
1112,
1120,
1128,
1132,
1136,
1144,
1156,
1160,
1164,
1168,
1172,
1176,
1180,
1184,
1188,
1192,
1196,
1200,
1204,
1208,
1212,
1220,
1228,
1232,
1236,
1240,
1244,
1250,
1256,
1261,
1267,
1272,
1278,
1284,
1288,
1292,
1296,
1302,
1308,
1312,
1316,
1320,
1324,
1328,
1332,
1336,
1340,
1344,
1356,
1358,
1361,
1363,
1366,
1368,
1372,
1376,
1380,
1382,
1384,
1386,
1388,
1391,
1394,
1397,
1400,
1402,
1404,
1406,
1408,
1410,
1412,
1414,
1416,
1418,
1420,
1422,
1424,
1426,
1428,
1430,
1432,
1434,
1436,
1439,
1442,
1445,
1448,
1449,
1450,
1451,
1452,
1453,
1455,
1456,
1457,
1459,
1460,
1461,
1463,
1464,
1464,
1464,
1464,
1466,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1468,
1467,
1467,
1466,
1465,
1465,
1464,
1464,
1464,
1464,
1464,
1464,
1463,
1462,
1461,
1460,
1459,
1458,
1457,
1456,
1456,
1456,
1456,
1456,
1456,
1456,
1454,
1452,
1452,
1452,
1448,
1448,
1444,
1440,
1436,
1424,
1418,
1412,
1408,
1404,
1400,
1395,
1389,
1384,
1380,
1376,
1372,
1368,
1363,
1357,
1352,
1347,
1341,
1336,
1332,
1328,
1324,
1320,
1316,
1312,
1308,
1304,
1296,
1288,
1283,
1277,
1272,
1266,
1260,
1255,
1249,
1244,
1236,
1228,
1223,
1217,
1212,
1204,
1196,
1190,
1184,
1178,
1172,
1167,
1161,
1156,
1152,
1148,
1144,
1139,
1133,
1128,
1120,
1112,
1104,
1096,
1091,
1085,
1080,
1074,
1068,
1052,
1048,
1044,
1040,
1036,
1028,
1020,
1015,
1009,
1004,
999,
993,
988,
984,
980,
976,
972,
967,
962,
957,
952,
947,
942,
937,
932,
926,
920,
914,
908,
903,
897,
892,
887,
881,
876,
869,
863,
856,
851,
845,
840,
832,
824,
819,
813,
808,
800,
792,
786,
780,
768,
760,
754,
748,
740,
732,
728,
724,
720,
716,
711,
705,
700,
693,
687,
680,
673,
667,
660,
654,
648,
642,
636,
629,
622,
614,
607,
600,
595,
590,
585,
580,
574,
568,
562,
544,
548,
534,
528,
516,
508,
496,
484,
480,
476,
468,
460,
448,
440,
436,
424,
420,
414,
408,
396,
390,
384,
372,
364,
360,
348,
344,
340,
336,
328,
324,
320,
316,
308,
304,
300,
296,
296,
292,
282,
276,
271,
265,
260,
256,
252,
248,
248,
240,
236,
224,
216,
204,
204,
192,
188,
176,
168,
168,
164,
160,
160,
156,
152,
148,
144,
140,
140,
140,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
136,
140,
142,
144,
148,
148,
148,
156,
160,
164,
168,
172,
176,
176,
176,
180,
180,
180,
180,
184,
184,
188,
200,
204,
208,
212,
220,
232,
236,
246,
252,
268,
272,
284,
292,
300,
305,
311,
316,
320,
328,
328,
340,
348,
356,
368,
372,
376,
384,
392,
394,
396,
404,
408,
412,
416,
420,
424,
424,
428,
432,
432,
432,
432,
432,
432,
432,
432,
432,
432,
432,
432,
428,
428,
428,
424,
424,
422,
420,
420,
418,
416,
412,
412,
412,
408,
408,
408,
404,
402,
400,
400,
392,
388,
384,
380,
376,
372,
368,
364,
360,
356,
352,
348,
344,
340,
336,
332,
328,
324,
312,
308,
304,
298,
292,
280,
280,
278,
276,
268,
262,
256,
240,
232,
224,
216,
196,
190,
184,
160,
148,
142,
136,
128,
112,
104,
96,
84,
78,
72,
66,
52,
48,
44,
32,
28,
20,
12,
4,
-4,
-12,
-18,
-28,
-40,
-48,
-56,
-64,
-76,
-80,
-80,
-82,
-92,
-100,
-112,
-116,
-152,
-152,
-152,
-152,
-152,
-191,
-196,
-200,
-204,
-208,
-213,
-219,
-224,
-232,
-240,
-248,
-254,
-260,
-268,
-274,
-280,
-288,
-292,
-296,
-304,
-312,
-320,
-325,
-331,
-336,
-342,
-348,
-356,
-364,
-368,
-372,
-376,
-381,
-387,
-392,
-398,
-404,
-408,
-412,
-418,
-424,
-430,
-436,
-442,
-448,
-454,
-460,
-464,
-468,
-472,
-476,
-480,
-484,
-488,
-496,
-500,
-504,
-509,
-515,
-520,
-524,
-528,
-532,
-540,
-546,
-548,
-552,
-556,
-560,
-561,
-563,
-564,
-566,
-568,
-572,
-576,
-580,
-581,
-583,
-584,
-588,
-592,
-596,
-602,
-608,
-611,
-613,
-616,
-618,
-620,
-624,
-628,
-632,
-636,
-640,
-640,
-644,
-647,
-649,
-652,
-660,
-662,
-664,
-664,
-664,
-668,
-668,
-668,
-668,
-672,
-672,
-676,
-676,
-680,
-684,
-684,
-686,
-688,
-688,
-688,
-688,
-688,
-688,
-688,
-688,
-688,
-688,
-688,
-687,
-685,
-684,
-684,
-684,
-683,
-681,
-680,
-679,
-677,
-676,
-672,
-672,
-672,
-670,
-668,
-666,
-664,
-661,
-659,
-656,
-654,
-652,
-651,
-649,
-648,
-645,
-643,
-640,
-638,
-636,
-632,
-628,
-624,
-620,
-616,
-612,
-608,
-604,
-598,
-592,
-590,
-588,
-576,
-572,
-568,
-564,
-560,
-552,
-548,
-540,
-528,
-524,
-520,
-516,
-504,
-496,
-488,
-484,
-480,
-464,
-460,
-454,
-448,
-442,
-436,
-431,
-425,
-420,
-415,
-409,
-404,
-398,
-392,
-386,
-380,
-374,
-368,
-362,
-356,
-352,
-348,
-344,
-336,
-328,
-324,
-320,
-316,
-312,
-302,
-300,
-290,
-280,
-275,
-269,
-264,
-260,
-256,
-252,
-247,
-241,
-236,
-231,
-225,
-220,
-215,
-209,
-204,
-200,
-196,
-192,
-188,
-183,
-177,
-172,
-168,
-164,
-160,
-156,
-151,
-146,
-142,
-137,
-132,
-126,
-120,
-117,
-115,
-112,
-108,
-104,
-90,
-88,
-84,
-80,
-76,
-60,
-58,
-56,
-48,
-42,
-36,
-34,
-32,
-24,
-20,
-20,
-16,
-12,
-4,
-4
};
const size_t sineTableSize = sizeof(sineTable) / sizeof(sineTable[0]);
const int startTime = 1000;
const int avg = math::avg(sineTable, sineTableSize);

music::music() {}

music::~music()
{
	song.clear();
}

void music::createSong()
{
	double time = 0.0;
	size_t nSamples = findSongNSamples();
	song.resize(nSamples);
	float msPerSample = 1 / (float)samplesPerMs;
	for (size_t i = 0; i < song.size(); ++i)
	{
		time = (float)i;
		time = time * msPerSample;
		song[i].setTime(time);
	}

	for (auto i = channels.begin(); i != channels.end(); ++i)
	{
		compileChannel(*i);
	}
	for (size_t i = startTime; i < song.size(); ++i)
	{
		song[i].addHeight(sineBase);
	}
}

size_t music::findSongNSamples() const
{
	double maxLength = 0.0f;
	double currentChannelLength = 0.0f;
	for (int i = 0; i < channels.size(); ++i)
	{
		currentChannelLength = 0;
		for (auto j = channels[i].begin(); j != channels[i].end(); ++j)
		{
			currentChannelLength += j->getDuration();
		}
		maxLength = math::max(maxLength, currentChannelLength);
	}
	return (size_t)((maxLength + 10 * samplesPerMs) * (samplesPerMs)); // + 1 for safety
}

void music::compileChannel(std::list<note> &channel)
{
	double currentTime = 0.0;
	int32_t height;
	int32_t sineIndex;
	for (auto curNote = channel.begin(), oldNote = curNote; curNote != channel.end();)
	{
		if (curNote != channel.begin())
		{
			curNote->duration = (curNote->duration + oldNote->duration);
		}
		oldNote = curNote;
		if (++curNote == channel.end())
		{
			oldNote->duration += (startTime / samplesPerMs);
		}
	}
	
	auto curNote = channel.begin();
	double frequencyDuration = 1000 / curNote->getFrequency();
	uint32_t nStepsPerFrequency = (uint32_t)(frequencyDuration / msPerSample);
	uint32_t nCurrentStep = 0;

	for (size_t currentIndex = startTime; currentIndex < song.size(); ++currentIndex)
	{
		currentTime = msPerSample * (currentIndex - startTime);
		if (curNote->getDuration() < currentTime)
		{
			++curNote;
			if (curNote == channel.end())
			{
				break;
			}
			if (curNote->getFrequency() == 0)
			{
				nStepsPerFrequency = sineTableSize;
			}
			else
			{
				frequencyDuration = 1000 / curNote->getFrequency();
				nStepsPerFrequency = (uint32_t)(frequencyDuration / msPerSample);
			}
			nCurrentStep = 0;
		}
		sineIndex = (int32_t)(nCurrentStep++ * sineTableSize / nStepsPerFrequency);
		if (nCurrentStep == nStepsPerFrequency)
		{
			nCurrentStep = 0;
		}
		height = (sineTable[sineIndex] - avg) * 8;
		song[currentIndex].addHeight(height);
	}
	for (size_t currentIndex = 0, stepHeight = sineBase / startTime; currentIndex < startTime; ++currentIndex)
	{
		song[currentIndex].setHeight((int16_t)(currentIndex * stepHeight));
	}
}


// NOTE
note::note(const double frequency, const double duration)
{
	this->frequency = frequency;
	this->duration = duration;
}

// SOUND
sound::sound() : height(0) {}
