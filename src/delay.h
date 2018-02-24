// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef DELAY_H
#define DELAY_H

#include <cstdint>

/**
 * Delays (blocking) for a specified number of microseconds.
 * Uses timer10 to do interrupt-driven waiting.
 * @param msec Duration to wait for, in μs.
 */
void delay(uint16_t msec);

#endif
