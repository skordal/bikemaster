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

		Point offset(int x, int y) const { return Point(this->x + x, this->y + y); }
		Point offset(const Point & point) const { return Point(x + point.x, y + point.y); }
		Point operator+(const Point & point) const { return offset(point); }

		bool within(const Point & origin, unsigned int w, unsigned int h) const
			{ return within(origin.getX(), origin.getY(), w, h); }
		bool within(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const
			{ return (this->x >= x && this->x < x + w && this->y >= y && this->y < y + h); }
	private:
		unsigned int x, y;
};

#endif
