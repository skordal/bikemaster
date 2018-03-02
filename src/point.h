// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef POINT_H
#define POINT_H

class Point
{
	public:
		Point() : x(0), y(0) {}
		Point(unsigned int x, unsigned int y) : x(x), y(y) {}

		unsigned int getX() const { return x; }
		unsigned int getY() const { return y; }

		void setX(unsigned int x) { this->x = x; }
		void setY(unsigned int y) { this->y = y; }

		Point offset(unsigned int x, unsigned int y) const { return Point(this->x + x, this->y + y); }
	private:
		unsigned int x, y;
};

#endif
