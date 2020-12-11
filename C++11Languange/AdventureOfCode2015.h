#pragma once
#include <string>
class AdventureOfCode2015
{
private:
    // Day Two
    int DayTwo_RectangularPrismArea(int, int, int) const;
    int DayTwo_OrderPaperGift(int, int, int) const;
    void DayTwo_GetDimentionsOfGift(const std::string&, int&, int&, int&) const;

    // Day Five
    bool DayFive_ContainsNiceVoiwels(const std::string&) const;
    bool DayFive_ContainsDoubleLetters(const std::string&) const;
    bool DayFive_DoesNotContainNaughtyCombinations(const std::string&) const;
    bool DayFive_RepeatingNoneOverLappingLetters(const std::string&) const;
    bool DayFive_RepeatingLetterWithOneLetterBetween(const std::string&) const;

public:
    // Day One
    int DayOne_SantasFloor(const std::string&) const;
    int DayOne_SantaInBasement(const std::string&) const;

    // Day Two
    int DayTwo_WrappingOrderSize(const std::string&) const;
    int DayTwo_WrappingRibbonOrderSize(const std::string&) const;

    // Day Three
    int DayThree_SantaDelivery(const std::string&) const;
    int DayThree_SantaAndRoboSantaDelivery(const std::string&) const;

    // Day four
    std::string DayFour_MySecretHash(const std::string&, int=5) const;

    // Day five
    int DayFive_HowManyNiceStringsInTheList(const std::string&) const;
    int DayFive_HowManyNiceStringsInTheListVersionTwo(const std::string&) const;

};

