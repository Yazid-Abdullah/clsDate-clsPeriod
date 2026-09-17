#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
using namespace std;


class clsDate {

	int day;
	int month;
	int year;

	static vector<string> SplitString(string S, string Delim)
	{
		vector<string>vString;
		int pos = 0;
		string sword;

		while ((pos = S.find(Delim)) != std::string::npos)
		{
			sword = S.substr(0, pos);

			if (sword != "")
				vString.push_back(sword);

			S.erase(0, pos + Delim.length());
		}

		if (S != "")
			vString.push_back(S);



		return vString;
	}
	static clsDate StringToDate(string Line, string Seperator = "/")
	{
		vector <string> vDate;

		vDate = SplitString(Line, Seperator);

		return clsDate(stoi(vDate[0]), stoi(vDate[1]), stoi(vDate[2]));
	}
	static string DateToString(clsDate Date, string Seperator = "/")
	{
		string stDateRecord = "";

		stDateRecord += to_string(Date.day) + Seperator;
		stDateRecord += to_string(Date.month) + Seperator;
		stDateRecord += to_string(Date.year);

		return stDateRecord;
	}
	static int dayOrderInWeek(short day, short month, short year) {

		int a = (14 - month) / 12;
		int y = year - a;
		int m = month + (12 * a) - 2;

		// for Gregorian calendar
		int d = (day + y + (y / 4) - (y / 100) +
			(y / 400) + ((31 * m) / 12)) % 7;

		return d;
	}

public:

	// setters

	void setDay(int Day) {
		day = Day;
	}
	void setMonth(int Month) {
		month = Month;
	}
	void setYear(int Year) {
		year = Year;
	}


	// getters

	int getDay() {
		return day;
	}
	int getMonth() {
		return month;
	}
	int getYear() {
		return year;
	}


	// Constructors

	clsDate() {

		*this = GetSystemDate();
	}
	clsDate(string date) {

		*this = StringToDate(date, "/");

	}
	clsDate(int day, int month, int year) {

		this->day = day;
		this->month = month;
		this->year = year;
	}
	clsDate(int DayOrder, int year) {

		*this = DateFromDayOrderInYear(year, DayOrder);
	}


	// static

