#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>

using namespace std;

class BigInteger {
private:
    string number;
    bool sign;

public:
    BigInteger();
    BigInteger(string s);
    BigInteger(string s, bool sin);
    BigInteger(int n);
    void setNumber(string s);
    const string& getNumber();
    void setSign(bool s);
    const bool& getSign();
    BigInteger absolute();
    void operator=(BigInteger b);
    bool operator==(BigInteger b);
    bool operator!=(BigInteger b);
    bool operator>(BigInteger b);
    bool operator<(BigInteger b);
    bool operator>=(BigInteger b);
    bool operator<=(BigInteger b);
    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);
    BigInteger operator+(BigInteger b);
    BigInteger operator-(BigInteger b);
    BigInteger operator*(BigInteger b);
    BigInteger operator/(BigInteger b);
    BigInteger operator%(BigInteger b);
    BigInteger& operator+=(BigInteger b);
    BigInteger& operator-=(BigInteger b);
    BigInteger& operator*=(BigInteger b);
    BigInteger& operator/=(BigInteger b);
    BigInteger& operator%=(BigInteger b);
    BigInteger& operator[](int n);
    BigInteger operator-();
    operator string();

private:
    bool equals(BigInteger n1, BigInteger n2);
    bool less(BigInteger n1, BigInteger n2);
    bool greater(BigInteger n1, BigInteger n2);
    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
    pair<string, long long> divide(string n, long long den);
    string toString(long long n);
    long long toInt(string s);
};

#endif