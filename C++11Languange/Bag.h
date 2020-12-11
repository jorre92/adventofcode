#pragma once
#include <string>
#include <map>

class Bag
{
private:
	std::string _color;
	std::map<std::string, int> _rules;
public:
	Bag();
	Bag(std::string);
	void Rule(std::string, int);
	bool operator== (const Bag&) const;
	bool operator== (const std::string&) const;
	std::string Color() const;
	std::map<std::string, int> Rules() const;
	bool CanHoldGoldBagDirectly() const;
};

