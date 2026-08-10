#pragma once
#include <iostream>
#include <cmath>
using namespace std;

namespace Math
{
    bool IsEven(int Number)
    {
        return Number % 2 == 0;
    }

    bool IsOdd(int Number)
    {
        return Number % 2 != 0;
    }

    bool IsPrime(int Number)
    {
        if (Number < 2)
            return false;
        for (int i = 2; i <= Number / 2; i++)
        {
            if (Number % i == 0)
                return false;
        }
        return true;
    }

    int SumOfDigits(int Number)
    {
        int Sum = 0;
        while (Number > 0)
        {
            Sum += Number % 10;
            Number /= 10;
        }
        return Sum;
    }

    int ReverseNumber(int Number)
    {
        int Reversed = 0;
        while (Number > 0)
        {
            Reversed = Reversed * 10 + Number % 10;
            Number /= 10;
        }
        return Reversed;
    }

    bool IsPalindrome(int Number)
    {
        return Number == ReverseNumber(Number);
    }

    int CountDigits(int Number)
    {
        int Count = 0;
        while (Number > 0)
        {
            Count++;
            Number /= 10;
        }
        return Count;
    }

    int RandomNumber(int From, int To)
    {
        return rand() % (To - From + 1) + From;
    }

    int Factorial(int Number)
    {
        if (Number == 0 || Number == 1)
            return 1;
        return Number * Factorial(Number - 1);
    }



   
}