#include "Skier.h"

Skier::Skier(int slope, int speed) : _slope(slope), _speed(speed), _currentDistance(0), _numberOfTrees(0)
{
}

void Skier::Skiing(const std::string& skiMap)
{
	if ((_currentDistance % _speed) == 0)
	{
		auto currentposition = _slope * _currentDistance / _speed;

		_numberOfTrees += skiMap[currentposition % skiMap.size()] == '#' ? 1 : 0;
	}

	_currentDistance += 1;
}

int Skier::TreesHit() const
{
	return _numberOfTrees;
}
