#include "fraction.h"
#include <limits>
#include <string>

std::vector<long long unsigned int> fraction::prime_factors(long long unsigned int n) const
{
	std::vector<long long unsigned int> factors;
	if (n == 0)
	{
		return { 0 };
	}
	if (n == 1)
	{
		return { 1 };
	}
	else
	{
		long long unsigned int i = 2;
		while (n > 1)
		{
			if (n % i == 0)
			{
				factors.push_back(i);
				n /= i;
			}
			else
			{
				i++;
			}
		}
	}
	return factors;
}

void fraction::simplify()
{
	for (auto i = 0; i < m_a.size(); i++)
	{
		for (auto j = 0; j < m_b.size(); j++)
		{
			if (m_a[i] == m_b[j])
			{
				m_a.erase(m_a.begin() + i);
				m_b.erase(m_b.begin() + j);
				i = 0;
				j = 0;
			}
		}
	}
	if(m_a.size() == 0)
	{
		m_a.push_back(1);
	}
	if (m_b.size() == 0)
	{
		m_b.push_back(1);
	}
	
}

long long unsigned int fraction::vecToLong(const std::vector<long long unsigned int>& v) const
{
	long long unsigned int result = 1;
	for (auto i = 0; i < v.size(); i++)
	{
		result *= v[i];
	}
	return result;
}

fraction::fraction()
{
	m_a = { 0 };
	m_b = { 1 };
	m_sign = true;
	m_overflow = false;
}

fraction::fraction(long long unsigned int a, long long unsigned int b, bool sign)
{
	m_a = prime_factors(a);
	m_b = prime_factors(b);
	m_sign = sign;
	setOverflow();	
	simplify();
}

long long unsigned int fraction::getA() const
{
	return vecToLong(m_a);
}

long long unsigned int fraction::getB() const
{
		return vecToLong(m_b);
}

bool fraction::getSign() const
{
	return m_sign;
}

bool fraction::getOverflow() const
{
		return m_overflow;
}

void fraction::setA(const long long unsigned int& a)
{
	m_a = prime_factors(a);
	simplify();
}

void fraction::setB(const long long unsigned int& b)
{
	m_b = prime_factors(b);
	simplify();
}

void fraction::setSign(const bool sign)
{
		m_sign = sign;
		simplify();
}

void fraction::setOverflow()
{

	if(m_a.size() > 0 && m_b.size() > 0)
	{
		m_overflow = false;
	}
	else if(getA() > (std::numeric_limits<long long unsigned int>::max()) || getB() >
		(std::numeric_limits<long long unsigned int>::max()))
	{
		m_overflow = true;
	}
	else if(to_float() > (std::numeric_limits<long double>::max()) || to_float() <
		(std::numeric_limits<long double>::min()))
	{
		m_overflow = true;
	}
	else
	{
		m_overflow = false;
	}
}

long double fraction::to_float() const
{
	if(getSign() == false)
	{
		return (long double)getA() / (long double)getB() * -1;
	}
	return (long double)getA() / (long double)getB();
}

