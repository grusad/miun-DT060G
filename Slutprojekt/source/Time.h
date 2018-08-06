/*
* Filename:		Time.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef TIME_H
#define TIME_H

#include <string>

class Time
{
public:

	Time() : days(0), hour(0), minute(0) {}
	Time(int days, int hour, int minute);
	Time(const Time &time);

	int GetHour() const { return hour; };
	int GetMinute() const { return minute; };
	int GetDays() const { return days; };

	void SetDays(int days) { this->days = days; };
	void SetHour(int hour) { this->hour = hour; };
	void SetMinute(int minute) { this->minute = minute; };

	int ToMinutes() const;
	Time FromMinutes(const int min) const;

	std::string ToString();
	Time operator+(const Time &time) const;
	Time operator-(const Time &time) const;
	Time& operator-=(int minutes);
	Time& operator+=(int minutes);
	bool operator<(const Time &time) const;
	bool operator>(const Time &time) const;
	bool operator==(const Time &time) const;
	bool operator<=(const Time &time) const;
	bool operator>=(const Time &time) const;

private:
	int hour;
	int minute;
	int days;

};

std::ostream &operator<<(std::ostream &stream, const Time &time);
std::istream &operator>>(std::istream &stream, Time &time);

#endif // !TIME_H
