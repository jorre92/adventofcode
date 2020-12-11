#include "House.h"

House::House(int addressX, int addressY) : address_x(addressX), address_y(addressY), visited(0)
{
}

void House::SantaVisit()
{
	visited += 1;
}

int House::Visited() const
{
	return visited;
}

bool House::IsMyAddress(int x, int y) const
{
	return address_x == x && address_y == y;
}

void House::MyAddress(int& x, int& y) const
{
	x = address_x;
	y = address_y;
}

bool House::operator==(const House& house) const
{
	int x = 0, y = 0;
	house.MyAddress(x, y);

	return this->IsMyAddress(x, y);
}
