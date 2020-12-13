#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <math.h>

#include "AdventOfCode2020.h"
#include "Skier.h"
#include "PassportValidator.h"
#include "Boat.h"
#include "../lib/InfInt.h"

/*PRIVATE FUNCTIONS*/

bool AOC2020::AdventOfCode2020::NextLine(std::istream& stream, std::string& line) const
{
	line = "";

	if (stream.eof())
	{
		return false;
	}

	std::getline(stream, line);

	return true;
}

bool AOC2020::AdventOfCode2020::NextBatch(std::istream& stream, std::string& batch) const
{
	batch = "";

	if (stream.eof())
	{
		return false;
	}

	std::string line;

	while (NextLine(stream, line))
	{
		if (line == "")
		{
			return true;
		}

		batch += line + "\n";
	}

	return true;
}

bool AOC2020::AdventOfCode2020::NextChar(std::istream& stream, char& character) const
{
	if (stream.eof())
	{
		return false;
	}

	if (!(stream >> character))
	{
		return false;
	}

	return true;
}

template<typename  T>
bool AOC2020::AdventOfCode2020::NextItem(std::istream& stream, T& item) const
{
	if (stream.eof())
	{
		return false;
	}

	if (!(stream >> item))
	{
		return false;
	}

	return true;
}

void AOC2020::AdventOfCode2020::ReadPasswordAndPolicy(const std::string& line, int& valueOne, int& valueTwo, char& character, std::string& password) const
{
	std::string newLine = line;

	std::replace(newLine.begin(), newLine.end(), '-', ' ');
	std::replace(newLine.begin(), newLine.end(), ':', ' ');

	std::stringstream sstream(newLine);

	sstream >> valueOne;
	sstream >> valueTwo;
	sstream >> character;
	sstream >> password;
}

bool AOC2020::AdventOfCode2020::ValidatePasswordRepeating(const std::string& passwordAndPolicy) const
{
	int min, max;
	char character;
	std::string password;

	ReadPasswordAndPolicy(passwordAndPolicy, min, max, character, password);

	auto numberOfRepeats = 0;

	for (auto& _char : password)
	{
		numberOfRepeats += _char == character ? 1 : 0;
	}

	return min <= numberOfRepeats && max >= numberOfRepeats;
}

bool AOC2020::AdventOfCode2020::ValidatePasswordPosition(const std::string& passwordAndPolicy) const
{
	int first, second;
	char character;
	std::string password;

	ReadPasswordAndPolicy(passwordAndPolicy, first, second, character, password);

	auto firstPos = password[first - 1];
	auto secondPos = password[second - 1];


	return (firstPos == character) != (secondPos == character);
}

std::string AOC2020::AdventOfCode2020::UniqAnswers(const std::string& groupAnswers) const
{
	std::string answers = groupAnswers;
	std::string uniqueAnswers = "";

	for (char& character : answers)
	{
		if (uniqueAnswers.find(character) == std::string::npos && character != '\n')
		{
			uniqueAnswers += character;
		}
	}

	return uniqueAnswers;
}

std::string AOC2020::AdventOfCode2020::AgreedAnswers(const std::string& groupAnswers) const
{
	std::stringstream sstream(groupAnswers);
	std::string survay;
	std::string agreedAnswers;
	
	if (sstream >> survay)
	{
		agreedAnswers = survay;
	}

	while (sstream >> survay)
	{
		std::string agreed;

		for (char& character : survay)
		{
			if (agreedAnswers.find(character) != std::string::npos && 
				agreed.find(character) == std::string::npos)
			{
				agreed += character;
			}
		}

		agreedAnswers = agreed;
	}

	return agreedAnswers;
}

