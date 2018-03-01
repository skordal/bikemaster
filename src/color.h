// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

class Color final
{
	public:
		static Color black() { return Color(  0,   0,   0); }
		static Color white() { return Color(255, 255, 255); }
		static Color red()   { return Color(255,   0,   0); }
		static Color green() { return Color(  0, 255,   0); }
		static Color blue()  { return Color(  0,   0, 255); }

		Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255)
			: b(b), g(g), r(r), a(a) {}

		uint8_t getR() const { return r; }
		uint8_t getG() const { return g; }
		uint8_t getB() const { return b; }
		uint8_t getA() const { return a; }

		void setR(uint8_t r) { this->r = r; }
		void setG(uint8_t g) { this->g = g; }
		void setB(uint8_t b) { this->b = b; }
		void setA(uint8_t a) { this->a = a; }

		void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
			{ this->r = r; this->g = g; this->b = b; this->a = a; }
		void set(const Color & color)
			{ r = color.getR(); g = color.getG(); b = color.getB(); a = color.getA(); }
	private:
		uint8_t b, g, r, a;
};

static_assert(sizeof(Color) == 4);

#endif
