#include "rational.h"

#include <vector>

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {  // NOLINT
}

Rational::Rational(int numer, int denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    Set(numer, denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero{};
    }
    Set(numer_, value);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int nok = std::lcm(lhs.denom_, rhs.denom_);
    int ldelta = nok / lhs.denom_;
    int rdelta = nok / rhs.denom_;
    lhs.Set(ldelta * lhs.numer_ + rdelta * rhs.numer_, nok);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.numer_ * rhs.numer_, lhs.denom_ * rhs.denom_);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.Set(ratio.numer_ + ratio.denom_, ratio.denom_);
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.Set(ratio.numer_ - ratio.denom_, ratio.denom_);
    return ratio;
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int numerator = static_cast<int>(numer / std::gcd(numer, denom));
    int denominator = static_cast<int>(denom / std::gcd(numer, denom));
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
    numer_ = numerator;
    denom_ = denominator;
}

Rational operator+(const Rational& ratio) {
    auto temp = ratio;
    return temp;
}

Rational operator-(const Rational& ratio) {
    return Rational(-1 * ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    int nok = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int ldelta = nok / lhs.GetDenominator();
    int rdelta = nok / rhs.GetDenominator();
    lhs.Set(ldelta * lhs.GetNumerator() - rdelta * rhs.GetNumerator(), nok);
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }
    lhs.Set(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator());
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational temp;
    int nok = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int ldelta = nok / lhs.GetDenominator();
    int rdelta = nok / rhs.GetDenominator();
    temp.Set(ldelta * lhs.GetNumerator() + rdelta * rhs.GetNumerator(), nok);
    return temp;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational temp;
    int nok = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int ldelta = nok / lhs.GetDenominator();
    int rdelta = nok / rhs.GetDenominator();
    temp.Set(ldelta * lhs.GetNumerator() - rdelta * rhs.GetNumerator(), nok);
    return temp;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational temp;
    temp.Set(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator());
    return temp;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }
    Rational temp;
    temp.Set(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator());
    return temp;
}

Rational operator++(Rational& ratio, int) {
    auto temp = ratio;
    ++ratio;
    return temp;
}

Rational operator--(Rational& ratio, int) {
    auto temp = ratio;
    --ratio;
    return temp;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    if (lhs.GetDenominator() == rhs.GetDenominator()) {
        return lhs.GetNumerator() < rhs.GetNumerator();
    } else {
        return lhs.GetNumerator() * rhs.GetDenominator() < lhs.GetDenominator() * rhs.GetNumerator();
    }
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs) && !(lhs > rhs);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    int num = 0;
    int denom = 1;
    is >> num;
    if (is.peek() == '/') {
        is.ignore(1);
        is >> denom;
    }
    ratio.Set(num, denom);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        os << ratio.GetNumerator();
    } else {
        os << ratio.GetNumerator() << '/' << ratio.GetDenominator();
    }
    return os;
}