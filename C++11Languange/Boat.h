#pragma once
#include <vector>

enum Direction
{
	North,
	East,
	South,
	West
};

class Boat
{
private:
	int _x, _y;
	int _xWayPoint, _yWayPoint;
	int _dirX, _dirY;

	void DirToInt(Direction, int&, int&);
public:
	Boat();
	Boat(int, int);

	void Rotate(float);
	void Move(Direction, int);
	void Forward(int);

	void Position(int&, int&) const;

	void MoveWaypoint(Direction, int);
	void RotateWaypoint(float);
	void MoveTowardsWayPoint(int);
};