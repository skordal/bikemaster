// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <cross_studio_io.h>

#include "debug.h"

Debug Debug::debugStream;

Debug & operator<<(Debug & stream, const char * string)
{
#ifdef ENABLE_DEBUG
	debug_printf(string);
#endif
	return stream;
}

Debug & operator<<(Debug & stream, unsigned int i)
{
#ifdef ENABLE_DEBUG
	debug_printf("0x%.08x", i);
#endif
	return stream;
}

Debug & operator<<(Debug & stream, float f)
{
#ifdef ENABLE_DEBUG
	debug_printf("%f", f);
#endif
	return stream;
}
