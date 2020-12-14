#pragma once
#include "../lib/InfInt.h"

#include <vector>
#include <string>
#include <map>

class MemoryController
{
private:
	uint64_t _maskClearOne;
	uint64_t _maskSetOne;
	uint64_t _floatingBits;
	std::string _mask;

	std::map<uint64_t, uint64_t> _memory;

	uint64_t TurnOnBit(uint64_t, uint64_t) const;
	uint64_t TurnOffBit(uint64_t, uint64_t) const;

public:
	MemoryController();

	bool ApplyMask(const std::string);
	void write(uint64_t, uint64_t);
	void write2(uint64_t, uint64_t);

	uint64_t Sum() const;
};

