#include "tools.hpp"

word getBigEndianAddress(word address) {
	byte low = (address >> 8);
	byte high = (byte)address;

	return (((word)0 | (word)high) << 8) | (word)low;
}