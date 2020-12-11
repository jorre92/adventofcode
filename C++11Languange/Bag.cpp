#include "Bag.h"


Bag::Bag() : _color("none")
{

}

Bag::Bag(std::string color) : _color(color)
{

}

void Bag::Rule(std::string color, int amount)
{	
	if (_rules.find(color) != _rules.end())
	{
		_rules[color] += amount;
	}
	else
	{
		_rules[color] = amount;
	}
}

bool Bag::operator==(const Bag& otherBag) const
{
	return this->_color == otherBag.Color();
}

bool Bag::operator==(const std::string& color) const
{
	return color == _color;
}

std::string Bag::Color() const
{
	return _color;
}

std::map<std::string, int> Bag::Rules() const
{
	return _rules;
}

bool Bag::CanHoldGoldBagDirectly() const
{
	for (auto& rule : _rules)
	{
		if (rule.first == "shiny gold")
		{
			return true;
		}
	}

	return false;
}
