// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <cross_studio_io.h>

#include "debug.h"

Debug Debug::debugStream;

Debug & operator<<(Debug & stream, const char * string)
{
	debug_printf(string);
	return stream;
}