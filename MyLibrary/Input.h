#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace Input
{
    int ReadPositiveNumber(string Message)
    {
        int Number;
        do {
            cout << Message;
            cin >> Number;

            while (cin.fail())
            {
                // User didn't enter a number
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid Number, Please enter a valid one:" << endl;
                cin >> Number;
            }

        } while (Number <= 0);
        return Number;
    }

    int ReadNumber()
    {
        int Number;
      
        cin >> Number;
        while (cin.fail())
        {
            // user didn't input a number
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one:" << endl;
            cin >> Number;
        }
        return Number;
    }

    int ReadNumberInRange(string Message, int From, int To)
    {
        int Number;
        do {
            cout << Message << endl;
            cin >> Number;

            while (cin.fail())
            {
                // User didn't enter a number
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid Number, Please enter a valid one:" << endl;
                cin >> Number;
            }


        } while (Number < From || Number > To);

        return Number;
    }

    float ReadFloatNumber(string Message)
    {
        float Number;
        cout << Message << endl;
        cin >> Number;

        while (cin.fail())
        {
            // User didn't enter a number
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Please enter a valid one:" << endl;
            cin >> Number;
        }

        return Number;
    }

    char ReadCharacter(string Message)
    {
        char Character;
        cout << Message << endl;
        cin >> Character;
        return Character;
    }

    string ReadString(string Message)
    {
        string Text;
        cout << Message;
        getline(cin >> ws, Text);
        return Text;
    }

  

    bool ReadBool(string Message)
    {
        short Value;
        do {
            cout << Message << " [1]: Yes, [0]: No" << endl;
            cin >> Value;
        } while (Value < 0 || Value > 1);
        return Value == 1;
    }

    void ReadArray(int arr[], int& Size)
    {
        Size = ReadPositiveNumber("Enter array size: ");
        for (int i = 0; i < Size; i++)
        {
            cout << "Element [" << i + 1 << "] : ";
            cin >> arr[i];
        }
    }

}