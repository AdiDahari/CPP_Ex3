#include "NumberWithUnits.hpp"
#include <iostream>
using namespace std;
const double EPS = 0.00001;
static unordered_map<string, unordered_map<string, double>> conv;

namespace ariel
{

    NumberWithUnits::NumberWithUnits(double v, const string &t)
    {
        bool flag = false;
        for (auto &p1 : conv)
        {
            if (flag)
            {
                break;
            }

            for (auto &p2 : p1.second)
            {
                if (t == p2.first)
                {
                    flag = true;
                    break;
                }
            }
        }
        if (flag)
        {
            _val = v;
            _type = t;
        }
        else
        {
            throw invalid_argument("Not a valid type of unit!");
        }
    }
    void NumberWithUnits::read_units(ifstream &units_file)
    {
        if (units_file.fail())
        {
            throw invalid_argument("Could not open units file!");
        }
        double val1 = 0;
        double val2 = 0;
        string type1;
        string type2;
        string eq;
        while (units_file >> val1 >> type1 >> eq >> val2 >> type2)
        {
            if (val1 == 0 || val2 == 0 || type1.empty() || type2.empty())
            {
                continue;
            }
            conv[type1][type2] = val2 / val1;
            conv[type2][type1] = val1 / val2;

            for (auto &p : conv[type2])
            {
                if (type1 != p.first)
                {
                    conv[type1][p.first] = p.second / (val1 / val2);
                    conv[p.first][type1] = (val1 / val2) / p.second;
                }
            }
            for (auto &p : conv[type1])
            {
                if (type2 != p.first)
                {
                    conv[type2][p.first] = p.second / (val1 * val2);
                    conv[p.first][type2] = (val1 * val2) / p.second;
                }
            }
        }
    }

    unordered_map<string, unordered_map<string, double>> NumberWithUnits::getTable()
    {
        return conv;
    }

    NumberWithUnits operator+(const NumberWithUnits &n)
    {
        return NumberWithUnits(n._val, n._type);
    }

    NumberWithUnits operator-(const NumberWithUnits &n)
    {
        return NumberWithUnits(-n._val, n._type);
    }

    NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double final_val = 0;
        if (n1._type == n2._type)
        {
            final_val = n1._val + n2._val;
            return NumberWithUnits(final_val, n1._type);
        }

        try
        {
            double r = conv.at(n2._type).at(n1._type);
            final_val = n1._val + (r * n2._val);
            return NumberWithUnits(final_val, n1._type);
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2._type + "] cannot be converted to [" + n1._type + "]");
        }
    }

    NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double final_val = 0;
        if (n1._type == n2._type)
        {
            final_val = n1._val - n2._val;
            return NumberWithUnits(final_val, n1._type);
        }
        try
        {
            double r = conv.at(n2._type).at(n1._type);
            final_val = n1._val - (r * n2._val);
            return NumberWithUnits(final_val, n1._type);
        }
        catch (const exception &e)
        {
            throw invalid_argument("Units do not match - [" + n2._type + "] cannot be converted to [" + n1._type + "]");
        }
    }

    NumberWithUnits operator*(const NumberWithUnits &n1, double n2)
    {
        return NumberWithUnits(n1._val * n2, n1._type);
    }

    NumberWithUnits operator*(double n1, const NumberWithUnits &n2)
    {
        return NumberWithUnits(n2._val * n1, n2._type);
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->_val += 1;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->_val -= 1;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int)
    {
        NumberWithUnits n(this->_val++, this->_type);
        return n;
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
        NumberWithUnits n(this->_val--, this->_type);
        return n;
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n)
    {
        if (this->_type == n._type)
        {
            this->_val += n._val;
            return *this;
        }
        try
        {
            double r = conv.at(n._type).at(this->_type);
            this->_val += (r * n._val);
            return *this;
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n._type + "] cannot be converted to [" + this->_type + "]");
        }
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &n)
    {
        if (this->_type == n._type)
        {
            this->_val -= n._val;
            return *this;
        }
        try
        {
            double r = conv.at(n._type).at(this->_type);
            this->_val -= (r * n._val);
            return *this;
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n._type + "] cannot be converted to [" + this->_type + "]");
        }
    }

    NumberWithUnits &NumberWithUnits::operator*=(double n2)
    {
        this->_val *= n2;
        return *this;
    }

    bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1._type == n2._type)
        {
            return (n1._val < n2._val);
        }
        try
        {
            double r = conv.at(n2._type).at(n1._type);
            return (n1._val < (r * n2._val));
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n2._type + "] cannot be converted to [" + n1._type + "]");
        }
    }

    bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1._type == n2._type)
        {
            return (n1._val > n2._val);
        }
        try
        {
            double r = conv.at(n2._type).at(n1._type);
            return (n1._val > (r * n2._val));
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n2._type + "] cannot be converted to [" + n1._type + "]");
        }
    }

    bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1._type == n2._type)
        {
            return (abs(n1._val - n2._val) < EPS);
        }
        try
        {
            double r = conv.at(n2._type).at(n1._type);
            return (abs(n1._val - (r * n2._val)) < EPS);
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n2._type + "] cannot be converted to [" + n1._type + "]");
        }
    }

    bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1._type == n2._type)
        {
            return (n1._val <= n2._val);
        }
        try
        {
            double r = conv.at(n2._type).at(n1._type);
            return ((n1._val < (r * n2._val) || n1 == n2));
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n2._type + "] cannot be converted to [" + n1._type + "]");
        }
    }

    bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        if (n1._type == n2._type)
        {
            return (n1._val >= n2._val);
        }
        try
        {
            double r = conv.at(n2._type).at(n1._type);
            return ((n1._val > (r * n2._val) || n1 == n2));
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n2._type + "] cannot be converted to [" + n1._type + "]");
        }
    }

    bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return !(n1 == n2);
    }

    ostream &operator<<(ostream &s, const NumberWithUnits &n)
    {
        return (s << n._val << "[" + n._type + "]");
    }

    istream &operator>>(istream &s, NumberWithUnits &n)
    {
        char c = 0;
        string t;
        double v = 0;
        s >> v >> c >> t >> c;
        if (t[t.length() - 1] == ']')
        {
            t.pop_back();
        }
        if (c == '-')
        {
            s.putback('-');
        }
        try
        {
            conv.at(t);
            n._val = v;
            n._type = t;
            return s;
        }
        catch (const exception &e)
        {
            throw std::invalid_argument(t + " is not a valid unit!");
        }
    }

}