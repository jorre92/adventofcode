#pragma once
#include <string>

class Skier
{
private:
	int _slope;
	int _speed;
	int _currentDistance;
	int _numberOfTrees;
public: 
	Skier(int, int);
	void Skiing(const std::string&);
	int TreesHit() const;
};