bool AOC2020::AdventOfCode2020::ParseBagString(const std::string& unparesedString, Bag& bag) const
{
	std::string word;
	std::string color[2];

	std::stringstream stream(unparesedString);

	NextItem(stream, color[0]);
	NextItem(stream, color[1]);

	bag = Bag(color[0] + " " + color[1]);

	NextItem(stream, word);
	NextItem(stream, word);

	if (NextItem(stream, word))
	{
		int numbers = 0;
		try
		{
			numbers = std::stoi(word);
		}
		catch (const std::exception&)
		{
			return true;
		}

		NextItem(stream, color[0]);
		NextItem(stream, color[1]);

		bag.Rule(color[0] + " " + color[1], numbers);
	}

	while (NextItem(stream, word))
	{
		if (NextItem(stream, word))
		{
			int numbers = 0;
			try
			{
				numbers = std::stoi(word);
			}
			catch (const std::exception&)
			{
				return true;
			}
			NextItem(stream, color[0]);
			NextItem(stream, color[1]);

			bag.Rule(color[0] + " " + color[1], numbers);
		}
	}

	return true;
}

bool AOC2020::AdventOfCode2020::CanContainGoldBag(const Bag& bag, const std::vector<Bag>& rules) const
{
	if (bag.CanHoldGoldBagDirectly())
	{
		return true;
	}

	auto bagRules = bag.Rules();

	for (auto rule : bagRules)
	{
		auto found = std::find(rules.begin(), rules.end(), rule.first);
		
		if (found != rules.end() && CanContainGoldBag((*found), rules))
		{
			return true;
		}
	}

	return false;
}

int AOC2020::AdventOfCode2020::HowManyBagsDoIneed(const std::string& bagColor, const std::vector<Bag>& rules) const
{
	int bags = 0;

	auto bag = *std::find(rules.begin(), rules.end(), bagColor);
	auto bagRules = bag.Rules();

	for (auto& rule : bagRules)
	{
		bags += HowManyBagsDoIneed(rule.first, rules) * rule.second  + rule.second;
	}

	return bags;
}

int AOC2020::AdventOfCode2020::RunCode(const std::vector<std::pair<std::string, int>>& code, std::vector<int>& stackTrace, bool debug) const
{
	int value = 0;
	int line = 0;

	while (true)
	{
		if (line > code.size()-1 || line < 0)
		{
			break;
		}

		auto instruction = code[line];

		if (std::find(stackTrace.begin(), stackTrace.end(), line) != stackTrace.end())
		{
			stackTrace.push_back(line);

			std::cout << "Program loop found at code instruction " << line << " the accumilator value is at " << value << std::endl;

			return 1;
		}

		stackTrace.push_back(line);

		if (debug)
		{
			std::cout << "Line : " << line << " : " << instruction.first << " (" << instruction.second << ") - Accumilator : " << value << std::endl;
		}

		if (instruction.first == "acc")
		{
			value += instruction.second;
		}

		if (instruction.first == "jmp")
		{
			line += instruction.second;
		}
		else
		{
			line++;
		}
	}
	
	std::cout << "The program finnised! The accumilator value is at " << value << std::endl;

	return 0;
}

bool AOC2020::AdventOfCode2020::FirstNonPreamble(const std::vector<long int>& list, int preambleLength, long int& nonPreamble) const
{
	for (int mainIndex = preambleLength; mainIndex < list.size(); ++mainIndex)
	{
		long int sum = list[mainIndex];
		bool foundMatch = false;

		auto end = list.begin() + mainIndex;

		for (int subIndexI = mainIndex - preambleLength; subIndexI < mainIndex; ++subIndexI)
		{
			long int findValue = sum - list[subIndexI];

			if(std::find(list.begin() + subIndexI + 1, end, findValue) != end)
			{
				foundMatch = true;
				break;
			}
		}

		if (!foundMatch)
		{
			nonPreamble = sum;
			return true;
		}
	}

	return false;
}

bool AOC2020::AdventOfCode2020::BreakPreambleEncoding(const std::vector<long int>& list, long int number, long int& weakness) const
{
	auto _it = std::find(list.begin(), list.end(), number);

	if (_it != list.end())
	{
		auto index = (int)(_it - list.begin());

		for (int subIndex = 0; subIndex < index; ++subIndex)
		{
			long int sum = number;
			std::vector<long int> numbers;

			for (int i = subIndex; i < index; ++i)
			{
				sum -= list[i];
				numbers.push_back(list[i]);

				if (sum <= 0)
				{
					if (sum == 0)
					{
						std::sort(numbers.begin(), numbers.end());
						
						weakness = numbers.front() + numbers.back();
						return true;
					}

					break;
				}
			}
		}
	}
	return true;
}

