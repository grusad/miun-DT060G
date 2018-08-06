/*
* Filename:		Time.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Time.h"
#include <ostream>
#include <istream>

Time::Time(int days, int hour, int minute)
{
	this->days = days;
	this->hour = hour;
	this->minute = minute;
	
}

Time::Time(const Time &time)
{
	hour = time.GetHour();
	minute = time.GetMinute();
	days = time.GetDays();
}

// adds to time object together
Time Time::operator+(const Time &time) const
{
	Time sum;

	int minutes = ToMinutes() + time.ToMinutes();

	sum.FromMinutes(minutes);

	return sum;
}

// subtracts to time object
Time Time::operator-(const Time &time) const
{
	Time sum;

	int minutes = ToMinutes() - time.ToMinutes();

	if (minutes < 0)
	{
		int temp = 1440;
		minutes = abs(minutes);
		minutes %= temp;
		temp -= minutes;
		minutes = temp;
	}

	sum.FromMinutes(minutes);

	return sum;
}

// subtracts minutes from time object
Time& Time::operator-=(int minutes) 
{
	while (minutes)
	{
		this->minute--;
		if (this->minute < 0)
		{
			this->hour--;
			if (this->hour < 0)
			{
				this->hour = 23;
				days--;
			}

			this->minute = 59;
		}
		minutes--;
	}
	return *this;
}

// adds minutes to time object
Time & Time::operator+=(int minutes)
{
	while (minutes)
	{
		this->minute++;
		if (this->minute >= 60)
		{
			this->hour++;
			if (this->hour >= 24)
			{
				this->hour = 0;
				days++;
			}
			this->minute = 0;
		}
		minutes--;
	}
	return *this;
}

bool Time::operator<(const Time &time) const
{
	return ToMinutes() < time.ToMinutes();
}


bool Time::operator>(const Time &time) const
{
	return ToMinutes() > time.ToMinutes();
}


bool Time::operator==(const Time &time) const
{
	return hour == time.hour && minute == time.minute && days == time.days;
}

bool Time::operator<=(const Time & time) const
{
	return *this < time || *this == time;
}

bool Time::operator>=(const Time & time) const
{
	return *this > time || *this == time;
}

// returns minutes from time object
int Time::ToMinutes() const
{
	return (days * 24 * 60) + (hour * 60) + minute;
}

// returns a time object by minutes.
Time Time::FromMinutes(const int min) const
{
	int minutes = min;

	Time time;

	int hours = minutes / 60;
	minutes %= 60;
	int days = hours / 24;
	hours %= 24;

	time.SetDays(days);
	time.SetHour(hours);
	time.SetMinute(minutes);


	return time;
}

// returns time in correct format of string
std::string Time::ToString()
{
	std::string str;

	if (hour < 10) str += "0";
	str += std::to_string(hour);
	str += ":";
	if (minute < 10) str += "0";
	str += std::to_string(minute);
	return str;

}

// reads to ostream
std::ostream &operator<<(std::ostream &stream, const Time &time)
{
	if (time.GetHour() < 10) stream << "0";
	stream << time.GetHour();
	stream << ":";
	if (time.GetMinute() < 10) stream << "0";
	stream << time.GetMinute();
	
	return stream;
}


// reads from istream
std::istream &operator>>(std::istream &stream, Time &time)
{
	int hour;
	int minute;

	stream >> hour;
	stream.get();
	stream >> minute;

	time.SetHour(hour);
	time.SetMinute(minute);
	
	return stream;
}
