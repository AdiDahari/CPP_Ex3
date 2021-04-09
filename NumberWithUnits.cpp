#include "NumberWithUnits.hpp"
#include <iostream>
using namespace std;

namespace ariel
{
    static map<string, map<string, double>> conv;

    void NumberWithUnits::read_units(ifstream &units_file)
    {
        double n1, n2;
        string t1, t2, eq;
        while (units_file >> n1 >> t1 >> eq >> n2 >> t2)
        {
            conv[t1][t2] = n2 / n1;
            conv[t2][t1] = n1 / n2;
        }
    }

    NumberWithUnits operator+(const NumberWithUnits &n)
    {
        return NumberWithUnits(n.val, n.type);
    }
    NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double final_val;
        if (n1.type == n2.type)
        {
            final_val = n1.val + n2.val;
            return NumberWithUnits(final_val, n1.type);
        }

        try
        {
            double r = conv.at(n2.type).at(n1.type);
            final_val = n1.val + (r * n2.val);
            return NumberWithUnits(final_val, n1.type);
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }
    NumberWithUnits operator+=(NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1.type == n2.type)
        {
            n1.val += n2.val;
            return n1;
        }
        try
        {
            double r = conv.at(n2.type).at(n1.type);
            n1.val += (r * n2.val);
            return n1;
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }
    NumberWithUnits operator-(const NumberWithUnits &n)
    {
        return NumberWithUnits(-n.val, n.type);
    }
    NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double final_val;
        if (n1.type == n2.type)
        {
            final_val = n1.val - n2.val;
            return NumberWithUnits(final_val, n1.type);
        }
        try
        {
            double r = conv.at(n2.type).at(n1.type);
            final_val = n1.val - (r * n2.val);
            return NumberWithUnits(final_val, n1.type);
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }
    NumberWithUnits operator-=(NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1.type == n2.type)
        {
            n1.val -= n2.val;
            return n1;
        }
        try
        {
            double r = conv.at(n2.type).at(n1.type);
            n1.val -= (r * n2.val);
            return n1;
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }

    NumberWithUnits operator++(NumberWithUnits &n)
    {
        n.val += 1;
        return n;
    }
    NumberWithUnits operator--(NumberWithUnits &n)
    {
        n.val += 1;
        return n;
    }

    NumberWithUnits operator*(const NumberWithUnits &n1, double n2)
    {
        return NumberWithUnits(n1.val * n2, n1.type);
    }
    NumberWithUnits operator*(double n1, const NumberWithUnits &n2)
    {
        return NumberWithUnits(n2.val * n1, n2.type);
    }
    NumberWithUnits operator*=(NumberWithUnits &n1, double n2)
    {
        n1.val *= n2;
        return n1;
    }
    NumberWithUnits operator*=(double n1, NumberWithUnits &n2)
    {
        n2.val *= n2;
        return n2;
    }

    bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1.type == n2.type)
        {
            return (n1.val < n2.val);
        }
        try
        {
            double r = conv.at(n2.type).at(n1.type);
            return (n1.val < (r * n2.val));
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }
    bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1.type == n2.type)
        {
            return (n1.val > n2.val);
        }
        try
        {
            double r = conv.at(n2.type).at(n1.type);
            return (n1.val > (r * n2.val));
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }
    bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1.type == n2.type)
        {
            return (n1.val <= n2.val);
        }
        try
        {
            double r = conv.at(n2.type).at(n1.type);
            return (n1.val <= (r * n2.val));
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }
    bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1.type == n2.type)
        {
            return (n1.val >= n2.val);
        }
        try
        {
            double r = conv.at(n2.type).at(n1.type);
            return (n1.val >= (r * n2.val));
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }
    bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1.type == n2.type)
        {
            return (n1.val == n2.val);
        }
        try
        {
            double r = conv.at(n2.type).at(n1.type);
            return (n1.val == (r * n2.val));
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
        }
    }
    bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return !(n1 == n2);
    }

    ostream &operator<<(ostream &s, const NumberWithUnits &n)
    {
        return (s << n.val << "[" + n.type + "]");
    }
    istream &operator>>(istream &s, NumberWithUnits &n)
    {
        string eq;
        s >> n.val >> eq >> n.type;
        return s;
    }

}