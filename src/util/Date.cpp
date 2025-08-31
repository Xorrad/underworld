#include "Date.hpp"

const Date Date::EPOCH = Date(0, 1, 1, 0);

Date::Date() : Date(0, 0, 0, 0) {}

Date::Date(int year, int month, int day, int hour) :
    year(year),
    month(month),
    day(day),
    hour(hour)
{
    if (month < 1 || month > 12)
        throw std::invalid_argument("Invalid month");
    if (day < 1 || day > Date::DaysInMonth(year, month))
        throw std::invalid_argument("Invalid day for given month/year");
    if (hour < 0 || hour > 23)
        throw std::invalid_argument("Invalid hour");
}

bool Date::IsLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::DaysInMonth(int y, int m) {
    static const int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m < 1 || m > 12)
        throw std::invalid_argument("Invalid month");
    if (m == 2 && Date::IsLeapYear(y))
        return 29;
    return days[m - 1];
}

Date Date::Epoch() {
    return Date::EPOCH;
}

Date Date::FromHours(long hours) {
    long days = hours / 24;
    
    int h = static_cast<int>(hours % 24);
    if (h < 0) {
        h += 24;
        days--; 
    }

    int y = Date::EPOCH.year;
    if (days >= 0) {
        while (true) {
            int yearDays = Date::IsLeapYear(y) ? 366 : 365;
            if (days >= yearDays) {
                days -= yearDays;
                y++;
            }
            else break;
        }
    }
    else {
        while (days < 0) {
            y--;
            int yearDays = Date::IsLeapYear(y) ? 366 : 365;
            days += yearDays;
        }
    }

    int m = 1;
    while (true) {
        int mdays = Date::DaysInMonth(y, m);
        if (days >= mdays) {
            days -= mdays;
            m++;
        }
        else break;
    }

    int d = static_cast<int>(days) + 1;
    return Date(y, m, d, h);
}

Date Date::FromString(const std::string& str) {
    // Expected format: YYYY-M-D H
    // Example: "2024-3-5 9" or "1-1-1 0"

    auto Split = [](const std::string& str, char delimiter) {
        std::vector<std::string> parts;
        std::string token;
        std::istringstream iss(str);
        while (std::getline(iss, token, delimiter)) {
            parts.push_back(token);
        }
        return parts;
    };

    // Split into "date" and "hour".
    auto parts = Split(str, ' ');
    if (parts.size() != 2) {
        throw std::invalid_argument("Invalid format, expected 'YYYY-M-D H': " + str);
    }

    // Split "date" into year, month, day.
    auto ymd = Split(parts[0], '-');
    if (ymd.size() != 3) {
        throw std::invalid_argument("Invalid date part, expected 'YYYY-M-D': " + parts[0]);
    }

    try {
        int y = std::stoi(ymd[0]);
        int m = std::stoi(ymd[1]);
        int d = std::stoi(ymd[2]);
        int h = std::stoi(parts[1]);

        return Date(y, m, d, h);
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid numeric values in date string: " + str);
    }
}

long Date::DaysSinceEpoch() const {
    long long days = 0;
    if (year >= Date::EPOCH.year) {
        for (int y = Date::EPOCH.year; y < year; ++y)
            days += Date::IsLeapYear(y) ? 366 : 365;
    }
    else {
        for (int y = year; y < Date::EPOCH.year; ++y)
            days -= Date::IsLeapYear(y) ? 366 : 365;
    }

    for (int m = 1; m < month; ++m)
        days += Date::DaysInMonth(year, m);

    days += (day - 1);
    return days;
}

long Date::ToHours() const {
    return DaysSinceEpoch() * 24 + hour;
}

// ---- Comparison ----
bool Date::operator==(const Date& other) const {
    return year == other.year &&
           month == other.month &&
           day == other.day &&
           hour == other.hour;
}
bool Date::operator!=(const Date& other) const {
    return !(*this == other); 
}

bool Date::operator<(const Date& other) const {
    return ToHours() < other.ToHours(); 
}

bool Date::operator<=(const Date& other) const {
    return ToHours() <= other.ToHours();
}

bool Date::operator>(const Date& other) const {
    return ToHours() > other.ToHours();
}

bool Date::operator>=(const Date& other) const {
    return ToHours() >= other.ToHours();
}

// ---- Arithmetic ----
Date Date::operator+(int hours) const {
    return Date::FromHours(ToHours() + hours);
}

Date Date::operator-(int hours) const {
    return Date::FromHours(ToHours() - hours);
}

long Date::operator-(const Date& other) const {
    return ToHours() - other.ToHours();
}