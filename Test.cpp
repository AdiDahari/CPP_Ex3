#include "doctest.h"
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;
TEST_CASE("Boolean operations - Length")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits km(1, "km");
    NumberWithUnits m(1, "m");
    NumberWithUnits cm(1, "cm");
    NumberWithUnits n1(999, "m");
    NumberWithUnits n2(1, "km");
    CHECK(m <= km);
    CHECK(m < km);
    CHECK(m >= cm);
    CHECK(m > cm);
    CHECK(km > cm);
    CHECK(cm < km);
    CHECK(((m <= m) && (m >= m)));
    CHECK_NOTHROW(n1 += m);
    CHECK(n1 == km);
    CHECK_NOTHROW(n1 -= m);
    CHECK_NOTHROW(n2 -= n1);
    CHECK(n2 == m);
    CHECK(n2 != n1);
    CHECK_NOTHROW(n2 -= m);
    CHECK(n2 != m);
    CHECK(m * (1.0 / 100) == cm);
    CHECK(km * (1.0 / 100000) == cm);
}
TEST_CASE("Boolean operations - Weight")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits g(1, "g");
    NumberWithUnits kg(1, "kg");
    NumberWithUnits ton(1, "ton");
    CHECK(g < kg);
    CHECK(kg > g);
    CHECK(g <= kg);
    CHECK(kg >= g);
    CHECK(kg < ton);
    CHECK(kg <= ton);
    CHECK(g < ton);
    CHECK(ton > g);
    CHECK((1000 * kg) == ton);
    CHECK((1000 * 1000 * g) == ton);
    CHECK((1000 * kg) >= ton);
    CHECK((1000 * 1000 * g) >= ton);
    CHECK((1000 * kg) <= ton);
    CHECK((1000 * 1000 * g) <= ton);
}