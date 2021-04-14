#ifndef __POLY_H__
#define __POLY_H__

#include <iostream>
#include <vector>

//using namespace std;

class poly
{
    public:
        poly();
        poly(double value);

        int size() const;

        double operator()(double x0);

        double& operator[](unsigned int index);
        double operator[](unsigned int index) const;

        friend poly operator+(const poly& p1, const poly& p2);
        friend poly operator*(const poly& p1, const poly& p2);

        friend std::ostream& operator<<(std::ostream& output, const poly& p);

        void reset();
        
    private:
        std::vector<double> data;
};

#endif /* __POLY_H__ */
//g++ -o main testpoly.cpp poly.h poly.cpp -Wall -pedantic
//valgrind ./main