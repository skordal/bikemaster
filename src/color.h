// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <cstring>

class __attribute((packed)) Color final
{
	public:
		static Color black()       { return Color(  0,   0,   0); }
		static Color white()       { return Color(255, 255, 255); }
		static Color red()         { return Color(255,   0,   0); }
		static Color green()       { return Color(  0, 255,   0); }
		static Color blue()        { return Color(  0,   0, 255); }

		Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : b(b), g(g), r(r) {}

		uint8_t getR() const { return r; }
		uint8_t getG() const { return g; }
		uint8_t getB() const { return b; }

		void setR(uint8_t r) { this->r = r; }
		void setG(uint8_t g) { this->g = g; }
		void setB(uint8_t b) { this->b = b; }

		void set(uint8_t r, uint8_t g, uint8_t b)
			{ this->r = r; this->g = g; this->b = b; }
		void set(const Color & color)
			{ r = color.getR(); g = color.getG(); b = color.getB(); }

		bool operator==(const Color & c) const { return memcmp(this, &c, sizeof(Color)) == 0; }
		bool operator!=(const Color & c) const { return !(c == *this); }

		Color & operator=(const Color & c) { memcpy(this, &c, sizeof(Color)); return *this; }
	private:
		uint8_t b, g, r;
};

static_assert(sizeof(Color) == 3);

#endif
