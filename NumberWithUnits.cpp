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
            val = v;
            type = t;
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
        return NumberWithUnits(n.val, n.type);
    }

    NumberWithUnits operator-(const NumberWithUnits &n)
    {
        return NumberWithUnits(-n.val, n.type);
    }

    NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double final_val = 0;
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

    NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double final_val = 0;
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

    NumberWithUnits operator*(const NumberWithUnits &n1, double n2)
    {
        return NumberWithUnits(n1.val * n2, n1.type);
    }

    NumberWithUnits operator*(double n1, const NumberWithUnits &n2)
    {
        return NumberWithUnits(n2.val * n1, n2.type);
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->val += 1;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->val -= 1;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n)
    {
        if (this->type == n.type)
        {
            this->val += n.val;
            return *this;
        }
        try
        {
            double r = conv.at(n.type).at(this->type);
            this->val += (r * n.val);
            return *this;
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n.type + "] cannot be converted to [" + this->type + "]");
        }
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &n)
    {
        if (this->type == n.type)
        {
            this->val -= n.val;
            return *this;
        }
        try
        {
            double r = conv.at(n.type).at(this->type);
            this->val -= (r * n.val);
            return *this;
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n.type + "] cannot be converted to [" + this->type + "]");
        }
    }

    NumberWithUnits &NumberWithUnits::operator*=(double n2)
    {
        this->val *= n2;
        return *this;
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
            throw std::invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
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
            throw std::invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
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
            return (abs(n1.val - (r * n2.val)) < EPS);
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
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
            return ((n1.val < (r * n2.val) || n1 == n2));
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
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
            return ((n1.val > (r * n2.val) || n1 == n2));
        }
        catch (const exception &e)
        {
            throw std::invalid_argument("Units do not match - [" + n2.type + "] cannot be converted to [" + n1.type + "]");
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
        char c = 0;
        string t;
        s >> n.val >> c >> t >> c;
        if (t[t.length() - 1] == ']')
        {
            t.pop_back();
        };
        n.type = t;
        return s;
    }

}