#include <iostream>
#include <string>
#include <algorithm>
#include "polynomial.h"

using std::istream;
using std::ostream;
using std::string;

string trimSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

polynomial convert(const string &poly)
{
    string polyString = trimSpaces(poly);
    polynomial polyObj;

    if (polyString.size() == 0)
        return polyObj;

    string coef, exp;
    float Coef;
    int Exp;
    bool coefFlag = true, expFlag = false;

    for (int i = 0; i < polyString.size(); i++)
    {
        if (polyString[i] == 'x')
        {
            Coef = stof(coef);
            continue;
        }

        if (polyString[i] == '^')
        {
            coefFlag = false;
            expFlag = true;
            continue;
        }

        if (polyString[i] == '+' || polyString[i] == '-')
            if (!coefFlag && expFlag && i > 0 && polyString[i - 1] != '^')
            {
                coefFlag = true;
                expFlag = false;
                Exp = stoi(exp);
                polyObj.newTerm(Coef, Exp);
                coef.clear();
                exp.clear();
            }

        if (coefFlag)
            coef.push_back(polyString[i]);
        if (expFlag)
            exp.push_back(polyString[i]);

        if (i == polyString.size() - 1)
        {
            Exp = stoi(exp);
            polyObj.newTerm(Coef, Exp);
            coef.clear();
            exp.clear();
        }
    }
    return polyObj;
}

ostream &operator<<(ostream &os, const polynomial &poly)
{
    if (poly.terms == 0)
        return os;

    for (int i = 0; i < poly.terms; i++)
    {
        if (poly.termArray[i].coef > 0)
            os << "+";
        os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp << " ";
    }
    os << std::endl;
    return os;
}

istream &operator>>(istream &is, polynomial &poly)
{
    string polyString;
    getline(is, polyString);
    poly = convert(polyString);
    return is;
}

polynomial::polynomial() : capacity(1), terms(0)
{
    termArray = new term[capacity];
}

polynomial::polynomial(const polynomial &oprd) : capacity(oprd.capacity), terms(oprd.terms)
{
    this->termArray = new term[oprd.capacity];
    for (int i = 0; i < oprd.terms; i++)
    {
        (this->termArray)[i].coef = oprd.termArray[i].coef;
        (this->termArray)[i].exp = oprd.termArray[i].exp;
    }
}

polynomial::polynomial(const string &oprd)
{
    polynomial temp = convert(oprd);
    this->termArray = new term[temp.capacity];
    for (int i = 0; i < temp.terms; i++)
    {
        (this->termArray)[i].coef = temp.termArray[i].coef;
        (this->termArray)[i].exp = temp.termArray[i].exp;
    }
    this->capacity = temp.capacity;
    this->terms = temp.terms;
}

polynomial::~polynomial()
{
    delete[] termArray;
}

void polynomial::newTerm(const float Coef, const int Exp)
{
    if (terms == capacity)
    {
        capacity *= 2;
        term *temp = new term[capacity];
        std::copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = Coef;
    termArray[terms++].exp = Exp;
}

polynomial polynomial::operator+(const polynomial &oprd)
{
    if(terms == 0 && oprd.terms == 0) return *this;
    
    polynomial result;
    int thisPos = 0, oprdPos = 0;

    while ((thisPos < terms) && (oprdPos < oprd.terms))
    {
        if (termArray[thisPos].exp == oprd.termArray[oprdPos].exp)
        {
            float t = termArray[thisPos].coef + oprd.termArray[oprdPos].coef;
            if (t) // coefficient is not zero
                result.newTerm(t, termArray[thisPos].exp);
            thisPos++;
            oprdPos++;
        }
        else if (termArray[thisPos].exp < oprd.termArray[oprdPos].exp)
        {
            result.newTerm(oprd.termArray[oprdPos].coef, oprd.termArray[oprdPos].exp);
            oprdPos++;
        }
        else
        {
            result.newTerm(termArray[thisPos].coef, termArray[thisPos].exp);
            thisPos++;
        }
    }

    for (; thisPos < terms; thisPos++)
        result.newTerm(termArray[thisPos].coef, termArray[thisPos].exp);

    for (; oprdPos < oprd.terms; oprdPos++)
        result.newTerm(oprd.termArray[oprdPos].coef, oprd.termArray[oprdPos].exp);

    return result;
}

polynomial polynomial::operator-(const polynomial &oprd)
{
    return *this + (-oprd);
}

polynomial operator-(const polynomial &oprd)
{
    polynomial polyObj = oprd;
    for (int i = 0; i < oprd.terms; i++)
        polyObj.termArray[i].coef *= -1;
    return polyObj;
}

polynomial polynomial::operator*(const polynomial &oprd)
{
    polynomial result;

    for (int i = 0; i < this->terms; i++)
    {
        polynomial temp;
        for (int j = 0; j < oprd.terms; j++)
            temp.newTerm(this->termArray[i].coef * oprd.termArray[j].coef, this->termArray[i].exp + oprd.termArray[j].exp);
        result += temp;
    }
    return result;
}

void polynomial::operator=(const polynomial &oprd)
{
    delete[] this->termArray;
    this->termArray = new term[oprd.capacity];
    for (int i = 0; i < oprd.terms; i++)
    {
        this->termArray[i].coef = oprd.termArray[i].coef;
        this->termArray[i].exp = oprd.termArray[i].exp;
    }
    this->capacity = oprd.capacity;
    this->terms = oprd.terms;
}

void polynomial::operator=(const string &oprd)
{
    polynomial temp = convert(oprd);
    *this = temp;
}

void polynomial::operator+=(const polynomial& oprd) { *this = *this + oprd; }
void polynomial::operator-=(const polynomial& oprd) { *this = *this - oprd; }
void polynomial::operator*=(const polynomial& oprd) { *this = *this * oprd; }

//float polynomial::discriminant() { }
//bool polynomial::findRoot(float *rt1, float *rt2, float *rt3) {}