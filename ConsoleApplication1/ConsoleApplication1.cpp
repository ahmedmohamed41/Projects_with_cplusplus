#pragma warning(disable : 4996)

#include <iostream>
#include<string>
#include <iomanip>
#include <ctime> 

using namespace std;

struct sDate {
    short numberOfDays, year, month ,day ;
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
bool IsDayEndOfWeek(short orderDay) {
    cout << "   Is it End of Week?" << endl;
    return orderDay == 6 ? 1 : 0;
}
bool IsDayWeekEnd(short orderDay) {
    /*cout << "   Is it WeekEnd?" << endl;*/
    return (orderDay == 6 || orderDay == 5) ? 1 : 0;
}
bool IsDayBusiness(short orderDay) {
    cout << "   Is it Business Day?" << endl;
    return (orderDay == 6 || orderDay == 5) ? 0 : 1;
}
short IsDayUntilEndOfWeek(short orderDay) {
    
    return (orderDay == 6) ? 0 : (orderDay == 5) ? 1 : (6 - orderDay);
}
short IsDayUntilEndOfMonth(sDate Date) {
    
    return (NumberOfDaysInMonth(Date.month, Date.year) - Date.day) + 1;
}
short IsDayUntilEndOfYear(sDate Date) {

    return CheckLeapYear(Date.year) ? (366 - GetNumberOfDaysBegining(Date.day, Date.month, Date.year) + 1) : (365 - GetNumberOfDaysBegining(Date.day, Date.month, Date.year) + 1);
}

short ActucalVacationDays(sDate Date1, sDate Date2) {
    short vacation = 0;

    while (IsDate1LessThanDate2(Date1,Date2))
    {
        
        if (IsDayWeekEnd(GetOrderOfDayInWeek(Date1.day,Date1.month,Date2.year)))
        {
            Date1 = IncreaseDateAfterAddingOneDay(Date1);
        }
        else
        {
            Date1 = IncreaseDateAfterAddingOneDay(Date1);
            vacation++;
        }
    }

    return vacation;
}

sDate ReturnDateFromVacationDays(sDate Date1, short VacationDays) {

   


    for (short i = 0; i < VacationDays; i++)
    {
        if (IsDayWeekEnd(GetOrderOfDayInWeek(Date1.day, Date1.month, Date1.year)))
        {
            Date1 = IncreaseDateAfterAddingOneDay(Date1);

            Date1 = IncreaseDateAfterAddingOneDay(Date1);

            Date1 = IncreaseDateAfterAddingOneDay(Date1);

        }
        else
        {
            Date1 = IncreaseDateAfterAddingOneDay(Date1);
            
        }
    }
   
    Date1 = DecreaseDateByOneDay(Date1);

    return Date1;
}







int main()
{
   cout << "Vaction Starts: " << endl;
   sDate Date1 = ReadFullDate();
   short VacationDays = 0;
   cout << "\n\n";
   cout << "Please enter vacation days? ";
   cin >> VacationDays;
   Date1 = ReturnDateFromVacationDays(Date1, VacationDays);
   cout << "\n\n";
   cout << "Return Date is: " << GetNameOfDay(GetOrderOfDayInWeek(Date1.day, Date1.month, Date1.year)) << " , " << Date1.day << "/" << Date1.month << "/" << Date1.year << endl;


    system("pause>0");

    return 0;

}


