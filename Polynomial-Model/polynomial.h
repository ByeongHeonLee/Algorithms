/* Constranints

1) 1(one) must be written as coefficient or exponent.
2) Positive symbol and negative symbol must be written.
3) All terms must be written their exponent. (ex) +1x^2 -3x^1 -7x^0)

*/

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <iostream>

using std::istream;
using std::ostream;
using std::string;

class polynomial;

class term
{
    friend polynomial;
    friend polynomial convert(const string &poly);

private:
    float coef; // Coefficient
    int exp;    // Exponent

public:                                                  // Operators
    friend polynomial operator-(const polynomial &oprd); // Negation

public: // IO
    friend ostream &operator<<(ostream &os, const polynomial &poly);
    friend istream &operator>>(istream &is, polynomial &poly);
};

class polynomial
{
    friend polynomial convert(const string &poly);

private:
    term *termArray; // Array for non-zero terms
    int capacity;    // Size of "temrArray"
    int terms;       // # of non-zero terms

public: // Constructors
    polynomial();
    polynomial(const polynomial &oprd);
    polynomial(const string &oprd);
    ~polynomial();

public: // Operators
    friend polynomial operator-(const polynomial &oprd); // Negation
    polynomial operator+(const polynomial &oprd);
    polynomial operator-(const polynomial &oprd); // Difference
    polynomial operator*(const polynomial &oprd);
    void operator=(const polynomial &oprd);
    void operator=(const string &oprd);
    void operator+=(const polynomial &oprd);
    void operator-=(const polynomial &oprd);
    void operator*=(const polynomial &oprd);

public: // IO
    friend ostream &operator<<(ostream &os, const polynomial &poly);
    friend istream &operator>>(istream &is, polynomial &poly);

public: // Mathematical Tools
    float discriminant();
    bool findRoot(float *rt1, float *rt2, float *rt3);

private:
    void newTerm(const float coef, const int exp);
};

#endif