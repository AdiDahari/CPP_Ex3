#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <array>
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
    NumberWithUnits n1(1.001, "kg");
    CHECK((kg + g) == n1);
    CHECK((g + kg) == n1);
    CHECK((kg + g) >= n1);
    CHECK((g + kg) >= n1);
    CHECK((kg + g) <= n1);
    CHECK((g + kg) <= n1);
    NumberWithUnits n2(1.001001, "ton");
    CHECK((ton + n1) == n2);
    CHECK((n1 + ton) == n2);
    CHECK((ton + n1) >= n2);
    CHECK((n1 + ton) >= n2);
    CHECK((ton + n1) <= n2);
    CHECK((n1 + ton) <= n2);
    CHECK(n2 > n1);
    CHECK(n1 < n2);
    CHECK(n2 >= n1);
    CHECK(n1 <= n2);
    CHECK((1001001 * g) == n2);
    CHECK((1001001 * g) <= n2);
    CHECK((1001001 * g) >= n2);
}
TEST_CASE("Boolean operations - Currency")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits shekel(1, "ILS");
    NumberWithUnits dollar(1, "USD");
    CHECK(shekel < dollar);
    CHECK(shekel <= dollar);
    CHECK(shekel != dollar);
    CHECK(dollar > shekel);
    CHECK(dollar >= shekel);
    CHECK(dollar != shekel);
    CHECK((shekel + dollar) == (4.33 * shekel));
}
TEST_CASE("Exceptions expected")
{
    ifstream bad_units_file{"UNITS_WRONG.txt"};
    CHECK_THROWS(NumberWithUnits::read_units(bad_units_file));
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits cm(1, "cm");
    NumberWithUnits m(1, "m");
    NumberWithUnits km(1, "km");
    array<NumberWithUnits, 3> lengths = {cm, m, km};
    NumberWithUnits g(1, "g");
    NumberWithUnits kg(1, "kg");
    NumberWithUnits ton(1, "ton");
    array<NumberWithUnits, 3> weights = {g, kg, ton};
    NumberWithUnits shekel(1, "ILS");
    NumberWithUnits dollar(1, "USD");
    CHECK_THROWS(NumberWithUnits euro(1, "EUR"));
    CHECK_THROWS(NumberWithUnits cm_wrong(1, "Cm"));
    CHECK_THROWS(NumberWithUnits g_wrong(1, "G"));
    CHECK_THROWS(NumberWithUnits shekel_wrong(1, "ils"));
    CHECK_THROWS(NumberWithUnits euro(1, "EUR"));

    array<NumberWithUnits, 2> currencies = {shekel, dollar};
    for (NumberWithUnits &l : lengths)
    {
        for (NumberWithUnits &w : weights)
        {
            for (NumberWithUnits &c : currencies)
            {
                /*Boolean operators*/
                CHECK_THROWS(cout << (l < w));
                CHECK_THROWS(cout << (l < c));
                CHECK_THROWS(cout << (w < c));
                CHECK_THROWS(cout << (l > w));
                CHECK_THROWS(cout << (l > c));
                CHECK_THROWS(cout << (w > c));
                CHECK_THROWS(cout << (l <= w));
                CHECK_THROWS(cout << (l <= c));
                CHECK_THROWS(cout << (w <= c));
                CHECK_THROWS(cout << (l >= w));
                CHECK_THROWS(cout << (l >= c));
                CHECK_THROWS(cout << (w >= c));
                CHECK_THROWS(cout << (l == w));
                CHECK_THROWS(cout << (l == c));
                CHECK_THROWS(cout << (w == c));
                CHECK_THROWS(cout << (l != w));
                CHECK_THROWS(cout << (l != c));
                CHECK_THROWS(cout << (w != c));

                /*Calculation operators*/
                CHECK_THROWS(cout << (l + w));
                CHECK_THROWS(cout << (l + c));
                CHECK_THROWS(cout << (w + c));
                CHECK_THROWS(cout << (l - w));
                CHECK_THROWS(cout << (l - c));
                CHECK_THROWS(cout << (w - c));
                CHECK_THROWS(cout << (l += w));
                CHECK_THROWS(cout << (l += c));
                CHECK_THROWS(cout << (w += c));
                CHECK_THROWS(cout << (l -= w));
                CHECK_THROWS(cout << (l -= c));
                CHECK_THROWS(cout << (w -= c));
            }
        }
    }
}