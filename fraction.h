#pragma once
#include <iostream>
#include <vector>
#include <string>

// This class is a template for a fraction. It can store any type of integer or floating point number.
// it will store the numbers as a fraction of prime numbers. 
// for example, 1/10 will be stored as 1 / (2 * 5)

class fraction
{
private:
	std::vector<long long unsigned int> m_a;
	std::vector<long long unsigned int> m_b;
	bool m_sign;
	bool m_overflow;
	// returns a vector of prime factors of n
	std::vector<long long unsigned int> prime_factors(long long unsigned int n) const;
	// simplifies the fraction
	void simplify();
	// converts a vector of prime factors to a long long unsigned int
	long long unsigned int vecToLong(const std::vector<long long unsigned int>& v) const;
public:
	// prints the fraction to the console for testing purposes
	void t_tester(const std::string name) const;
	// constructors
	fraction();
	fraction(long long unsigned int a, long long unsigned int b, bool sign);
	fraction(const fraction& other);
	fraction(const long double& num);
	fraction(const int& num);
	fraction(const long long int& num);
	fraction(const float num);
	// getters and setters
	long long unsigned int getA() const;
	long long unsigned int getB() const;
	bool getSign() const;
	bool getOverflow() const;
	void setA(const long long unsigned int& a);
	void setB(const long long unsigned int& b);
	void setSign(const bool sign);
	void setOverflow();
	// converts the fraction to a floating point number
	long double to_float() const;
	// converts the fraction to a string
	std::string to_string() const;
	// overloading nonMath operators
	friend std::ostream& operator<<(std::ostream& os, const fraction& num);
	// overloading math operators
	// assignment operator
	fraction operator=(const fraction& rhs) const;
	fraction operator=(const long double& rhs) const;
	fraction operator=(const int& rhs) const;
	fraction operator=(const long long int& rhs) const;
	fraction operator=(const float& rhs) const;
	// equals operator
	bool operator==(const fraction& rhs) const;
	bool operator==(const long double& rhs) const;
	bool operator==(const int& rhs) const;
	bool operator==(const long long int& rhs) const;
	bool operator==(const float& rhs) const;
	// not equals operator
	bool operator!=(const fraction& rhs) const;
	bool operator!=(const long double& rhs) const;
	bool operator!=(const int& rhs) const;
	bool operator!=(const long long int& rhs) const;
	bool operator!=(const float& rhs) const;
	// greater than
	bool operator>(const fraction& rhs) const;
	bool operator>(const long double& rhs) const;
	bool operator>(const int& rhs) const;
	bool operator>(const long long int& rhs) const;
	bool operator>(const float& rhs) const;
	// less than
	bool operator<(const fraction& rhs) const;
	bool operator<(const long double& rhs) const;
	bool operator<(const int& rhs) const;
	bool operator<(const long long int& rhs) const;
	bool operator<(const float& rhs) const;
	// greater than or equal to
	bool operator>=(const fraction& rhs) const;
	bool operator>=(const long double& rhs) const;
	bool operator>=(const int& rhs) const;
	bool operator>=(const long long int& rhs) const;
	bool operator>=(const float& rhs) const;
	// less than or equal to
	bool operator<=(const fraction& rhs) const;
	bool operator<=(const long double& rhs) const;
	bool operator<=(const int& rhs) const;
	bool operator<=(const long long int& rhs) const;
	bool operator<=(const float& rhs) const;
	// addition
	fraction operator+(const fraction& rhs) const;
	fraction operator+(const long double& rhs) const;
	fraction operator+(const int& rhs) const;
	fraction operator+(const long long int& rhs) const;
	fraction operator+(const float& rhs) const;
	// subtraction
	fraction operator-(const fraction& rhs) const;
	fraction operator-(const long double& rhs) const;
	fraction operator-(const int& rhs) const;
	fraction operator-(const long long int& rhs) const;
	fraction operator-(const float& rhs) const;
	// multiplication
	fraction operator*(const fraction& rhs) const;
	fraction operator*(const long double& rhs) const;
	fraction operator*(const int& rhs) const;
	fraction operator*(const long long int& rhs) const;
	fraction operator*(const float& rhs) const;
	// divisions
	fraction operator/(const fraction& rhs) const;
	fraction operator/(const long double& rhs) const;
	fraction operator/(const int& rhs) const;
	fraction operator/(const long long int& rhs) const;
	fraction operator/(const float& rhs) const;
	//returns the common denominator of two fractions
	std::vector<fraction> commonDenom(const fraction& a, const fraction& b) const;
};

