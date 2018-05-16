// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef IMAGES_H
#define IMAGES_H

#include "image.h"

namespace Images
{
	class Buttons final
	{
		public:
			Buttons() = delete;

			static const Image & backButton();
			static const Image & statisticsButton();
			static const Image & tripButton();
		private:
	};
}

#endif
