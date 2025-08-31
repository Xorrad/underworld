#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.hpp"

// Desc: Tests related to the date structure and its operations.

TEST_CASE("[date] Basic construction") {
    SUBCASE("Constructor") {
        Date d1(2000, 2, 29, 12);
        CHECK(d1.year == 2000);
        CHECK(d1.month == 2);
        CHECK(d1.day == 29);
        CHECK(d1.hour == 12);
    }

    SUBCASE("Months requirements") {
        CHECK_THROWS(Date(2000, 13, 1, 1));
        CHECK_THROWS(Date(2000, 0, 1, 1));
    }
    
    SUBCASE("Days requirements") {
        static const int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        for (int m = 0; m < 12; m++) {
            CHECK_THROWS(Date(2001, m+1, 0, 1));
            CHECK_NOTHROW(Date(2001, m+1, 1, 1));
            CHECK_NOTHROW(Date(2001, m+1, days[m], 1));
            CHECK_THROWS(Date(2001, m+1, days[m]+1, 1));
        }
    }

    SUBCASE("Leap years") {
        CHECK_NOTHROW(Date(2000, 2, 28, 1));
        CHECK_NOTHROW(Date(2000, 2, 29, 1));
        CHECK_THROWS(Date(2001, 2, 29, 1));
    }

    SUBCASE("Hours requirements") {
        CHECK_THROWS(Date(2000, 1, 1, -1));
        CHECK_NOTHROW(Date(2000, 1, 1, 1));
        CHECK_NOTHROW(Date(2000, 1, 1, 23));
        CHECK_THROWS(Date(2000, 1, 1, 24));
    }
}

TEST_CASE("[date] Helper functions") {
    SUBCASE("Leap years") {
        CHECK(Date::IsLeapYear(2000));
        CHECK_FALSE(Date::IsLeapYear(2001));
        CHECK_FALSE(Date::IsLeapYear(2002));
        CHECK_FALSE(Date::IsLeapYear(2003));
        CHECK(Date::IsLeapYear(2004));
    }
    
    SUBCASE("Days in month") {
        static const int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        for (int m = 0; m < 12; m++) {
            CHECK(Date::DaysInMonth(2001, m+1) == days[m]);
        }
        CHECK(Date::DaysInMonth(2000, 2) == 29);
    }
}

TEST_CASE("[date] Epoch behavior") {
    Date epoch = Date::Epoch();
    CHECK(epoch.year == 0);
    CHECK(epoch.month == 1);
    CHECK(epoch.day == 1);
    CHECK(epoch.hour == 0);

    Date d1(0, 1, 2, 0);
    CHECK((d1 - epoch) == 24);
}

TEST_CASE("[date] Conversion to and from hours") {
    Date epoch = Date::Epoch();  // 0000-01-01 00h

    SUBCASE("Epoch is zero hours") {
        CHECK(epoch - epoch == 0);
        CHECK((epoch - Date::FromHours(0)) == 0);
    }

    SUBCASE("One day after epoch is 24 hours") {
        Date d1(0, 1, 2, 0);
        CHECK((d1 - epoch) == 24);
    }

    SUBCASE("Round-trip consistency") {
        Date d1(2024, 2, 29, 12);  // leap day
        Date d2 = Date::FromHours(d1 - epoch); // hack to reach fromHours
        CHECK(d2 == d1);
    }

    SUBCASE("Negative dates (before epoch)") {
        Date d1(-1, 12, 31, 0);
        long hours = d1 - epoch;
        CHECK(hours == -24);

        Date d2 = Date::FromHours(hours);
        CHECK(d2 == d1);
    }

    SUBCASE("Adding hours via toHours consistency") {
        Date d1(0, 1, 1, 0);
        Date d2(0, 1, 1, 10);
        CHECK((d2 - d1) == 10);

        Date d3 = Date::FromHours(d1 - epoch + 10);
        CHECK(d3 == d2);
    }
}

TEST_CASE("[date] Comparison operators") {
    Date d1(2000, 5, 10, 10);
    Date d2(2000, 5, 10, 12);
    Date d3(2000, 5, 11, 10);

    CHECK(d1 < d2);
    CHECK(d2 < d3);
    CHECK(d3 > d1);
    CHECK(d1 != d2);
    CHECK(d2 == Date(2000, 5, 10, 12));
}

TEST_CASE("[date] Arithmetic with hours") {
    Date d1(2000, 12, 31, 23);
    Date d2 = d1 + 2;
    Date d3 = d2 - 25;

    // Wrap to next year.
    SUBCASE("Wrapping to next year") {
        CHECK(d2.year == 2001);
        CHECK(d2.month == 1);
        CHECK(d2.day == 1);
        CHECK(d2.hour == 1);
    }

    SUBCASE("Going backwards") {
        CHECK(d3.year == 2000);
        CHECK(d3.month == 12);
        CHECK(d3.day == 31);
        CHECK(d3.hour == 0);
    }
}

TEST_CASE("[date] Difference between dates") {
    Date d1(2000, 5, 10, 10);
    Date d2(2000, 5, 11, 10);

    CHECK((d2 - d1) == 24);
    CHECK((d1 - d2) == -24);
}