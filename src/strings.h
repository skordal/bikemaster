// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef STRINGS_H
#define STRINGS_H

#include "lut.h"

class Strings final
{
	public:
		Strings() = delete;

		enum class Language
		{
			ENGLISH, NORWEGIAN
		};

		enum class ID
		{
			INITIALIZING = 0,
			SPEED,
            SPEED_UNIT,
			DISTANCE,
			DISTANCE_UNIT,
		};

		static const wchar_t * get(ID id, Language language);
		static void formatSpeedString(float speed, wchar_t * buffer, Strings::Language language);
		static void formatDistanceString(float speed, wchar_t * buffer, Strings::Language language);
};

#endif
