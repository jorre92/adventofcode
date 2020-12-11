#pragma once
#include <string>
#include <vector>
#include "Bag.h"

namespace AOC2020
{
	class AdventOfCode2020
	{
	private:
		// General help methode
		bool NextLine(std::istream&, std::string&) const;
		bool NextBatch(std::istream&, std::string&) const;
		bool NextChar(std::istream&, char&) const;
		template<typename  T> bool NextItem(std::istream&, T&) const;

		void ReadPasswordAndPolicy(const std::string&, int&, int&, char&, std::string&) const;
		bool ValidatePasswordRepeating(const std::string&) const;
		bool ValidatePasswordPosition(const std::string&) const;
		std::string UniqAnswers(const std::string&) const;
		std::string AgreedAnswers(const std::string&) const;

		bool ParseBagString(const std::string&, Bag&) const;
		bool CanContainGoldBag(const Bag&, const std::vector<Bag>&) const;
		int HowManyBagsDoIneed(const std::string&, const std::vector<Bag>&) const;

		int RunCode(const std::vector<std::pair<std::string, int>>&, std::vector<int>&, bool = false) const;

		bool FirstNonPreamble(const std::vector<long int>&, int, long int&) const;
		bool BreakPreambleEncoding(const std::vector<long int>&, long int, long int&) const;

		bool CalculateAllPossibleAdapterSetups(const std::vector<int>&, size_t&) const;
		
		bool UpdateSeatingInformation(std::vector<std::string>&, int, bool = true) const;
		bool AdjacentSeats(const std::vector<std::string>&, int, int, int&) const;
		bool AdjacentSeatsInVision(const std::vector<std::string>&, int, int, int&) const;
		bool FirstVisibleSeat(const std::vector<std::string>&, int, int, int, int, int&, int&) const;
		bool IsSeatOccupied(const std::vector<std::string>&, int, int) const;
	public:
		void DayOne() const;
		void DayTwo() const;
		void DayThree() const;
		void DayFour() const;
		void DayFive() const;
		void DaySix() const;
		void DaySeven() const;
		void DayEight() const;
		void DayNine() const;
		void DayTen() const;
		void DayEleven() const;
	};
}
