#include "tools.hpp"

Word GetBigEndianAddress(Word address) {
	Byte low = (address >> 8);
	Byte high = (Byte) address;

	return (((Word) high) << 8) | (Word) low;
}

Word GetLittleEndianAddress(Word address) {
	Byte low = (Byte) address;
	Byte high = (address >> 8);

	return (((Word) low) << 8) | (Word) high;
}