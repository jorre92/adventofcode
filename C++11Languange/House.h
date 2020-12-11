#pragma once
class House
{
private:
	int address_x;
	int address_y;
	int visited;
public:
	House(int addressX, int addressY);
	void SantaVisit();
	int Visited() const;
	bool IsMyAddress(int x, int y) const;
	void MyAddress(int& x, int& y) const;
	bool operator==(const House& house) const;
};

