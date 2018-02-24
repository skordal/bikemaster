// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef DEBUG_H
#define DEBUG_H

class Debug final
{
	public:
		static Debug & stream() { return debugStream; }

		static constexpr const char * endl() { return "\n"; }
	private:
		static Debug debugStream;
};

Debug & operator<<(Debug & stream, const char * string);

#endif
