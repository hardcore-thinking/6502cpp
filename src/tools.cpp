#include "tools.hpp"

word getBigEndianAddress(word address) {
	byte low = (address >> 8);
	byte high = (byte) address;

	return (((word) 0 | (word) high) << 8) | (word) low;
}

word getLittleEndianAddress(word address) {
	byte low = (byte) address;
	byte high = (address >> 8);

	return (((word) 0 | (word) low) << 8) | (word) high;
}