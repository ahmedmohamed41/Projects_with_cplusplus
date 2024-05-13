#pragma warning(disable : 4996)

#include <iostream>
#include<string>
#include <iomanip>
#include <ctime> 

using namespace std;
enum sCompare {
    before = -1, equal = 0, after = 1
};
struct sDate {
    short numberOfDays, year, month, day;
};

short ReadNumberOfYears() {
    short year;
    cout << "Please Enter a year? ";
    cin >> year;
    return year;
}
short ReadNumberOfMonths() {
    short Month;
    cout << "Please Enter a Month? ";
    cin >> Month;
    return Month;
}
short ReadNumberOfDays() {
    short Day;
    cout << "Please Enter a Day? ";
    cin >> Day;
    return Day;
}
short ReadAddingNumberOfDays() {
    short Day;
    cout << "How many days to add? ";
    cin >> Day;
    return Day;
}
sDate ReadFullDate() { 
    sDate Date;
    Date.day = ReadNumberOfDays();
    cout << "\n";
    Date.month = ReadNumberOfMonths();
    cout << "\n";
    Date.year = ReadNumberOfYears();
    
    return Date;
}
sDate ReadFullDateNow() { 
    sDate Date;

    time_t t = time(0);

    tm* now = localtime(&t);
    
    Date.year = now->tm_year + 1900;
    Date.month = now->tm_mon + 1;
    Date.day = now->tm_mday;

    return Date;
}
bool CheckLeapYear(short Year) {

    return ((Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0));
   
}
bool CheckExistMonth(short Month) {

    return (Month <= 12 && Month >= 1) ? true : false;
   
}

short NumberOfDaysInMonth(short Month, short Year) {
    short numberOfDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    return (CheckLeapYear(Year) && Month == 2) ? 29 : numberOfDays[Month - 1];

}

bool LastDayInMonth(sDate Date) {

    return (Date.day == NumberOfDaysInMonth(Date.month, Date.year)) ? true : false;
}

bool LastMonthInYear(sDate Date) {

    return (Date.month == 12) ? true : false;
}
sDate IncreaseDateAfterAddingOneDay(sDate Date) {

    if (LastDayInMonth(Date) && LastMonthInYear(Date))
    {
        Date.day = 1;
        Date.month = 1;
        Date.year++;
    }
    else if (LastDayInMonth(Date))
    {
        Date.day = 1;
        Date.month++;
    }
    else
    {
        Date.day++;
    }
    return Date;
}
sDate DecreaseDateByOneDay(sDate Date) {

    if (Date.day == 1 && Date.month == 1)
    {
        Date.day = 31;
        Date.month = 12;
        Date.year--;
    }
    else if (Date.day == 1)
    {
        Date.month--;
        Date.day = NumberOfDaysInMonth(Date.month, Date.year);
    }
    else
    {
        Date.day--;
    }
    return Date;
}

short GetOrderOfDayInWeek(short day, short month, short year) {

    short a, y, m, d;

    a = (14 - month) / 12;

    y = year - a;

    m = month + (12 * a) - 2;

    // For the Gregorian calendar: 

    d = ((day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);

    return d;

}

string GetNameOfDay(short day) {

    string nameArr[] = { "Sun","Mon" ,"Tue","Wed","Thu","Fri","Sat" };

    return nameArr[day];
}

short GetNumberOfDaysBegining(short day, short month, short year)
{

    short numberOfDays = day;

    for (short i = month - 1; i >= 1; i--) {

        numberOfDays += NumberOfDaysInMonth(i, year);
    }

    return numberOfDays;
}
bool IsDate1LessThanDate2(sDate Date1, sDate Date2) {


    return (Date1.year < Date2.year) ? true : (Date1.month < Date2.month) ? true : (Date1.day < Date2.day) ? true : false;

}
bool IsDate1EqualToDate2(sDate Date1, sDate Date2) {


    return (Date1.year == Date2.year) ? (Date1.month == Date2.month) ? (Date1.day == Date2.day) : false : false;

}
sCompare CompareTwoDate(sDate Date1, sDate Date2) {
   

    if (IsDate1LessThanDate2(Date1, Date2))
    {
        return sCompare::before;
    }else if (IsDate1EqualToDate2(Date1,Date2))
    {
        return sCompare::equal;
    }
    else
    {
        return sCompare::after;
    }
}
bool GetPeriodsOverlapTwoPeriods(sDate Date1, sDate Date2, sDate Date3, sDate Date4) {

    return ((IsDate1LessThanDate2(Date3, Date1) && (IsDate1LessThanDate2(Date4, Date1))) || ((IsDate1LessThanDate2(Date1, Date3) && (IsDate1LessThanDate2(Date2, Date3))))) ? true: false;
}
short GetPeriodLength(sDate Date1, sDate Date2, bool IncludingEndDate = true) {
    short periodDate = 0;
    while (IsDate1LessThanDate2(Date1,Date2))
    {
        Date1 = IncreaseDateAfterAddingOneDay(Date1);
        periodDate++;
    }

    return IncludingEndDate ? periodDate : ++periodDate;
}
bool CheckDateWithinPeriods(sDate Date1, sDate Date2, sDate Date3) {

    short period = GetPeriodLength(Date1, Date2, true);

    for (short i = 0; i < period; i++)
    {
        if (IsDate1EqualToDate2(Date1, Date3))
        {
            return true;
            break;
        }
        Date1 = IncreaseDateAfterAddingOneDay(Date1);
    }
    return false;

}
short GetOverlapDaysCounts(sDate Date1, sDate Date2, sDate Date3, sDate Date4) {

    if (IsDate1LessThanDate2(Date3,Date2) && IsDate1LessThanDate2(Date2, Date4))
    {
        return GetPeriodLength(Date3, Date2);
    }
    else
    {
        return 0;
    }
   
}
bool CheckValidatedDate(sDate Date) {

    return CheckLeapYear(Date.year) ? (CheckExistMonth(Date.month) ? (Date.day<=NumberOfDaysInMonth(Date.month, Date.year)?true:false) : false) : (CheckExistMonth(Date.month) ? (Date.day <= NumberOfDaysInMonth(Date.month, Date.year) ? true : false) : false);
}
int main()
{

 
   cout << "Enter Date: " << endl;
   cout << "\n";
   sDate Date1 = ReadFullDate();
   cout << "\n";
   

   if (CheckValidatedDate(Date1))
   {
       cout << "Yes ,Date is a Valide date." << endl;
   }
   else
   {
       cout << "NO ,Date is NOT a Valide date." << endl;

   }
   

     system("pause>0");

    return 0;

}