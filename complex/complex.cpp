#include <iostream>
#include <math.h>
#include "complex.h"

using namespace std;

Complex& Complex::operator=(const Complex& s)
{
    Real = s.Real;
    Imag = s.Imag;
    return *this;
};

Complex operator-(const Complex& s1, const Complex& s2)
{
    return Complex(s1.Real-s2.Real,s1.Imag-s2.Imag);
};

Complex operator+(const Complex& s1, const Complex& s2)
{
    return Complex(s1.Real+s2.Real,s1.Imag+s2.Imag);
};

Complex& Complex::operator-=(const Complex& s)
{
    Real -= s.Real;
    Imag -= s.Imag;
    return *this;
};

Complex operator/(Complex& s1, Complex& s2)
{
    Complex s3(0,0);
    double w;
    w=s2.Real * s2.Real + s2.Imag * s2.Imag;
    if (w > 0)
    {       
        s3.Real = (s1.Real * s2.Real + s1.Imag * s2.Imag)/w;
        s3.Imag = (s2.Real * s1.Imag - s1.Real * s2.Imag)/w;
    }
    return Complex(s3.Real,s3.Imag);
};

Complex operator/=(Complex& s1, Complex& s2)
{
    return Complex(s1.Real/=s2.Real,s1.Imag/=s2.Imag);
};

ostream& operator<<(ostream& o, const Complex& c)
{
    o<<c.Real<<"+"<<c.Imag<<"i"<<endl;
    return o;
}

double Complex::abs()
{
    return sqrt(Real*Real+Imag*Imag);
}

double phase(const Complex& c)
{
    return atan(c.Imag/c.Real);
}

Complex Complex::conj(const Complex& c)
{
    return Complex(c.Real,-c.Imag);
}