	static short ReadDay()
	{
		short Day;

		cout << "Enter Day: ";
		cin >> Day;

		return Day;
	}
	static short ReadMonth()
	{
		short Month;

		cout << "Please enter a month: ";
		cin >> Month;

		while (Month < 1 || Month > 12)
		{
			cout << "Invalid Month, Please enter a month between 1 and 12: ";
			cin >> Month;
		}

		return Month;
	}
	static short ReadYear()
	{
		short Year;

		cout << "Please enter a year: ";
		cin >> Year;

		return Year;
	}
	static clsDate ReadFullDate()
	{
		return clsDate(ReadDay(), ReadMonth(), ReadYear());
	}
	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		return clsDate(
			now->tm_mday,
			now->tm_mon + 1,
			now->tm_year + 1900
		);
	}
	static bool isCenturyYear(short year) {

		int ones, tens;

		ones = year % 10;
		year = year / 10;
		tens = year % 10;

		if (ones == 0 && tens == 0) {

			return true;
		}

		return false;
	}
	static bool isLeapYear(short year) {

		if (isCenturyYear(year)) {

			if (year % 400 == 0) {

				return true;

			}
			else {
				return false;
			}
		}
		else {

			if (year % 4 == 0) {

				return true;

			}
			else {
				return false;
			}
		}
	}
	static short numberOfDaysInYear(short year) {

		return isLeapYear(year) ? 366 : 365;
	}
	static int numberOfHoursInYear(short year) {

		return numberOfDaysInYear(year) * 24;
	}
	static int numberOfMinutesInYear(short year) {

		return numberOfHoursInYear(year) * 60;
	}
	static int numberOfSecondsInYear(short year) {

		return numberOfMinutesInYear(year) * 60;
	}
	static short numberOfDaysInMonth(short year, short month) {

		short DaysInMonth[12] =
		{
			31, 28, 31, 30, 31, 30,
			31, 31, 30, 31, 30, 31
		};

		return (isLeapYear(year) && (month == 2))
			? 29
			: DaysInMonth[month - 1];
	}
	static short numberOfHoursInMonth(short year, short month) {

		return numberOfDaysInMonth(year, month) * 24;
	}
	static int numberOfMinutesInMonth(short year, short month) {

		return numberOfHoursInMonth(year, month) * 60;
	}
	static int numberOfSecondsInMonth(short year, short month) {

		return numberOfMinutesInMonth(year, month) * 60;
	}
	static short daysFromTheBeginingOfYear(short day, short month, short year)
	{
		short TotalDays = 0;

		for (short i = 1; i < month; i++) {

			TotalDays += numberOfDaysInMonth(year, i);

		}

		TotalDays = TotalDays + day;

		return TotalDays;
	}
	static clsDate DateFromDayOrderInYear(short year, short dayOrder)
	{
		int remDays = dayOrder;

		clsDate Date(1, 1, year);

		Date.month = 1;

		for (short i = 0; i < 12; i++)
		{
			short DaysInMonth =
				numberOfDaysInMonth(year, Date.month);

			if (DaysInMonth < remDays)
			{
				remDays -= DaysInMonth;
				Date.month++;
			}
			else
			{
				break;
			}
		}

		Date.day = remDays;
		Date.year = year;

		return Date;
	}
	static void increaseDateByOneDay(clsDate& Date) {

		if (IsLastDayInMonth(
			Date.day,
			Date.month,
			Date.year))
		{
			Date.day = 1;

			if (Date.month == 12) {

				Date.month = 1;
				Date.year++;
			}
			else {

				Date.month++;
			}
		}
		else {

			Date.day++;
		}
	}
	static void IncreaseDateByXDays(clsDate& Date, short Days)
	{
		for (short i = 1; i <= Days; i++)
		{
			increaseDateByOneDay(Date);
		}
	}
	static void IncreaseDateByOneWeek(clsDate& Date)
	{
		IncreaseDateByXDays(Date, 7);
	}
	static void IncreaseDateByXWeeks(clsDate& Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			IncreaseDateByOneWeek(Date);
		}
	}
	static void IncreaseDateByOneMonth(clsDate& Date) {

		if ((Date.month + 1) == 13) {

			Date.year++;
			Date.month = 1;
		}
		else {

			Date.month++;
		}

		short days =
			numberOfDaysInMonth(Date.year, Date.month);

		if (days < Date.day) {

			Date.day = days;
		}
	}
	static void IncreaseDateByXMonths(clsDate& Date, short Months)
	{
		for (short i = 1; i <= Months; i++)
		{
			IncreaseDateByOneMonth(Date);
		}
	}
	static void IncreaseDateByOneYear(clsDate& Date)
	{
		IncreaseDateByXMonths(Date, 12);
	}
	static void IncreaseDateByXYears(clsDate& Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			IncreaseDateByOneYear(Date);
		}
	}
	static void IncreaseDateByOneDecade(clsDate& Date)
	{
		IncreaseDateByXYears(Date, 10);
	}
	static void IncreaseDateByXDecades(clsDate& Date, short Decades)
	{
		for (short i = 1; i <= Decades; i++)
		{
			IncreaseDateByOneDecade(Date);
		}
	}
	static void IncreaseDateByOneCentury(clsDate& Date)
	{
		IncreaseDateByXYears(Date, 100);
	}
	static void IncreaseDateByXCenturies(clsDate& Date, short Centuries)
	{
		for (short i = 1; i <= Centuries; i++)
		{
			IncreaseDateByOneCentury(Date);
		}
	}
	static void IncreaseDateByOneMillennium(clsDate& Date)
	{
		IncreaseDateByXYears(Date, 1000);
	}
	static void IncreaseDateByXMillennia(clsDate& Date, short Millennia)
	{
		for (short i = 1; i <= Millennia; i++)
		{
			IncreaseDateByOneMillennium(Date);
		}
	}
	static void DecreaseDateByOneDay(clsDate& Date) {

		if (Date.day == 1) {

			if (Date.month == 1) {

				Date.year--;
				Date.month = 12;
				Date.day =
					numberOfDaysInMonth(
						Date.year,
						Date.month);

			}
			else {

				Date.month--;
				Date.day =
					numberOfDaysInMonth(
						Date.year,
						Date.month);
			}
		}
		else {

			Date.day--;
		}
	}
	static void DecreaseDateByXDays(clsDate& Date, short Days)
	{
		for (short i = 1; i <= Days; i++)
		{
			DecreaseDateByOneDay(Date);
		}
	}
	static void DecreaseDateByOneWeek(clsDate& Date)
	{
		DecreaseDateByXDays(Date, 7);
	}
	static void DecreaseDateByXWeeks(clsDate& Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			DecreaseDateByOneWeek(Date);
		}
	}
	static void DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.month == 1)
		{
			Date.year--;
			Date.month = 12;
		}
		else
		{
			Date.month--;
		}

		short days =
			numberOfDaysInMonth(
				Date.year,
				Date.month);

		if (days < Date.day)
		{
			Date.day = days;
		}
	}
	static void DecreaseDateByXMonths(clsDate& Date, short Months)
	{
		for (short i = 1; i <= Months; i++)
		{
			DecreaseDateByOneMonth(Date);
		}
	}
	static void DecreaseDateByOneYear(clsDate& Date)
	{
		DecreaseDateByXMonths(Date, 12);
	}
	static void DecreaseDateByXYears(clsDate& Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			DecreaseDateByOneYear(Date);
		}
	}
	static void DecreaseDateByOneDecade(clsDate& Date)
	{
		DecreaseDateByXYears(Date, 10);
	}
	static void DecreaseDateByXDecades(clsDate& Date, short Decades)
	{
		for (short i = 1; i <= Decades; i++)
		{
			DecreaseDateByOneDecade(Date);
		}
	}
	static void DecreaseDateByOneCentury(clsDate& Date)
	{
		DecreaseDateByXYears(Date, 100);
	}
	static void DecreaseDateByXCenturies(clsDate& Date, short Centuries)
	{
		for (short i = 1; i <= Centuries; i++)
		{
			DecreaseDateByOneCentury(Date);
		}
	}
	static void DecreaseDateByOneMillennium(clsDate& Date)
	{
		DecreaseDateByXYears(Date, 1000);
	}
	static void DecreaseDateByXMillennia(clsDate& Date, short Millennia)
	{
		for (short i = 1; i <= Millennia; i++)
		{
			DecreaseDateByOneMillennium(Date);
		}
	}
	static string dayName(short dayorder) {

		switch (dayorder) {

		case 0: return "Sunday";
		case 1: return "Monday";
		case 2: return "Tuesday";
		case 3: return "Wednesday";
		case 4: return "Thursday";
		case 5: return "Friday";
		case 6: return "Saturday";

		}
	}
	static string shortDayName(short dayorder) {

		switch (dayorder) {

		case 0: return "Sun";
		case 1: return "Mon";
		case 2: return "Tue";
		case 3: return "Wed";
		case 4: return "Thu";
		case 5: return "Fri";
		case 6: return "Sat";

		}
	}
	static string monthName(short month) {

		string Months[12] =
		{
			"January", "February", "March",
			"April", "May", "June",
			"July", "August", "September",
			"October", "November", "December"
		};

		return Months[month - 1];
	}
	static string shortMonthName(short month) {

		string Months[12] =
		{
			"Jan", "Feb", "Mar", "Apr",
			"May", "Jun", "Jul", "Aug",
			"Sep", "Oct", "Nov", "Dec"
		};

		return Months[month - 1];
	}
	static void printMonthCalender(short year, short month)
	{
		int NumberOfDays =
			numberOfDaysInMonth(year, month);

		int current =
			dayOrderInWeek(1, month, year);


		printf(
			"\n  ---------------%s---------------\n\n",
			shortMonthName(month).c_str());

		printf(
			"  Sun  Mon  Tue  wed  Thu  Fri  Sat\n");


		int i;

		for (i = 0; i < current; i++) {

			printf("     ");
		}


		for (int j = 1; j <= NumberOfDays; j++) {

			printf("%5d", j);

			if (++i == 7) {

				i = 0;
				cout << endl;
			}
		}
	}
	static void printYearCalender(short year) {

		cout << "  ";

		printf(
			"-------------------------------------------------------\n\n");

		cout << "  ";

		printf(
			"                     Calender - %d                     \n\n",
			year);

		cout << "  ";

		printf(
			"-------------------------------------------------------\n");


		cout << endl << endl;


		for (short i = 1; i < 13; i++) {

			printMonthCalender(year, i);

			cout << endl << endl;
		}
	}
	static void addDaysToDate(clsDate& Date, int daystoAdd)
	{
		int remDays =
			daystoAdd +
			daysFromTheBeginingOfYear(
				Date.day,
				Date.month,
				Date.year);

		short MonthDays = 0;

		Date.month = 1;

		while (true) {

			MonthDays =
				numberOfDaysInMonth(
					Date.year,
					Date.month);

			if (MonthDays < remDays) {

				remDays -= MonthDays;

				if (Date.month < 12) {

					Date.month++;

				}
				else {

					Date.year++;
					Date.month = 1;
				}
			}
			else {

				Date.day = remDays;

				break;
			}
		}
	}
	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		if (Date1.year != Date2.year)
			return Date1.year < Date2.year;

		if (Date1.month != Date2.month)
			return Date1.month < Date2.month;

		return Date1.day < Date2.day;
	}
	static bool IsDate1EqualsDate2(clsDate Date1, clsDate Date2)
	{
		return (
			Date1.year == Date2.year &&
			Date1.month == Date2.month &&
			Date1.day == Date2.day);
	}
	static bool IsLastMonthInYear(short month) {

		return month == 12;
	}
	static bool IsLastDayInMonth(short day, short month, short year)
	{
		short daysInMonth =
			numberOfDaysInMonth(year, month);

		return daysInMonth == day;
	}
	static bool IsFirstDayInMonth(short day, short month, short year)
	{
		return day == 1;
	}
	static int diffBetweenTwoDates(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		if (IsDate1BeforeDate2(Date2, Date1))
		{
			cout <<
				"Date 1 should be less than or equal to Date 2 ... "
				<< endl;

			return 0;
		}


		int days = 0;

		while (IsDate1BeforeDate2(Date1, Date2)) {

			days++;

			increaseDateByOneDay(Date1);
		}


		return IncludeEndDay ? ++days : days;
	}
	static int diffBetweenTwoDatesNegative(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		if (IsDate1BeforeDate2(Date1, Date2)) {

			int days = 0;

			while (IsDate1BeforeDate2(Date1, Date2)) {

				days++;

				increaseDateByOneDay(Date1);
			}

			return IncludeEndDay ? ++days : days;
		}
		else {

			int days = 0;

			while (IsDate1BeforeDate2(Date2, Date1)) {

				days++;

				increaseDateByOneDay(Date2);
			}

			return IncludeEndDay
				? ((++days) * -1)
				: (days * -1);
		}
	}
	static int dayOrderInWeek(clsDate Date)
	{
		return dayOrderInWeek(
			Date.day,
			Date.month,
			Date.year);
	}
	static bool IsEndOfWeek(clsDate Date)
	{
		return dayOrderInWeek(Date) == 6;
	}
	static bool IsWeekEnd(clsDate Date)
	{
		int DayIndex = dayOrderInWeek(Date);

		return DayIndex == 5 || DayIndex == 6;
	}
	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}
	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - dayOrderInWeek(Date);
	}
	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		return numberOfDaysInMonth(
			Date.year,
			Date.month) - Date.day;
	}
	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		return numberOfDaysInYear(Date.year)
			- daysFromTheBeginingOfYear(
				Date.day,
				Date.month,
				Date.year);
	}
	static bool ValidateDate(clsDate Date) {

		if (Date.month > 12 || Date.month < 1) {
			return false;
		}

		int days =
			numberOfDaysInMonth(
				Date.year,
				Date.month);

		if (Date.day > days || Date.day < 1) {

			return false;
		}

		return true;
	}
	static string FormatDate(clsDate Date, string Format = "dd/mm/yyyy")
	{
		string FormattedDate = Format;

		FormattedDate.replace(
			FormattedDate.find("dd"),
			2,
			to_string(Date.day));

		FormattedDate.replace(
			FormattedDate.find("mm"),
			2,
			to_string(Date.month));

		FormattedDate.replace(
			FormattedDate.find("yyyy"),
			4,
			to_string(Date.year));

		return FormattedDate;
	}
	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !(
			IsDate1BeforeDate2(Date1, Date2) ||
			IsDate1EqualsDate2(Date1, Date2));
	}
	static short CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2)) {

			return -1;
		}
		else if (IsDate1EqualsDate2(Date1, Date2)) {

			return 0;
		}
		else {

			return 1;
		}
	}
	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate Temp = Date1;
		Date1 = Date2;
		Date2 = Temp;
	}

	// non-static

	void Print() {

		cout << day << " / "
			<< month << " / "
			<< year;
	}
	bool IsCenturyYear()
	{
		return isCenturyYear(year);
	}
	bool IsLeapYear()
	{
		return isLeapYear(year);
	}
	short NumberOfDaysInYear()
	{
		return numberOfDaysInYear(year);
	}
	int NumberOfHoursInYear()
	{
		return numberOfHoursInYear(year);
	}
	int NumberOfMinutesInYear() {
		return numberOfMinutesInYear(year);
	}
	int NumberOfSecondsInYear()
	{
		return numberOfSecondsInYear(year);
	}
	short NumberOfDaysInMonth()
	{
		return numberOfDaysInMonth(year, month);
	}
	short NumberOfHoursInMonth()
	{
		return numberOfHoursInMonth(year, month);
	}
	int NumberOfMinutesInMonth()
	{
		return numberOfMinutesInMonth(year, month);
	}
	int NumberOfSecondsInMonth()
	{
		return numberOfSecondsInMonth(year, month);
	}
	short DaysFromTheBeginingOfYear()
	{
		return daysFromTheBeginingOfYear(
			day,
			month,
			year);
	}
	void increaseDateByOneDay() {

		increaseDateByOneDay(*this);
	}
	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(*this, Days);
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}
	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(*this, Weeks);
	}
	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}
	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(*this, Months);
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}
	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(*this, Years);
	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}
	void IncreaseDateByXDecades(short Decades)
	{
		IncreaseDateByXDecades(*this, Decades);
	}
	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}
	void IncreaseDateByXCenturies(short Centuries)
	{
		IncreaseDateByXCenturies(*this, Centuries);
	}
	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}
	void IncreaseDateByXMillennia(short Millennia)
	{
		IncreaseDateByXMillennia(*this, Millennia);
	}
	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}
	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(*this, Days);
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}
	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(*this, Weeks);
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}
	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(*this, Months);
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}
	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(*this, Years);
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}
	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(*this, Decades);
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}
	void DecreaseDateByXCenturies(short Centuries)
	{
		DecreaseDateByXCenturies(*this, Centuries);
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}
	void DecreaseDateByXMillennia(short Millennia)
	{
		DecreaseDateByXMillennia(*this, Millennia);
	}
	string DayName()
	{
		return dayName(
			dayOrderInWeek(
				day,
				month,
				year));
	}
	string ShortDayName()
	{
		return shortDayName(
			dayOrderInWeek(
				day,
				month,
				year));
	}
	string MonthName()
	{
		return monthName(month);
	}
	string ShortMonthName()
	{
		return shortMonthName(month);
	}
	void PrintMonthCalender()
	{
		printMonthCalender(year, month);
	}
	void PrintYearCalender()
	{
		printYearCalender(year);
	}
	void AddDaysToDate(int DaysToAdd)
	{
		addDaysToDate(*this, DaysToAdd);
	}
	bool IsDateBefore(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}
	bool IsDateEquals(clsDate Date2)
	{
		return IsDate1EqualsDate2(*this, Date2);
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(month);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(
			day,
			month,
			year);
	}
	bool IsFirstDayInMonth()
	{
		return IsFirstDayInMonth(
			day,
			month,
			year);
	}
	int DiffBetweenTwoDates(clsDate Date2, bool IncludeEndDay = false)
	{
		return diffBetweenTwoDates(
			*this,
			Date2,
			IncludeEndDay);
	}
	int DiffBetweenTwoDatesNegative(clsDate Date2, bool IncludeEndDay = false)
	{
		return diffBetweenTwoDatesNegative(
			*this,
			Date2,
			IncludeEndDay);
	}
	int DayOrderInWeek()
	{
		return dayOrderInWeek(*this);
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}
	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}
	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}
	bool ValidateDate()
	{
		return ValidateDate(*this);
	}
	string FormatDate(string Format = "dd/mm/yyyy")
	{
		return FormatDate(*this, Format);
	}
	bool IsDateAfter(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}
	short CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}
	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);
	}

};

