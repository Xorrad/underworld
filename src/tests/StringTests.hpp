#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.hpp"

// Desc: Tests related to the string utility functions.

TEST_CASE("[string] Idfy") {
    CHECK(String::Idfy("abcd") == "abcd");
    CHECK(String::Idfy("12345") == "12345");
    CHECK(String::Idfy("a1b2c3d4e5f") == "a1b2c3d4e5f");
    CHECK(String::Idfy("a1b2 c3d4e 5f") == "a1b2_c3d4e_5f");
    CHECK(String::Idfy("Aéro Del Sol'a") == "aero_del_sol_a");
}