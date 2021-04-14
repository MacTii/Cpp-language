#include "poly.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>

poly::poly()
{
    data.resize(1);
}

poly::poly(double value)
{
    data.push_back(value);
}

int poly::size() const
{
    return data.size();
}

double poly::operator()(double x0)
{
    const size_t size = data.size();

    double result = data[size - 1];

    for(int i = size - 2; i >= 0; i--)
    {
        result *= x0;
        result += data[i];
    }

    return result;
}

double& poly::operator[](unsigned int index)
{
    if(index >= (unsigned int)data.size()) 
    {
        data.resize(index + 1); 
    }

    return data[index];
}

double poly::operator[](unsigned int index) const
{
    assert(index < (unsigned int)data.size());

    return data[index];
}

poly operator+(const poly& p1, const poly& p2)
{
    poly result;

    unsigned int size = std::max(p1.size(),p2.size());
    result.data.resize(size);

    for(unsigned int i = 0; i < size; i++)
    {
        double& data = result.data[i];

        if(i < (unsigned int)p1.size()) data = p1[i];
        if(i < (unsigned int)p2.size()) data += p2[i];
    }

    return result;
}

poly operator*(const poly& p1, const poly& p2)
{
    poly result;

    result.data.resize(p1.size() + p2.size() - 1);

    for(size_t i = 0; i < (unsigned int)p1.size(); i++)
    {
        for(size_t j = 0; j < (unsigned int)p2.size(); j++)
        {
            result[i + j] += p1[i] * p2[j];
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& output, const poly& p)
{
    const int size = p.size();

    bool value_printed = false;

    for(int i = size - 1; i >= 0; i--)
    {
        const double value = p[i];

        if(value == 0) continue;
        if(value_printed) output << " + ";
        if(value != 1) output << value;
        if(i != 0)
        {
            output << 'x';
            if(i > 1)
            {
                output << '^' << i;
            }
        }
        value_printed = true;
    }
    return output;
}

void poly::reset()
{
    data.clear();
}