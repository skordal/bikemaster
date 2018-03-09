// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <cstdio>
#include "strings.h"

// English language string table:
static const LUT<Strings::ID, const wchar_t *>::Entry englishEntries[] = {
	{ Strings::ID::INITIALIZING, L"Initializing..." },
	{ Strings::ID::SPEED, L"Speed:" },
    { Strings::ID::SPEED_UNIT, L"km/h" },
	{ Strings::ID::DISTANCE, L"Distance:" },
	{ Strings::ID::DISTANCE_UNIT, L"m" },
};
static const LUT<Strings::ID, const wchar_t *> englishLUT(englishEntries, sizeof(englishEntries) / sizeof(englishEntries[0]));

// Norwegian language string table:
static const LUT<Strings::ID, const wchar_t *>::Entry norwegianEntries[] = {
	{ Strings::ID::INITIALIZING, L"Starter opp..." },
	{ Strings::ID::SPEED, L"Hastighet:" },
    { Strings::ID::SPEED_UNIT, L"km/t" },
	{ Strings::ID::DISTANCE, L"Distanse:" },
    { Strings::ID::DISTANCE_UNIT, L"m" },
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

void Strings::formatSpeedString(float speed, wchar_t * buffer, Strings::Language language)
{
	const wchar_t * speedUnit = get(ID::SPEED_UNIT, language);
	if(speedUnit == nullptr)
		return;

	int outIndex = 0;
	char numberBuffer[6];
	snprintf(numberBuffer, sizeof(numberBuffer), "%.1f ", speed);
	for(unsigned int i = 0; numberBuffer[i] != 0; ++i)
		buffer[outIndex++] = static_cast<wchar_t>(numberBuffer[i]);

	for(unsigned int i = 0; speedUnit[i] != 0; ++i)
		buffer[outIndex++] = speedUnit[i];
	buffer[outIndex] = 0;
}

void Strings::formatDistanceString(float distance, wchar_t * buffer, Strings::Language language)
{
	const wchar_t * distanceUnit = get(ID::DISTANCE_UNIT, language);
	if(distanceUnit == nullptr)
		return;

	int outIndex = 0;
	char numberBuffer[8];
	snprintf(numberBuffer, sizeof(numberBuffer), "%.1f ", distance);
	for(unsigned int i = 0; numberBuffer[i] != 0; ++i)
		buffer[outIndex++] = static_cast<wchar_t>(numberBuffer[i]);

	for(unsigned int i = 0; distanceUnit[i] != 0; ++i)
		buffer[outIndex++] = distanceUnit[i];
	buffer[outIndex] = 0;
}
