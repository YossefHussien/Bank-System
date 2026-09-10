#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include "MyLibrary/Ystring.h"

using namespace std;

namespace YDateTime
{
    // _______________________________________________________________________________________
    // General
  
    struct sDate
    {
        short Year;
        short Month;
        short Day;
    };

    struct stPeriod
    {
        sDate StartDate;
        sDate EndDate;
    };

    bool isWeekEnd(sDate Date);

    sDate IncreaseDateByOneDay(sDate Date);

    bool IsDate1BeforeDate2(sDate Date1, sDate Date2);

    sDate GetSystemDate()
    {
        sDate Date;

        time_t t = time(0);
        tm now;

        localtime_s(&now, &t);

        Date.Year = now.tm_year + 1900;
        Date.Month = now.tm_mon + 1;
        Date.Day = now.tm_mday;

        return Date;
    }

    bool AreEqualDates(sDate Date1, sDate Date2)
    {
        return Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day;
    }
    
    void SwapDates(sDate &Date1, sDate &Date2)
    {
        sDate temp = Date1;
        Date1 = Date2;
        Date2 = temp;
    }

    sDate CalcVacationReturnDate(sDate DateFrom, int VacationDays)
    {
        short WeekEndCounter = 0;

        while (YDateTime::isWeekEnd(DateFrom))
        {
            DateFrom = YDateTime::IncreaseDateByOneDay(DateFrom);
        }

        for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
        {
            if (YDateTime::isWeekEnd(DateFrom))
                WeekEndCounter++;

            DateFrom = YDateTime::IncreaseDateByOneDay(DateFrom);
        }

        while (YDateTime::isWeekEnd(DateFrom))
        {
            DateFrom = YDateTime::IncreaseDateByOneDay(DateFrom);
        }

        return DateFrom;
    }

    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    enDateCompare CompareDates(sDate Date1, sDate Date2)
    {
        if (YDateTime::IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (YDateTime::AreEqualDates(Date1, Date2))
            return enDateCompare::Equal;

        return enDateCompare::After;
    }

    sDate StringtoDateStructure(string DateString)
    {
        vector <string> vDate = Ystring::SplitString(DateString, "/");
        sDate DateStruct;

        DateStruct.Day = stoi(vDate[0]);
        DateStruct.Month = stoi(vDate[1]);
        DateStruct.Year = stoi(vDate[2]);

        return DateStruct;
    }

    string DateToString(sDate Date)
    {
        return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
    }
    // _______________________________________________________________________________________
    // Years

    bool isLeapYear(int Year)
    {
        return (Year % 400 == 0) ||
            (Year % 4 == 0 && Year % 100 != 0);
    }

    short NumberOfDaysInAYear(int Year)
    {
        return isLeapYear(Year) ? 366 : 365;
    }

    short NumberOfHoursInAYear(int Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    int NumberOfMinutesInAYear(int Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear(int Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    sDate IncreaseDateByOneYear(sDate Date)
    {
        Date.Year++;
        return Date;
    }

    sDate IncreaseDateByXYears(sDate Date, short NumberOfYears)
    {
        Date.Year += NumberOfYears;
        return Date;
    }

    sDate IncreaseDateByOneDecade(sDate Date)
    {
        Date.Year += 10;
        return Date;
    }

    sDate IncreaseDateByXDecades(sDate Date, short NumberOfDecades)
    {
        Date.Year += (NumberOfDecades * 10);
        return Date;
    }

    sDate IncreaseDateByOneCentury(sDate Date)
    {
        Date.Year += 100;
        return Date;
    }

    sDate IncreaseDateByXCentury(sDate Date, short NumberOfCenturies)
    {
        Date.Year += (NumberOfCenturies * 100);
        return Date;
    }

    sDate IncreaseDateByOneMillennium(sDate Date)
    {
        Date.Year += 1000;
        return Date;
    }

    sDate DecreaseDateByOneYear(sDate Date)
    {
        Date.Year--;
        return Date;
    }

    sDate DecreaseDateByXYears(int NumberOfYears, sDate Date)
    {
        Date.Year -= NumberOfYears;
        return Date;
    }

    sDate DecreaseDateByOneDecade(sDate Date)
    {
        Date.Year -= 10;
        return Date;
    }

    sDate DecreaseDateByXDecades(int NumberOfDecades, sDate Date)
    {
        Date.Year -= (NumberOfDecades * 10);
        return Date;
    }

    sDate DecreaseDateByOneCentury(sDate Date)
    {
        Date.Year -= 100;
        return Date;
    }

    sDate DecreaseDateByOneMillennium(sDate Date)
    {
        Date.Year -= 1000;
        return Date;
    }

    // _______________________________________________________________________________________
    // Months

    short NumberOfDaysInAMonth(int Year, int Month)
    {
        if (Month < 1 || Month > 12)
            return 0;

        int NumberOfDays[13] =
        {
            0, 31, 28, 31, 30, 31,
            30, 31, 31, 30, 31, 30, 31
        };

        return (Month == 2)
            ? (isLeapYear(Year) ? 29 : 28)
            : NumberOfDays[Month];
    }

    short NumberOfHoursInAMonth(int Year, int Month)
    {
        return NumberOfDaysInAMonth(Year, Month) * 24;
    }

    int NumberOfMinutesInAMonth(int Year, int Month)
    {
        return NumberOfHoursInAMonth(Year, Month) * 60;
    }

    int NumberOfSecondsInAMonth(int Year, int Month)
    {
        return NumberOfMinutesInAMonth(Year, Month) * 60;
    }

    string MonthShortName(short MonthNumber)
    {
        string Months[12] =
        {
            "Jan", "Feb", "Mar", "Apr", "May", "Jun",
            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
        };

        return Months[MonthNumber - 1];
    }

    bool isLastDayInAMonth(sDate Date)
    {
        return Date.Day == YDateTime::NumberOfDaysInAMonth(Date.Year, Date.Month);
    }

    bool isLastMonthInAYear(short Month)
    {
        return Month == 12;
    }

    bool IsFirstMonthInAYear(short Month)
    {
        return Month == 1;
    }

    sDate IncreaseDateByOneMonth(sDate Date)
    {
        Date.Month++;
        if (Date.Month > 12)
        {
            Date.Month = 1;
            Date.Year++;
        }

        short NumberOfDaysInCurrentMonth = YDateTime::NumberOfDaysInAMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    sDate IncreaseDateByXMonths(sDate Date, short NumberOfMonths)
    {
        for (int i = 1; i <= NumberOfMonths;i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }

        return Date;
    }

    sDate DecreaseDateByOneMonth(sDate Date)
    {
        if (IsFirstMonthInAYear(Date.Month))
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    sDate DecreaseDateByXMonths(int NumberOfMonths, sDate Date)
    {
        for (int i = 1; i <= NumberOfMonths; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }

        return Date;
    }
    // _______________________________________________________________________________________
    // Days

    short DayOfWeekOrder(short Year, short Month, short Day)
    {
        short a, y, m;

        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;

        return (Day + y + (y / 4) - (y / 100) +
            (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder(sDate Date)
    {
        return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
    }

    bool IsEndOfWeek(sDate Date)
    {
        return DayOfWeekOrder(Date) == 6;
    }

    bool isWeekEnd(sDate Date)
    {
        // Weekends are Fri and Sat
        short DayIndex = DayOfWeekOrder(Date);

        return DayIndex == 5 || DayIndex == 6;
    }

    bool isBusniessDay(sDate Date)
    {
        return !isWeekEnd(Date);
    }

    int NumberOfDaysSinceBegginingOfTheYear(short Year,short Month,short Day)
    {
        int TotalDays = 0;

        for (int i = 1; i < Month; i++)
        {
            TotalDays += NumberOfDaysInAMonth(Year, i);
        }

        TotalDays += Day;

        return TotalDays;
    }

    string DayShortName(short DaysOfWeekOrder)
    {
        string DaysName[7] =
        {
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday"
        };

        return DaysName[DaysOfWeekOrder];
    }

    sDate IncreaseDateByOneDay(sDate Date)
    {

        if (isLastDayInAMonth(Date))
        {
            if (isLastMonthInAYear(Date.Month))
            {
                Date.Day = 1;
                Date.Month = 1;
                Date.Year++;
            }
            else
            {
                Date.Day = 1;
                Date.Month++;
            }


        }
        else
        {
            Date.Day++;
        }


        return Date;

    }

    bool IsFirstDayInAMonth(sDate Date)
    {
        return Date.Day == 1;
    }

    sDate DecreaseDateByOneDay(sDate Date)
    {
        if (IsFirstDayInAMonth(Date))
        {
            if (IsFirstMonthInAYear(Date.Month))
            {
                Date.Day = 31;
                Date.Month = 12;
                Date.Year--;
            }
            else
            {
                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
            }
        }
        else
        {
            Date.Day--;
        }

        return Date;
    }

    sDate DecreaseDateByXDays(int NumberOfDays, sDate Date)
    {
        for (int i = 1; i <= NumberOfDays; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    sDate DecreaseDateByOneWeek(sDate Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    sDate DecreaseDateByXWeeks(sDate Date, int NumberOfWeeks)
    {
        for (int i = 1; i <= NumberOfWeeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }

        return Date;
    }

    bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
    {
        return (Date1.Year < Date2.Year) ? true : ((Date1.Year ==
            Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month ==
                Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }

    bool IsDate1AfterDate2(sDate Date1, sDate Date2)
    {
        return !(YDateTime::IsDate1BeforeDate2(Date1, Date2) && !YDateTime::AreEqualDates(Date1, Date2));
    }

    int GetDifferenceInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short SwapFlag = 1;

        if (!YDateTime::IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlag = -1;
        }

        while (YDateTime::IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = YDateTime::IncreaseDateByOneDay(Date1);
        }


        return IncludeEndDay ? ++Days * SwapFlag : Days * SwapFlag;
    }

    bool IsOverLapPeriods(stPeriod Period1, stPeriod Period2)
    {
        return !(CompareDates(Period2.EndDate, Period1.StartDate) == enDateCompare::Before ||
            CompareDates(Period2.StartDate, Period1.EndDate) == enDateCompare::After);
    }

    int PeriodLengthInDays(stPeriod Period, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
    }

    bool IsDateWithinPeriod(stPeriod Period, sDate Date)
    {
        return !IsDate1BeforeDate2(Date, Period.StartDate) && !IsDate1AfterDate2(Date, Period.EndDate);
    }

    sDate IncreaseDateByXDays(sDate Date, int NumberOfDays)
    {
        for (int i = 1; i <= NumberOfDays;i++)
        {
            Date = YDateTime::IncreaseDateByOneDay(Date);
        }

        return Date;
    }

    sDate IncreaseDateByOneWeek(sDate Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = YDateTime::IncreaseDateByOneDay(Date);
        }
        return Date;
    }

    sDate IncreaseDateByXWeeks(sDate Date, short NumberOfWeeks)
    {
        for (int i = 1; i <= NumberOfWeeks;i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }

        return Date;
    }

    int CalcVacationsDays(sDate DateFrom, sDate DateTo)
    {
        int ActualVacationDays = 0;

        while (YDateTime::IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (YDateTime::isBusniessDay(DateFrom))
                ActualVacationDays++;


            DateFrom = YDateTime::IncreaseDateByOneDay(DateFrom);
        }
        return ActualVacationDays;
    }


    // _______________________________________________________________________________________
    // Calendar

    void PrintMonthCalendar(short Year, short Month)
    {
        int NumberOfDays = NumberOfDaysInAMonth(Year, Month);
        int Current = DayOfWeekOrder(Year, Month, 1);

        printf(
            "\n _______________%s_______________\n\n",
            MonthShortName(Month).c_str()
        );

        printf("  Sun Mon Tue Wed Thu Fri Sat\n");

        int i;

        for (i = 0; i < Current; i++)
            printf("    ");

        for (int j = 1; j <= NumberOfDays; j++)
        {
            printf("%4d", j);

            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }

        printf("\n _________________________________\n");
    }

    void PrintYearCalender(short Year)
    {
        printf("\n_____________________________________\n");
        printf("\n            Calender - %d\n", Year);
        printf("\n_____________________________________\n");

        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(Year, i);
        }
    }


    // _______________________________________________________________________________________
    // Date Functions

    sDate DateAddDays(short Days, sDate Date)
    {
        short RemainingDays = Days + NumberOfDaysSinceBegginingOfTheYear(Date.Year,Date.Month, Date.Day);

        short MonthDays = 0;

        Date.Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Year, Date.Month);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Month++;

                if (Date.Month > 12)
                {
                    Date.Month = 1;
                    Date.Year++;
                }
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    sDate GetDateFromDayOrderInYear( short DateOrderInYear, short Year)
    {
        sDate Date;

        short RemainingDays = DateOrderInYear;

        Date.Year = Year;
        Date.Month = 1;

        short NumOfDaysInAMonth;

        while (true)
        {
            NumOfDaysInAMonth =
                NumberOfDaysInAMonth(Year, Date.Month);

            if (RemainingDays > NumOfDaysInAMonth)
            {
                RemainingDays -= NumOfDaysInAMonth;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    int CountOverLapDays(stPeriod Period1, stPeriod Period2)
    {
        if (!IsOverLapPeriods(Period1, Period2))
            return 0;


        sDate StartOverLap = CompareDates(Period1.StartDate, Period2.StartDate) == enDateCompare::After
            ? Period1.StartDate : Period2.StartDate;


        sDate EndOverLap = CompareDates(Period1.EndDate, Period2.EndDate) == enDateCompare::Before
            ? Period1.EndDate : Period2.EndDate;

        return YDateTime::GetDifferenceInDays(StartOverLap, EndOverLap);
    }

    bool isValidDate(sDate Date)
    {
        return !(Date.Day < 1 || Date.Month < 1 || Date.Month > 12 || Date.Day > YDateTime::NumberOfDaysInAMonth(Date.Year, Date.Month));
    }
}
