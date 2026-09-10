#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

namespace Ystring
{

string UpperAllString(string S1)
{
	for (short i = 0; i < S1.length(); i++)
	{
		S1[i] = toupper(S1[i]);
	}
	return S1;
}

string LowerAllString(string S1)
{
	for (short i = 0; i < S1.length(); i++)
	{
		S1[i] = tolower(S1[i]);
	}
	return S1;
}

char InvertCharactarCase(char charactar)
{
	return isupper(charactar) ? tolower(charactar) : toupper(charactar);
}

string InvertAllStringLetterCase(string S1)
{
	for (short i = 0; i < S1.length(); i++)
	{
		S1[i] = InvertCharactarCase(S1[i]);
	}

	return S1;
}

short CountCapitalLetters(string S1)
{
	short Counter = 0;
	for (short i = 0; i < S1.length(); i++)
	{
		if (isupper(S1[i]))
			Counter++;
	}
	return Counter;
}

short CountSmallLetters(string S1)
{
	short Counter = 0;
	for (short i = 0; i < S1.length(); i++)
	{
		if (islower(S1[i]))
			Counter++;
	}
	return Counter;
}

short CountLetterInString(string S1, char Charactar)
{
	short Counter = 0;
	for (short i = 0; i < S1.length();i++)
	{
		if (S1[i] == Charactar)
			Counter++;
	}
	return Counter;
}

bool IsVowel(char Ch)
{
	Ch = tolower(Ch);

	return (Ch == 'a' || Ch == 'e' || Ch == 'i' || Ch == 'o' || Ch == 'u');
}

void PrintEachWordInString(string S1)
{
	string delim = " "; // delimiter
	cout << "\nYour string wrords are: \n\n";
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			cout << sWord << endl;
		}
		S1.erase(0, pos + delim.length()); /* erase() until
		positon and move to next word. */
	}
	if (S1 != "")
	{
		cout << S1 << endl; // it print last word of the string.
	}
}



vector <string> SplitString(string S1, string Delim)
{
	vector <string> vString;

	short pos = 0;
	string sWord; // define a string variable

	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word

		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length()); /* erase() until
		positon and move to next word. */

	}

	if (S1 != "")
	{
		vString.push_back(S1);
	}


	return vString;
}

string TrimLeft(string S1)
{
	for (short i = 0; i < S1.length(); i++)
	{
		if (S1[i] != ' ')
		{
			return S1.substr(i, S1.length() - i);
		}
	}

	return "";
}

string TrimRight(string S1)
{

	for (short i = S1.length() - 1; i >= 0; i--)
	{
		if (S1[i] != ' ')
		{
			return S1.substr(0, i + 1);
		}
	}

	return "";
}




string Trim(string S1)
{
	return TrimLeft(TrimRight(S1));
}

string JoinString(vector <string>& vString, string Delim)
{
	string sWord = "";

	for (string& s : vString)
	{
		sWord = sWord + s + Delim;
	}

	return sWord.substr(0, sWord.length() - Delim.length());
}

string JoinString(string arrString[], short arrlength, string Delim)
{
	string sWord = "";
	for (short i = 0;i < arrlength; i++)
	{

		sWord = sWord + arrString[i] + Delim;
	}

	return sWord.substr(0, sWord.length() - Delim.length());

}

string ReverseWordsInString(string S1)
{
	vector <string> vString;
	string S2 = "";

	vString = SplitString(S1, " ");

	vector <string>::iterator iter = vString.end();

	while (iter != vString.begin())
	{
		--iter;

		S2 += *iter + " ";

	}

	return S2.substr(0, S2.length() - 1);

}

string ReplaceWord(string S1, string StringToReplace, string ReplacedTo)
{
	short pos = S1.find(StringToReplace);


	while (pos != string::npos)
	{
		S1.replace(pos, StringToReplace.length(), ReplacedTo);
		pos = S1.find(StringToReplace);

	}
	return S1;
}

string MyReplaceUsingSplit(string S1, string StringToReplace, string ReplacedTo, bool MatchCase = true)
{

	vector <string> vString = SplitString(S1, "");

	for (string& s : vString)
	{

		if (MatchCase)
		{
			if (s == StringToReplace)
				s = ReplacedTo;

		}
		else
		{
			if (LowerAllString(StringToReplace) == LowerAllString(s))
				s = ReplacedTo;

		}


	}

	return JoinString(vString, " ");
}

string RemovePunctFromString(string S1)
{
	string Result = "";

	for (short i = 0;i < S1.length();i++)
	{

		if (!ispunct(S1[i]))
			Result += S1[i];

	}

	return Result;
}
}