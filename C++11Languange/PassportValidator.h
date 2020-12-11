#pragma once
#include <fstream>
#include <vector>

class PassportValidator
{
private:
	std::vector<std::string> _requredFields;
	bool ValidPassport(const std::string&) const;
	bool ValidPassportImproved(const std::string&) const;
	bool YearCheck(const std::string&, int, int) const;
	bool heightCheck(const std::string&) const;
	bool HairColorCheck(const std::string&) const;
	bool EyeColorCheck(const std::string&) const;
	bool PassportIdCheck(const std::string&) const;
public:
	PassportValidator();
	void NextPassport(std::ifstream&, bool&, bool&) const;
};

