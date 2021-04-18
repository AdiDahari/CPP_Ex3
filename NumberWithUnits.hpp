#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
namespace ariel
{
    class NumberWithUnits
    {
    private:
        double val;
        string type;

    public:
        NumberWithUnits(double v, const string &t);
        ~NumberWithUnits(){};
        static void read_units(ifstream &units_file);
        double getVal() const { return val; };
        string getType() const { return type; };
        friend NumberWithUnits operator+(const NumberWithUnits &n1);
        friend NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator+=(NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator-(const NumberWithUnits &n1);
        friend NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator-=(NumberWithUnits &n1, const NumberWithUnits &n2);

        friend NumberWithUnits operator++(NumberWithUnits &n1);
        friend NumberWithUnits operator--(NumberWithUnits &n1);

        friend NumberWithUnits operator*(const NumberWithUnits &n1, double n2);
        friend NumberWithUnits operator*(double n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator*=(NumberWithUnits &n1, double n2);
        friend NumberWithUnits operator*=(double n1, NumberWithUnits &n2);

        friend bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2);

        friend ostream &operator<<(ostream &s, const NumberWithUnits &n);
        friend istream &operator>>(istream &s, NumberWithUnits &n);
    };
}