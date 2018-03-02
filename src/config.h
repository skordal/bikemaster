// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef CONFIG_H
#define CONFIG_H

// GUI language:
#define CONFIG_GUI_LANGUAGE	Strings::Language::NORWEGIAN

// Delay timer IRQ priority
#define CONFIG_DELAY_TIMER_IRQ_PRIORITY 8
#define CONFIG_GUI_REDRAW_IRQ_PRIORITY	15

// Framebuffer addresses:
#define CONFIG_FRAMEBUFFER_WIDTH		480
#define CONFIG_FRAMEBUFFER_HEIGHT		272
#define CONFIG_FRAMEBUFFER_ADDRESS(n)	reinterpret_cast<void *>(\
	0xc0000000 + (n * sizeof(StaticFramebuffer<CONFIG_FRAMEBUFFER_WIDTH, CONFIG_FRAMEBUFFER_HEIGHT>)))

#endif