bool AOC2020::AdventOfCode2020::CalculateAllPossibleAdapterSetups(const std::vector<int>& adapters, size_t& possibleMatch) const
{
	std::vector<size_t> counts;
	counts.push_back(1);

	for (size_t i = 1; i < adapters.size(); ++i)
	{
		size_t count = 0;
		if (i == 1)
		{
			count = counts[i - 1] * ((adapters[i] - adapters[i - 1]) <= 3);
		}
		else if (i == 2)
		{
			count = counts[i - 1] * ((adapters[i] - adapters[i - 1]) <= 3)
				+ counts[i - 2] * ((adapters[i] - adapters[i - 2]) <= 3);
		}
		else
		{
			count = counts[i - 1] * ((adapters[i] - adapters[i - 1]) <= 3)
				+ counts[i - 2] * ((adapters[i] - adapters[i - 2]) <= 3)
				+ counts[i - 3] * ((adapters[i] - adapters[i - 3]) <= 3);
		}
		counts.push_back(count);
	}

	possibleMatch = counts.back();

	return true;
}

bool AOC2020::AdventOfCode2020::UpdateSeatingInformation(std::vector<std::string>& seats, int pickyness, bool useDirectConnectedSeats) const
{
	std::vector<std::string> newSeats;

	bool rowChanged = false;

	for (int y = 0; y < seats.size(); ++y)
	{
		auto row = seats[y];
		for (int x = 0; x < row.size(); ++x)
		{
			int ocupodeSeats = 0;

			if (useDirectConnectedSeats)
			{
				AdjacentSeats(seats, x, y, ocupodeSeats);
			}
			else
			{
				AdjacentSeatsInVision(seats, x, y, ocupodeSeats);
			}
			
			switch (row[x])
			{
			case 'L':
				if (ocupodeSeats == 0)
				{
					row[x] = '#';
				}

				break;
			case '#':
				if (ocupodeSeats >= pickyness)
				{
					row[x] = 'L';
				}

				break;
			default:
				break;
			}
		}

		if (row != seats[y])
		{
			rowChanged = true;
		}

		newSeats.push_back(row);
	}

	seats = newSeats;

	return rowChanged;
}

bool AOC2020::AdventOfCode2020::AdjacentSeats(const std::vector<std::string>& seats, int x, int y, int& ocupodeSeats) const
{
	for (int adjY = y - 1; adjY <= y + 1; ++adjY)
	{
		if (adjY < 0 || adjY >= seats.size())
		{
			continue;
		}

		for (int adjX = x - 1; adjX <= x + 1; ++adjX)
		{
			if (adjX < 0 || adjX >= seats[adjY].size() || (adjX == x && adjY == y))
			{
				continue;
			}

			if (IsSeatOccupied(seats, adjX, adjY))
			{
				ocupodeSeats++;
			}
		}
	}

	return true;
}

bool AOC2020::AdventOfCode2020::AdjacentSeatsInVision(const std::vector<std::string>& seats, int xStart, int yStart, int& ocupodeSeats) const
{
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			if (x == 0 && y == 0)
			{
				continue;
			}
			int visibleX, visibleY;

			if (FirstVisibleSeat(seats, xStart, yStart, x, y, visibleX, visibleY))
			{
				if (IsSeatOccupied(seats, visibleX, visibleY))
				{
					ocupodeSeats++;
				}
			}

		}
	}

	return true;
}

bool AOC2020::AdventOfCode2020::FirstVisibleSeat(const std::vector<std::string>& seats, int xStart, int yStart, int xDir, int yDir, int& xFound, int& yFound) const
{
	bool found = false;

	for (int i = 1; i < seats.size(); ++i)
	{
		int x = xStart + xDir * i;
		int y = yStart + yDir * i;

		if (y < 0 || y >= seats.size() || x < 0 || x >= seats[y].length())
		{
			break;
		}
		char seat = seats[y][x];

		if (seat == 'L' || seat == '#')
		{
			found = true;

			xFound = x;
			yFound = y;

			break;
		}
	}

	return found;
}

