#pragma once
#include <string>
#include <istream>
#include <ostream>


class BigInteger
{
private:
	// Identifier
	static const std::string name;

	// Static Property
	static const int initial_capacity = 10;

	// Property
	bool sign;
	unsigned int length;
	unsigned int capacity;
	char* value_string;
	unsigned int null_length;  // string이 다른 타입이랑 length가 다른 방식으로 저장되어서 연산을 위해 따로 null_length 추가

	// Method
	void initialize_properties();
	void doubling_capacity();
	int get_ll_length(long long value);  // long long 변수의 길이를 계산하는 함수 선언 
	
	enum COMPARE_RESULT {
		COMPARE_LARGER,
		COMPARE_EQUAL,
		COMPARE_SMALLER,
	};
	COMPARE_RESULT compare_absolute_value(const BigInteger& big_integer) const;

public:
	// Method (Interface)
	BigInteger();
	BigInteger(int value);
	BigInteger(long long value);
	BigInteger(std::string value);
	BigInteger(const BigInteger& big_integer);
	~BigInteger();

	std::string get_name() const;
	char* get_string() const;

	BigInteger& operator = (const BigInteger& big_integer);
	bool operator == (const BigInteger& big_integer) const;
	bool operator > (const BigInteger& big_integer) const;
	bool operator < (const BigInteger& big_integer) const;
	bool operator >= (const BigInteger& big_integer) const;
	bool operator <= (const BigInteger& big_integer) const;

	BigInteger operator + (const BigInteger& big_integer) const;
	BigInteger operator - (const BigInteger& big_integer) const;
	BigInteger operator * (const BigInteger& big_integer) const;
	BigInteger operator / (const BigInteger& big_integer) const;
	BigInteger operator % (const BigInteger& big_integer) const;

	friend std::ostream& operator << (std::ostream& out, const BigInteger& big_integer);
	friend std::istream& operator >> (std::istream& out, BigInteger& big_integer);
};