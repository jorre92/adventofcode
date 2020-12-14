#include "MemoryController.h"

#include <iostream>

uint64_t MemoryController::TurnOnBit(uint64_t value, uint64_t bit) const
{
	return (bit | (1 << (value - 1)));
}

uint64_t MemoryController::TurnOffBit(uint64_t value, uint64_t bit) const
{
	return (bit & ~(1 << (value - 1)));
}

MemoryController::MemoryController() : _maskSetOne(0), _maskClearOne(0), _floatingBits(0)
{
}

bool MemoryController::ApplyMask(const std::string mask)
{
	_mask = mask;
	_maskClearOne = 0;
	_maskSetOne = 0;
	_floatingBits = 0;

	for (int i = 0; i < mask.size(); i++)
	{
		uint64_t bitToSet = mask.size() - i - 1;

		if (mask[i] == '1')
		{
			_maskSetOne |= (1LL << bitToSet);
		}
		else if(mask[i] == '0')
		{
			_maskClearOne |= (1LL << bitToSet);
		}
		else
		{
			_floatingBits++;
		}
	}

	return true;
}

void MemoryController::write(uint64_t memory, uint64_t value)
{
	value |= _maskSetOne;
	value &= ~_maskClearOne;

	_memory[memory] = value;
}

void MemoryController::write2(uint64_t memory, uint64_t value)
{
	if (_floatingBits != 0)
	{
		for (uint64_t permutation = 0; permutation < pow(2, _floatingBits); ++permutation)
		{
			uint64_t permutationIt = 0;
			uint64_t maskOnes = _maskSetOne;
			uint64_t maskZeros = 0;

			for (int i = _mask.size() - 1; i >= 0; --i)
			{
				if (_mask[i] == 'X')
				{
					bool bit = permutation & (1LL << permutationIt);
					uint64_t bitToSet = (_mask.size() - 1 - i);

					if (bit)
					{
						maskOnes |= (1LL << bitToSet);
					}
					else
					{
						maskZeros |= (1LL << bitToSet);
					}
					permutationIt++;
				}
			}
			memory |= maskOnes;
			memory &= ~maskZeros;
			_memory[memory] = value;
		}
	}
	else
	{
		memory |= _maskSetOne;
		_memory[memory] = value;
	}

}

uint64_t MemoryController::Sum() const
{
	uint64_t sum = 0;
	
	for (auto& _it : _memory)
	{
		sum += _it.second;
	}

	return sum;
}
