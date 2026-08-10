#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace Validation
{
    bool IsPositive(int Number)
    {
        return Number > 0;
    }

    bool IsNegative(int Number)
    {
        return Number < 0;
    }

    bool IsZero(int Number)
    {
        return Number == 0;
    }

    bool IsInRange(int Number, int From, int To)
    {
        return Number >= From && Number <= To;
    }

    bool IsEqual(int Number1, int Number2)
    {
        return Number1 == Number2;
    }

    bool IsNumber(string Text)
    {
        for (char c : Text)
        {
            if (!isdigit(c))
                return false;
        }
        return !Text.empty();
    }

    bool IsLetter(char Character)
    {
        return isalpha(Character);
    }

    bool IsDigit(char Character)
    {
        return isdigit(Character);
    }

    bool IsUpperCase(char Character)
    {
        return isupper(Character);
    }

    bool IsLowerCase(char Character)
    {
        return islower(Character);
    }

    bool IsSpecialCharacter(char Character)
    {
        return !isalpha(Character) && !isdigit(Character);
    }

    bool IsEmpty(string Text)
    {
        return Text.empty();
    }

    bool IsDivisibleBy(int Number, int Divisor)
    {
        return Divisor != 0 && Number % Divisor == 0;
    }
}