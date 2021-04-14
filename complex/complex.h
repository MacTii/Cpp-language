#ifndef __Complex_H__
#define __Complex_H__
#include <iostream>
#include <math.h>

using namespace std;

class Complex
{
    public:
        double Real, Imag;
        Complex (double Real=0, double Imag=0)
        {
            this->Real = Real;
            this->Imag = Imag;
        };
        Complex& operator=(const Complex& s);
        Complex& operator-=(const Complex& s1);
        Complex operator- () const
        {
            return Complex(-Real,-Imag);
        };
        double abs();
        double phase(const Complex& c);
        Complex conj(const Complex& c);
};

ostream& operator<<(ostream& o, const Complex& c);
Complex operator-(const Complex& s1, const Complex& s2);
Complex operator+(const Complex& s1, const Complex& s2);
Complex operator/(const Complex& s1, const Complex& s2);
Complex operator/=(Complex& s1, Complex& s2);

#endif