std::string fraction::to_string() const
{
	std::string result = "";
	if (getA() < (std::numeric_limits<long long unsigned int>::max()) &&
		(getB() < (std::numeric_limits<long long unsigned int>::max())))
	{
	if (getSign() == false)
		{
			result += "-";
		}
		result += std::to_string(getA());
		result += "/";
		result += std::to_string(getB());
	}
	else
	{
		for(auto i = 0; i < m_a.size(); i++)
		{
			result += std::to_string(m_a[i]);
			if(i != m_a.size() - 1)
			{
				result += " * ";
			}
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const fraction& num)
{
	if (num.getOverflow())
	{
		os << num.to_string();
	}
	else
	{
		os << num.to_float();
	}
	return os;
}

void fraction::t_tester(const std::string name = "this") const
{
	std::cout << name << " a: " << getA() << " b: " << getB();
	std::cout << " sign: " << getSign() << " overflow: " << getOverflow() << std::endl;
}

bool fraction::operator==(const fraction& rhs) const
{
	std::vector<fraction> a = commonDenom(*this, rhs);
	if(a[0].getA() == a[1].getA() && a[0].getSign() == a[1].getSign())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool fraction::operator>(const fraction& rhs) const
{
	std::vector<fraction> a = commonDenom(*this, rhs);
	if(a[0].getSign() > a[1].getSign())
	{
		return true;
	}
	else if(a[0].getSign() < a[1].getSign())
	{
		return false;
	}
	else if(a[0].getA() > a[1].getA())
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<fraction> fraction::commonDenom(const fraction& a, const fraction& b) const
{
	std::vector<fraction> result;
	fraction temp1 = a;
	fraction temp2 = b;
	temp1.m_a.insert(temp1.m_a.end(), b.m_b.begin(), b.m_b.end());
	temp1.m_b.insert(temp1.m_b.end(), b.m_b.begin(), b.m_b.end());
	temp2.m_a.insert(temp2.m_a.end(), a.m_b.begin(), a.m_b.end());
	temp2.m_b.insert(temp2.m_b.end(), a.m_b.begin(), a.m_b.end());
	result.push_back(temp1);
	result.push_back(temp2);
	return result;
}

fraction fraction::operator+(const fraction& rhs) const
{
	std::vector<fraction> a = commonDenom(*this, rhs);
	fraction result;
	if(a[0].getSign() == a[1].getSign())
	{
		result.setA(a[0].getA() + a[1].getA());
		result.setB(a[0].getB());
		result.setSign(a[0].getSign());
	}
	else
	{
		if(a[0].getA() > a[1].getA())
		{
			result.setA(a[0].getA() - a[1].getA());
			result.setB(a[0].getB());
			result.setSign(a[0].getSign());
		}
		else
		{
			result.setA(a[1].getA() - a[0].getA());
			result.setB(a[0].getB());
			result.setSign(a[1].getSign());
		}
	}
	result.simplify();

	return result;
}

fraction fraction::operator-(const fraction& rhs) const
{
	fraction temp = *this;
	fraction temp1 = rhs;
	temp1.setSign(!temp1.getSign());
	return temp + temp1;
}

fraction fraction::operator*(const fraction& rhs) const
{
	fraction result;
	if (getSign() == true && rhs.getSign() == true)
	{
		result.setSign(true);
	}
	else if (getSign() == false && rhs.getSign() == false)
	{
		result.setSign(true);
	}
	else
	{
		result.setSign(false);
	}
	result.setA(getA() * rhs.getA());
	result.setB(getB() * rhs.getB());
	result.setSign(getSign() == rhs.getSign());
	result.simplify();
	return result;
}

fraction fraction::operator/(const fraction& rhs) const
{
	fraction result;
	if (getSign() == true && rhs.getSign() == true)
	{
		result.setSign(true);
	}
	else if (getSign() == false && rhs.getSign() == false)
	{
		result.setSign(true);
	}
	else
	{
		result.setSign(false);
	}
	result.setA(getA() * rhs.getB());
	result.setB(getB() * rhs.getA());
	return result;
}

bool fraction::operator!=(const fraction& rhs) const
{
	return !(*this == rhs);
}

bool fraction::operator<(const fraction& rhs) const
{
	return !(*this > rhs);
}

bool fraction::operator>=(const fraction& rhs) const
{
	return *this > rhs || *this == rhs;
}

bool fraction::operator<=(const fraction& rhs) const
{
	return *this < rhs || *this == rhs;
}

fraction::fraction(const fraction& other)
{
	m_a = other.m_a;
	m_b = other.m_b;
	m_sign = other.m_sign;
	m_overflow = other.m_overflow;
}

fraction fraction::operator=(const fraction& rhs) const
{
	return rhs;
}

fraction::fraction(const long double& num)
{
	if (num < 0)
	{
		m_sign = false;
	}
	else
	{
		m_sign = true;
	}
	int count = 0;
	bool done = false;
	std::string temp = std::to_string(num);
	for(auto i = 0; i < temp.size(); i++)
	{
		if (temp[i] == '.')
		{
			done = true;
		}
		else if (done)
		{
			count++;
		}
	}
	long long unsigned int count1 = 1;
	for(auto i = 0; i < count; i++)
	{
		count1 *= 10;
	}
	std::string temp1;
	for (auto i = 0; i < temp.size(); i++)
	{
		if(temp[i] == '.' || temp[i] == '-')
		{
			continue;
		}
		temp1 += temp[i];
	}
	m_a = prime_factors(std::stoull(temp1));
	m_b = prime_factors(count1);
	setOverflow();
	simplify();
}

fraction::fraction(const float num)
{
	if (num < 0)
	{
		m_sign = false;
	}
	else
	{
		m_sign = true;
	}
	int count = 0;
	bool done = false;
	std::string temp = std::to_string(num);
	for (auto i = 0; i < temp.size(); i++)
	{
		if (temp[i] == '.')
		{
			done = true;
		}
		else if (done)
		{
			count++;
		}
	}
	long long unsigned int count1 = 1;
	for (auto i = 0; i < count; i++)
	{
		count1 *= 10;
	}
	std::string temp1;
	for (auto i = 0; i < temp.size(); i++)
	{
		if (temp[i] == '.' || temp[i] == '-')
		{
			continue;
		}
		temp1 += temp[i];
	}
	m_a = prime_factors(std::stoull(temp1));
	m_b = prime_factors(count1);
	setOverflow();
	simplify();
}

fraction::fraction(const long long int& num)
{
	if(num < 0)
	{
		m_sign = false;
	}
	else
	{
		m_sign = true;
	}
	m_a = prime_factors(num);
	m_b = { 1 };
	setOverflow();
	simplify();
}

fraction::fraction(const int& num)
{
	m_a = prime_factors(num);
	m_b = { 1 };
	m_sign = true;
	setOverflow();
	simplify();
}

fraction fraction::operator=(const long double& rhs) const
{
	return fraction(rhs);
}

fraction fraction::operator=(const int& rhs) const
{
	return fraction(rhs);
}

fraction fraction::operator=(const long long int& rhs) const
{
	return fraction(rhs);
}

fraction fraction::operator=(const float& rhs) const
{
	return fraction(rhs);
}

bool fraction::operator==(const long double& rhs) const
{
	return *this == fraction(rhs);
}

bool fraction::operator==(const int& rhs) const
{
	return *this == fraction(rhs);
}

bool fraction::operator==(const long long int& rhs) const
{
	return *this == fraction(rhs);
}

bool fraction::operator==(const float& rhs) const
{
	return *this == fraction(rhs);
}

bool fraction::operator!=(const long double& rhs) const
{
	return !(*this == rhs);
}

bool fraction::operator!=(const int& rhs) const
{
	return !(*this == rhs);
}

bool fraction::operator!=(const long long int& rhs) const
{
	return !(*this == rhs);
}

bool fraction::operator!=(const float& rhs) const
{
	return !(*this == rhs);
}

bool fraction::operator>(const long double& rhs) const
{
	return *this > fraction(rhs);
}

bool fraction::operator>(const int& rhs) const
{
	return *this > fraction(rhs);
}

bool fraction::operator>(const long long int& rhs) const
{
	return *this > fraction(rhs);
}

bool fraction::operator>(const float& rhs) const
{
	return *this > fraction(rhs);
}

bool fraction::operator<(const long double& rhs) const
{
		return *this < fraction(rhs);
}

bool fraction::operator<(const int& rhs) const
{
	return *this < fraction(rhs);
}

bool fraction::operator<(const long long int& rhs) const
{
		return *this < fraction(rhs);

}

bool fraction::operator<(const float& rhs) const
{
	return *this < fraction(rhs);
}

bool fraction::operator<=(const long double& rhs) const
{
	return *this <= fraction(rhs);
}

bool fraction::operator<=(const int& rhs) const
{
	return *this <= fraction(rhs);
}

bool fraction::operator<=(const long long int& rhs) const
{
	return *this <= fraction(rhs);
}

bool fraction::operator<=(const float& rhs) const
{
	return *this <= fraction(rhs);
}


bool fraction::operator>=(const long double& rhs) const
{
		return *this >= fraction(rhs);

}

bool fraction::operator>=(const int& rhs) const
{
	return *this >= fraction(rhs);
}

bool fraction::operator>=(const long long int& rhs) const
{
	return *this >= fraction(rhs);

}

bool fraction::operator>=(const float& rhs) const
{
	return *this >= fraction(rhs);
}

fraction fraction::operator+(const long double& rhs) const
{
	return *this + fraction(rhs);
}

fraction fraction::operator+(const int& rhs) const
{
	return *this + fraction(rhs);

}

fraction fraction::operator+(const long long int& rhs) const
{
	return *this + fraction(rhs);
}

fraction fraction::operator+(const float& rhs) const
{
	return *this + fraction(rhs);
}

fraction fraction::operator-(const long double& rhs) const
{
	return *this - fraction(rhs);
}

fraction fraction::operator-(const int& rhs) const
{
	return *this - fraction(rhs);
}

fraction fraction::operator-(const long long int& rhs) const
{
	return *this - fraction(rhs);

}

fraction fraction::operator-(const float& rhs) const
{
	return *this - fraction(rhs);
}

fraction fraction::operator*(const long double& rhs) const
{
	return *this * fraction(rhs);
}

fraction fraction::operator*(const int& rhs) const
{
	return *this * fraction(rhs);
}

fraction fraction::operator*(const long long int& rhs) const
{
	return *this * fraction(rhs);
}

fraction fraction::operator*(const float& rhs) const
{
	return *this * fraction(rhs);
}

fraction fraction::operator/(const long double& rhs) const
{
	return *this / fraction(rhs);
}

fraction fraction::operator/(const int& rhs) const
{
	return *this / fraction(rhs);
}

fraction fraction::operator/(const long long int& rhs) const
{
	return *this / fraction(rhs);
}

fraction fraction::operator/(const float& rhs) const
{
	return *this / fraction(rhs);
}