bool AOC2020::AdventOfCode2020::IsSeatOccupied(const std::vector<std::string>& seats, int x, int y) const
{
	auto seatIsOccupied = false;

	if (y >= 0 && y < seats.size() && x >= 0 && x < seats[y].size())
	{
		char seatInfo = seats[y][x];

		switch (seatInfo)
		{
		case '#':
			seatIsOccupied = true;
			break;
		default:
			break;
		}
	}

	return seatIsOccupied;
}

/*PUBLIC FUNCTIONS*/

void AOC2020::AdventOfCode2020::DayOne() const
{
	std::ifstream stream("Files//Day1.txt");
	int entry;

	std::vector<int> entries;

	// Part one.
	while (NextItem(stream, entry))
	{
		auto firstNumber = entry;
		auto secondNumber = 2020 - firstNumber;

		auto atPosition = std::find(entries.begin(), entries.end(), secondNumber);

		if (atPosition != entries.end())
		{
			std::cout << "Found pair : " << firstNumber << " and " << secondNumber << ", sum = " << firstNumber + secondNumber << ", pruduct = " << firstNumber * secondNumber << std::endl;
		}

		entries.push_back(entry);
	}
	
	// part two.
	for (int i = 0; i < entries.size(); ++i)
	{
		auto firstNumber = entries[i];

		auto left = 2020 - firstNumber;

		for (int j = i + 1; j < entries.size(); j++)
		{
			auto secondNumber = entries[j];

			if (secondNumber > left)
			{
				continue;
			}

			auto thirdNumber = left - secondNumber;

			if (std::find(entries.begin() + j + 1, entries.end(), thirdNumber) != entries.end())
			{
				std::cout << "Found tripplets : " << firstNumber << ", " << secondNumber << ", " << thirdNumber << ", sum = " << firstNumber + secondNumber + thirdNumber << ", pruduct = " << firstNumber * secondNumber * thirdNumber << std::endl;
				break;
			}
		}
	}
}

void AOC2020::AdventOfCode2020::DayTwo() const
{
	auto validPasswordsRepeat = 0;
	auto validPasswordsPosition = 0;

	std::ifstream stream("Files//Day2.txt");
	std::string passwordAndPolicy;

	while (NextLine(stream, passwordAndPolicy))
	{
		if (ValidatePasswordRepeating(passwordAndPolicy))
		{
			validPasswordsRepeat += 1;
		}

		if (ValidatePasswordPosition(passwordAndPolicy))
		{
			validPasswordsPosition += 1;
		}
	}

	std::cout << "Valid Passwords repeating : " << validPasswordsRepeat << std::endl;
	std::cout << "Valid Passwords position : " << validPasswordsPosition << std::endl;
}

void AOC2020::AdventOfCode2020::DayThree() const
{
	Skier Tom(1, 1);
	Skier Jenny(3, 1);
	Skier Philip(5, 1);
	Skier Casandra(7, 1);
	Skier Speedy(1, 2);

	auto currentPosition = 0;
	auto currentLine = 0;
	auto numberOfTrees = 0;

	std::ifstream map("Files//Day3.txt");
	std::string mapLine;

	while (NextLine(map, mapLine))
	{
		Tom.Skiing(mapLine);
		Jenny.Skiing(mapLine);
		Philip.Skiing(mapLine);
		Casandra.Skiing(mapLine);
		Speedy.Skiing(mapLine);
	}

	std::cout << "Number of trees : " << Tom.TreesHit() << std::endl;
	std::cout << "Number of trees : " << Jenny.TreesHit() << std::endl;
	std::cout << "Number of trees : " << Philip.TreesHit() << std::endl;
	std::cout << "Number of trees : " << Casandra.TreesHit() << std::endl;
	std::cout << "Number of trees : " << Speedy.TreesHit() << std::endl; 
	
	long long int calc = Tom.TreesHit();
	calc *= Jenny.TreesHit();
	calc *= Philip.TreesHit();
	calc *= Casandra.TreesHit();
	calc *= Speedy.TreesHit();
	std::cout << calc << std::endl;
	
}

