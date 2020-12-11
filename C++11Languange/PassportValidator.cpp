#include "PassportValidator.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <regex>

bool PassportValidator::ValidPassport(const std::string& passportData) const
{
	bool valid = true;

	for (auto& field : _requredFields)
	{
		auto found = passportData.find(field);
		if (found == std::string::npos)
		{
			valid = false;
			break;
		}
	}

	return valid;
}

bool PassportValidator::ValidPassportImproved(const std::string& passportData) const
{
	bool valid = true;

	std::stringstream sstream(passportData);
	std::map<std::string, std::string> dataPonts;
	std::string line;

	while (sstream >> line)
	{
		std::replace(line.begin(), line.end(), ':', ' ');
		std::stringstream lineStream(line);
		std::string key;
		std::string value;

		if (lineStream >> key && lineStream >> value)
		{
			dataPonts[key] = value;
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < _requredFields.size(); ++i)
	{
		auto field = _requredFields[i];
		bool foundValid = dataPonts.find(field) != dataPonts.end();
		
		if (foundValid)
		{
			switch (i)
			{
			case 0:
				foundValid = YearCheck(dataPonts[field], 1920, 2002);
				break;
			case 1: 
				foundValid = YearCheck(dataPonts[field], 2010, 2020);
				break;
			case 2:
				foundValid = YearCheck(dataPonts[field], 2020, 2030);
				break;
			case 3: 
				foundValid = heightCheck(dataPonts[field]);
				break;
			case 4:
				foundValid = HairColorCheck(dataPonts[field]);
				break;
			case 5:
				foundValid = EyeColorCheck(dataPonts[field]);
				break;
			case 6: 
				foundValid = PassportIdCheck(dataPonts[field]);
				break;
			default:
				break;
			}
		}
		
		if(!foundValid)
		{
			valid = false;
			break;
		}
	}


	return valid;
}

bool PassportValidator::YearCheck(const std::string& year, int minYear, int maxYear) const
{
	bool valid = false;

	if (year.length() == 4)
	{
		int value = std::stoi(year);
		valid = minYear <= value && maxYear >= value;
	}

	return valid;
}

bool PassportValidator::heightCheck(const std::string& length) const
{
	bool valid = false;
	std::string height = length;

	bool cm = height.find("cm") != std::string::npos;
	bool in = height.find("in") != std::string::npos;

	height.erase(height.end() - 2, height.end());
	int heightNumeric = std::stoi(height);

	int min = cm ? 150 : 59;
	int max = cm ? 193 : 76;

	bool validLength = min <= heightNumeric && max >= heightNumeric;

	valid = (cm || in) && validLength;

	return valid;
}

bool PassportValidator::HairColorCheck(const std::string& color) const
{
	bool valid = false;

	std::regex color_regex("#[a-f0-9]{6}");
	

	std::string hairColor = color;

	if (color[0] == '#' && color.length() == 7)
	{
		valid = std::regex_search(hairColor, color_regex);
	}

	return valid;
}

bool PassportValidator::EyeColorCheck(const std::string& color) const
{
	std::vector<std::string> validColors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

	bool found = std::find(validColors.begin(), validColors.end(), color) != validColors.end();

	return found;
}

bool PassportValidator::PassportIdCheck(const std::string& pid) const
{
	bool found = false;

	std::regex regex_pid ("[0-9]{9}");

	if (pid.length() == 9)
	{
		found = std::regex_search(pid, regex_pid);
	}

	return found;
}

PassportValidator::PassportValidator()
{
	_requredFields = std::vector<std::string>();
	_requredFields.push_back("byr");
	_requredFields.push_back("iyr");
	_requredFields.push_back("eyr");
	_requredFields.push_back("hgt");
	_requredFields.push_back("hcl");
	_requredFields.push_back("ecl");
	_requredFields.push_back("pid");
}

void PassportValidator::NextPassport(std::ifstream& passportList, bool& normal, bool& improved) const
{
	std::string passportDetails;
	std::string line;
	std::getline(passportList, line, '\n');
	passportDetails = line;

	while (line != "")
	{
		std::getline(passportList, line, '\n');
		passportDetails += " " + line;

		if (passportList.eof())
		{
			break;
		}
	}
	improved = ValidPassportImproved(passportDetails);
	normal = ValidPassport(passportDetails);
}
