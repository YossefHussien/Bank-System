#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace Output
{
    void PrintArray(int arr[], int Size)
    {
        for (int i = 0; i < Size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void PrintArrayWithIndex(int arr[], int Size)
    {
        for (int i = 0; i < Size; i++)
        {
            cout << "Element [" << i + 1 << "] : " << arr[i] << endl;
        }
    }

    string Tabs(short NumberOfTabs)
    {
        string Tab = "";
        for (int i = 0; i < NumberOfTabs; i++)
            Tab += "\t";
        return Tab;
    }

    void PrintLine(short Length = 40)
    {
        for (int i = 0; i < Length; i++)
            cout << "_";
        cout << endl;
    }

    void SetScreenColor(string Color)
    {
        system(("color " + Color).c_str());
    }

    void ResetScreen()
    {
        system("cls");
        system("color 0f");
    }

    void PrintMessage(string Message, string Color = "0f")
    {
        SetScreenColor(Color);
        cout << Message << endl;
    }

    void RingBell()
    {
        cout << "\a";
    }
}