void AOC2020::AdventOfCode2020::DayFour() const
{
	std::ifstream fstream("Files//Day4.txt");
	std::string line;

	PassportValidator validator;
	auto validPassports = 0;
	auto validPassportsImproved = 0;

	while (!fstream.eof())
	{
		bool normal, improved;
		validator.NextPassport(fstream, normal, improved);

		if(normal)
		{
			validPassports += 1;
		}
		if (improved)
		{
			validPassportsImproved += 1;
		}
	}

	std::cout << "Valid passports : " << validPassports << std::endl;
	std::cout << "Valid passports Improved : " << validPassportsImproved << std::endl;
}

void AOC2020::AdventOfCode2020::DayFive() const
{
	std::fstream fstream("Files//Day5.txt");
	std::string bordingInformation;
	std::vector<int> seats;
	int highestBoradingId = 0;

	for (int i = 0; i < 1024; i++)
	{
		seats.push_back(i);
	}

	while (fstream >> bordingInformation)
	{
		std::string rowInformation = bordingInformation.substr(0, 7);
		std::string seatInformation = bordingInformation.substr(7, 9);

		char row = 0;

		for (int i = 0; i < rowInformation.size(); ++i)
		{
			char character = rowInformation[i];

			if (character == 'B')
			{
				row += (char)std::pow(2, (6 - i));
			}
		}
		
		char seat = 0;

		for (int i = 0; i < seatInformation.size(); ++i)
		{
			char character = seatInformation[i];

			if (character == 'R')
			{
				seat += (char)std::pow(2, (2 - i));
			}
		}

		int seatID = row * 8 + seat;

		int boardingId = 0;

		for (int i = 0; i < bordingInformation.size(); ++i)
		{
			char character = bordingInformation[i];

			if (character == 'R' || character == 'B')
			{
				boardingId += (int)std::pow(2, (9 - i));
			}
		}

		highestBoradingId = boardingId > highestBoradingId ? boardingId : highestBoradingId;

		auto found = std::find(seats.begin(), seats.end(), boardingId);

		if (found != seats.end())
		{
			seats.erase(found);
		}

		

	}
	std::cout << "highest seat number is : " << highestBoradingId << std::endl; 
	
	for (int i = 1; i < seats.size(); ++i)
	{
		auto tempSeatId = seats[i];

		if (std::find(seats.begin(), seats.end(), tempSeatId - 1) == seats.end() &&
			std::find(seats.begin(), seats.end(), tempSeatId + 1) == seats.end())
		{

			std::cout << "your seat id is : " << tempSeatId << std::endl;
		}
	}
}

void AOC2020::AdventOfCode2020::DaySix() const
{
	std::ifstream fstream("Files//Day6.txt");
	std::string group;

	int answers = 0;
	int allAgreedanswers = 0;

	while (NextBatch(fstream, group))
	{
		std::string uniqueAnswers = UniqAnswers(group);
		std::string agreedAnswers = AgreedAnswers(group);

		answers += (int)uniqueAnswers.size();
		allAgreedanswers += (int)agreedAnswers.size();
	}

	std::cout << "Total uniq answers groups : " << answers << std::endl;
	std::cout << "Total agreed answers groups : " << allAgreedanswers << std::endl;
}

void AOC2020::AdventOfCode2020::DaySeven() const
{
	std::ifstream stream("Files//Day7.txt");
	std::string line;
	std::vector<Bag> bagRules;

	while (NextLine(stream, line))
	{
		Bag bagRule;

		if (ParseBagString(line, bagRule))
		{
			bagRules.push_back(bagRule);
		}
	}

	int holdGoldBag = 0;

	for (auto& bag : bagRules)
	{
		if (CanContainGoldBag(bag, bagRules))
		{
			holdGoldBag++;
		}
	}


	std::cout << holdGoldBag << std::endl;
	std::cout << HowManyBagsDoIneed("shiny gold", bagRules) << std::endl;
}

