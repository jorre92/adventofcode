#include <math.h>

#include "Boat.h"

void Boat::DirToInt(Direction dir, int& x, int& y)
{
	switch (dir)
	{
	case Direction::North:
		x = 0;
		y = 1;
		break;
	case Direction::East:
		x = 1;
		y = 0;
		break;
	case Direction::South:
		x = 0;
		y = -1;
		break;
	case Direction::West:
		x = -1;
		y = 0;
		break;
	default:
		break;
	}
}

Boat::Boat() : _x(0), _y(0), _xWayPoint(10), _yWayPoint(1)
{
	DirToInt(Direction::East, _dirX, _dirY);
}

Boat::Boat(int x, int y) : _x(x), _y(y), _xWayPoint(10), _yWayPoint(1)
{
	DirToInt(Direction::East, _dirX, _dirY);
}

void Boat::Rotate(float angle)
{
	int ox = _dirX;
	int oy = _dirY;
	auto radians = angle * (3.14f / -180);
	auto cosAngle = cos(radians);
	auto sinAngle = sin(radians);

	_dirX = floorf((cosAngle * ox - sinAngle * oy) + 0.5f);
	_dirY = floorf((sinAngle * ox + cosAngle * oy) + 0.5f);
}

void Boat::Move(Direction direction, int speed)
{
	int xDir, yDir;
	DirToInt(direction, xDir, yDir);

	for (int i = 0; i < speed; ++i)
	{
		_x += xDir;
		_y += yDir;
	}
}

void Boat::Forward(int speed)
{
	for (int i = 0; i < speed; ++i)
	{
		_x += _dirX;
		_y += _dirY;
	}
}

void Boat::Position(int& x, int& y) const
{
	x = _x;
	y = _y;
}

void Boat::MoveWaypoint(Direction dir, int speed)
{
	int x, y;
	DirToInt(dir, x, y);

	x *= speed;
	y *= speed;

	_xWayPoint += x;
	_yWayPoint += y;
}

void Boat::RotateWaypoint(float angle)
{
	int ox = _xWayPoint;
	int oy = _yWayPoint;
	auto radians = angle * (3.14f / -180);
	auto cosAngle = cos(radians);
	auto sinAngle = sin(radians);

	_xWayPoint = floorf((cosAngle * ox - sinAngle * oy) + 0.5f);
	_yWayPoint = floorf((sinAngle * ox + cosAngle * oy) + 0.5f);
}

void Boat::MoveTowardsWayPoint(int speed)
{
	for (int i = 0; i < speed; ++i)
	{
		_x += _xWayPoint;
		_y += _yWayPoint;
	}
}
