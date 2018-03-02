// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef LUT_H
#define LUT_H

template<typename K, typename V>
class LUT
{
	public:
		struct Entry
		{
			K key;
			V value;
		};

		LUT(const Entry * entryArray, unsigned int numEntries)
			: entryArray(entryArray), numEntries(numEntries) {}

		bool get(const K & key, V * entry) const
		{
			for(unsigned int i = 0; i < numEntries; i++)
			{
				if(entryArray[i].key == key)
				{
					*entry = entryArray[i].value;
					return true;
				}
			}

			return false;
		}
	private:
		const Entry * entryArray;
		unsigned int numEntries;
};

#endif