void AOC2020::AdventOfCode2020::DayEight() const
{
	std::ifstream stream("Files//Day8.txt");
	std::string line;
	std::vector<std::pair<std::string, int>> code;

	while (NextLine(stream, line))
	{
		std::string word;
		int value;
		std::stringstream sstream(line);

		NextItem(sstream, word);
		NextItem(sstream, value);

		std::pair<std::string, int> instruction(word, value);

		code.push_back(instruction);
	}

	std::vector<int> stackTrace;

	std::cout << RunCode(code, stackTrace) << std::endl;

	stackTrace = std::vector<int>();
	int count = 1;

	for (int i = 0; i < code.size(); i++)
	{
		auto instructionToChange = code[i];
		std::string change = "no change";

		if (instructionToChange.first == "nop") 
		{
			change = "jmp";
		}
		else if (instructionToChange.first == "jmp")
		{
			change = "nop";
		}

		if (change != "no change")
		{
			auto newCodeBase = code;

			newCodeBase[i].first = change;

			stackTrace = std::vector<int>();

			if (RunCode(newCodeBase, stackTrace) == 0)
			{
				break;
			}
		}
	}
}

void AOC2020::AdventOfCode2020::DayNine() const
{
	std::ifstream file("Files//Day9.txt");
	long int value;
	std::vector<long int> numbers;
	
	while (NextItem(file, value))
	{
		numbers.push_back(value);
	}

	if (FirstNonPreamble(numbers, 25, value))
	{
		std::cout << value << std::endl;
	}

	long int weakness;
	if (BreakPreambleEncoding(numbers, value, weakness))
	{
		std::cout << weakness << std::endl;
	}
}

void AOC2020::AdventOfCode2020::DayTen() const 
{
	std::ifstream stream("Files//Day10.txt");
	int value;
	std::vector<int> adapters;

	while (NextItem(stream, value))
	{
		adapters.push_back(value);
	}

	adapters.push_back(0);
	std::sort(adapters.begin(), adapters.end());
	adapters.push_back(adapters.back() + 3);

	int adapter_1dif, adapter_3dif;
	adapter_1dif = adapter_3dif = 0;

	int start = 0;
	for (auto adapter : adapters)
	{
		auto change = adapter - start;
		start = adapter;
		switch (change)
		{
		case 1:
			adapter_1dif++;
			break;
		case 3:
			adapter_3dif++;
			break;
		default:
			break;
		}
	}
	std::cout << "1-jolt adapter " << adapter_1dif << std::endl;
	std::cout << "3-jolt adapter " << adapter_3dif << std::endl;
	std::cout << "1-jolt times 3-jolt adapter " << adapter_1dif * adapter_3dif << std::endl;
	std::cout << "(0) to " << adapters.back() + 3 << std::endl;

	size_t possibleSetups;
	CalculateAllPossibleAdapterSetups(adapters, possibleSetups);

	std::cout << possibleSetups << std::endl;
}

void AOC2020::AdventOfCode2020::DayEleven() const 
{
	std::ifstream stream("Files//Day11.txt");
	std::vector<std::string> seats;
	std::vector<std::string> seatsPart2;
	std::string line;

	while (NextLine(stream, line))
	{
		seats.push_back(line);
		seatsPart2.push_back(line);
	}

	while (UpdateSeatingInformation(seats, 4));

	size_t occupide = 0;

	for (int y = 0; y < seats.size(); ++y)
	{
		auto row = seats[y];
		for (int x = 0; x < row.size(); ++x)
		{
			if (IsSeatOccupied(seats, x, y))
			{
				occupide++;
			}
		}
	}
	std::cout << occupide << std::endl;

	while (UpdateSeatingInformation(seatsPart2, 5, false));

	occupide = 0;

	for (int y = 0; y < seatsPart2.size(); ++y)
	{
		auto row = seatsPart2[y];
		for (int x = 0; x < row.size(); ++x)
		{
			if (IsSeatOccupied(seatsPart2, x, y))
			{
				occupide++;
			}
		}
	}
	std::cout << occupide << std::endl;
}