class clsPeriod {

	clsDate periodStart;
	clsDate periodEnd;


public:


	clsPeriod(clsDate start, clsDate end) {

		periodStart = start;
		periodEnd = end;

	}

	void setStart(clsDate start) {
		periodStart = start;
	}
	void setEnd(clsDate end) {
		periodEnd = end;
	}
	clsDate getStart() {
		return periodStart;
	}
	clsDate getEnd() {
		return periodEnd;
	}


	static bool IsOverlapPeriods(clsPeriod period1, clsPeriod period2) {

		if (clsDate::IsDate1AfterDate2(period2.periodStart, period1.periodEnd)) {
			return false;
		}

		if (clsDate::IsDate1BeforeDate2(period2.periodEnd, period1.periodStart)) {
			return false;
		}

		return true;



	};
	static int periodLength(clsPeriod period, bool IncludeEndDay = false) {

		return clsDate::diffBetweenTwoDates(period.periodStart, period.periodEnd, IncludeEndDay);

	}
	static bool IsDateWithinPeriod(clsPeriod period, clsDate DateToCheck) {

		if (!clsDate::IsDate1BeforeDate2(DateToCheck, period.periodStart) &&
			!clsDate::IsDate1AfterDate2(DateToCheck, period.periodEnd)) {
			return true;
		}
		return false;
	}
	static int CountOverlapDays(clsPeriod period1, clsPeriod period2) {

		if (!IsOverlapPeriods(period1, period2))
			return 0;


		clsDate OverlapStart = clsDate::IsDate1AfterDate2(period1.periodStart, period2.periodStart)
			? period1.periodStart : period2.periodStart;

		clsDate OverlapEnd = clsDate::IsDate1BeforeDate2(period1.periodEnd, period2.periodEnd)
			? period1.periodEnd : period2.periodEnd;

		clsPeriod c(OverlapStart, OverlapEnd);
		return periodLength(c, true);


	}
	static int calculateVacationDays(clsDate startDate, clsDate endDate) {

		int Vacationdays = 0;

		while (clsDate::IsDate1BeforeDate2(startDate, endDate)) {

			if (!clsDate::IsWeekEnd(startDate)) {
				Vacationdays++;
			}

			clsDate::increaseDateByOneDay(startDate);

		}
		return Vacationdays;
	}
	clsDate vacationReturnDate(clsDate startDate, int vacdays) {

		while (vacdays != 0) {

			if (!clsDate::IsWeekEnd(startDate)) {
				vacdays--;
			}


			clsDate::increaseDateByOneDay(startDate);

		}
		return startDate;

	}

	int periodfLength(bool IncludeEndDay = false) {

		return periodLength(*this, IncludeEndDay);
	};
	bool IsDateWithinPeriod(clsDate DateToCheck) {

		return IsDateWithinPeriod(*this, DateToCheck);
	}
	bool IsOverlapPeriods(clsPeriod period) {


		return IsOverlapPeriods(*this, period);

	};
	int CountOverlapDays(clsPeriod period) {

		return CountOverlapDays(*this, period);

	}


};



int main()
{
	 
}
