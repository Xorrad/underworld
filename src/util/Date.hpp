#pragma once

class Date {
public:
    Date();
    Date(int year, int month, int day, int hour);

    // Helper functions
    static bool IsLeapYear(int y);
    static int DaysInMonth(int y, int m);
    static Date Epoch();

    // Conversion
    static Date FromHours(long hours);
    static Date FromString(const std::string& str);
    static std::string DurationFormat(long hours);
    long DaysSinceEpoch() const;
    long ToHours() const;
    std::string ToString() const;
    std::string ToStringFormatted() const;
    std::string ToStringFormatted12H() const;

    // Comparison operators
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;

    // Arithmetic operators (difference in hours, add hours)
    Date operator+(int hours) const;
    Date operator-(int hours) const;
    long operator-(const Date& other) const; // returns difference in hours

public:
    int year;
    int month;
    int day;
    int hour;

public:
    static const std::vector<std::string_view> MONTHS;
    static const Date EPOCH;
};