void AOC2020::AdventOfCode2020::DayTwelve() const
{
	std::string testFile = "Files//Tests//Day12.txt";
	std::string file = "Files//Day12.txt";

	std::fstream input(file);

	//Part one.
	Boat boat;
	char instruction;
	int boatX, boatY;

	while (NextChar(input, instruction))
	{
		int value;
		NextItem(input, value);

		switch (instruction)
		{
		case 'N': 
			boat.Move(Direction::North, value);
			break;
		case 'S':
			boat.Move(Direction::South, value);
			break;
		case 'E':
			boat.Move(Direction::East, value);
			break;
		case 'W':
			boat.Move(Direction::West, value);
			break;
		case 'L': 
			boat.Rotate(-value);
			break;
		case 'R': 
			boat.Rotate(value);
			break;
		case 'F': 
			boat.Forward(value);
			break;
		default:
			break;
		}
	}

	boat.Position(boatX, boatY);

	std::cout << "Answer Part 1 : " << abs(boatX) + abs(boatY) << std::endl;

	//Part two.
	input.clear();
	input.seekg(0, std::ios::beg);

	boat = Boat();

	while (NextChar(input, instruction))
	{
		int value;
		NextItem(input, value);

		switch (instruction)
		{
		case 'N':
			boat.MoveWaypoint(Direction::North, value);
			break;
		case 'S':
			boat.MoveWaypoint(Direction::South, value);
			break;
		case 'E':
			boat.MoveWaypoint(Direction::East, value);
			break;
		case 'W':
			boat.MoveWaypoint(Direction::West, value);
			break;
		case 'L':
			boat.RotateWaypoint(-value);
			break;
		case 'R':
			boat.RotateWaypoint(value);
			break;
		case 'F':
			boat.MoveTowardsWayPoint(value);
			break;
		default:
			break;
		}
	}

	boat.Position(boatX, boatY);

	std::cout << "Answer Part 2 : " << abs(boatX) + abs(boatY) << std::endl;
}

void AOC2020::AdventOfCode2020::DayThirteen() const
{
	// Set up
	std::string testFile = "Files//Tests//Day13.txt";
	std::string file = "Files//Day13.txt";
	std::fstream input(file);

	size_t arrivingBussTerminal;
	std::string BussTimeTable;

	NextItem(input, arrivingBussTerminal);
	NextItem(input, BussTimeTable);

	std::replace(BussTimeTable.begin(), BussTimeTable.end(), ',', ' ');
	std::stringstream TimeTableStream(BussTimeTable);

	std::vector<Buss> busses;

	{
		std::string bussNumberString;
		for (int i = 0; NextItem(TimeTableStream, bussNumberString); ++i)
		{
			if (bussNumberString != "x")
			{
				int nummer = std::stoi(bussNumberString);

				Buss buss;
				buss.bussNumber = nummer;
				buss.index = i;
				busses.push_back(buss);
			}
		}
	}

	// Part one
	{
		auto soonest = arrivingBussTerminal;
		auto soonestLine = 0;

		for (auto& buss : busses)
		{
			auto minToWait = buss.bussNumber - (arrivingBussTerminal % buss.bussNumber);
			if (minToWait < soonest)
			{
				soonest = minToWait;
				soonestLine = buss.bussNumber;
			}
		}

		std::cout << "Answer Part 1 : " << soonest * soonestLine << std::endl;
	}

	// part 2
	// find t
	// where t is:
	// t % bussNummer == bussIndex -> t + bussIndex % bussNumber == 0
	// for all busses.
	{
		InfInt t = 0;
		InfInt product = 1;

		for (auto buss : busses)
		{
			while ((t + buss.index) % buss.bussNumber != 0)
			{
				t += product;
			}

			product *= buss.bussNumber;
		}

		printf("ANSWER -> Running product :%d, Current min value: %s\n", product.toString().c_str(), t.toString().c_str());
	}
}
