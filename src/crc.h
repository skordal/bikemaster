// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef CRC_H
#define CRC_H

#include <cstdint>

/**
 * Calculates a 32-bit CRC of the specified data.
 */
uint32_t crc32(const uint32_t * data, unsigned int size);

#endif
