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
		};

		static const wchar_t * get(ID id, Language language);
};

#endif
