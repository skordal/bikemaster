// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "strings.h"

// English language string table:
static const LUT<Strings::ID, const wchar_t *>::Entry englishEntries[] = {
	{ Strings::ID::INITIALIZING, L"Initializing..." },
};
static const LUT<Strings::ID, const wchar_t *> englishLUT(englishEntries, sizeof(englishEntries) / sizeof(englishEntries[0]));

// Norwegian language string table:
static const LUT<Strings::ID, const wchar_t *>::Entry norwegianEntries[] = {
	{ Strings::ID::INITIALIZING, L"Starter opp..." },
};
static const LUT<Strings::ID, const wchar_t *> norwegianLUT(norwegianEntries, sizeof(norwegianEntries) / sizeof(norwegianEntries[0]));

// Language to string table lookup table:
static LUT<Strings::Language, const LUT<Strings::ID, const wchar_t *>*>::Entry entries[] = {
	{ Strings::Language::ENGLISH, &englishLUT },
	{ Strings::Language::NORWEGIAN, &norwegianLUT },
};
static LUT<Strings::Language, const LUT<Strings::ID, const wchar_t *>*> languageLUT(entries, sizeof(entries) / sizeof(entries[0]));

const wchar_t * Strings::get(Strings::ID id, Strings::Language language)
{
	const LUT<Strings::ID, const wchar_t *> * stringTable;
	if(!languageLUT.get(language, &stringTable))
		return nullptr;

	const wchar_t * retval = nullptr;
	stringTable->get(id, &retval);
	return retval;
}
