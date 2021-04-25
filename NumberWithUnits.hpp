#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;
namespace ariel
{
    /*This class represent a unit with a value.*/
    /*Each unit made of this class holds 2 members: _val, _type. It's value is double and it's type is string*/

    class NumberWithUnits
    {
    private:
        double _val;
        string _type;

    public:
        /* Constructor & Destructor */
        NumberWithUnits(double v, const string &t);
        ~NumberWithUnits(){};

        /* Read & Getters */
        static void read_units(ifstream &units_file);
        static unordered_map<string, unordered_map<string, double>> getTable();
        double getVal() const { return _val; };
        string getType() const { return _type; };

        /* Unary Operators - friendly */
        friend NumberWithUnits operator+(const NumberWithUnits &n);
        friend NumberWithUnits operator-(const NumberWithUnits &n);

        /* Mathematic Operators - New Object - friendly */
        friend NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator*(const NumberWithUnits &n1, double n2);
        friend NumberWithUnits operator*(double n1, const NumberWithUnits &n2);

        /* Mathematic Operators - Same Object */
        NumberWithUnits &operator++();
        NumberWithUnits &operator--();
        NumberWithUnits operator++(int);
        NumberWithUnits operator--(int);
        NumberWithUnits &operator+=(const NumberWithUnits &n);
        NumberWithUnits &operator-=(const NumberWithUnits &n);
        NumberWithUnits &operator*=(double n);

        /* Boolean Operators - friendly */
        friend bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2);

        /* Stream Operators - friendly */
        friend ostream &operator<<(ostream &s, const NumberWithUnits &n);
        friend istream &operator>>(istream &s, NumberWithUnits &n);
    };
}