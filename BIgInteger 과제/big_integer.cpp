#define _CRT_SECURE_NO_WARNINGS
#include "big_integer.h"
#include <iostream>
#include <algorithm>


// Identifier
const std::string BigInteger::name = "BigInteger";

// Method
void BigInteger::initialize_properties() {
	this->sign = true;
	this->length = 0;
	this->capacity = 0;
	this->value_string = new char[this->initial_capacity]();
	if (this->value_string != NULL) {
		this->capacity = this->initial_capacity;
		this->length = 0;
	}
}

void BigInteger::doubling_capacity() {
	int new_capacity = this->capacity * 2;
	char* new_value_string = new char[new_capacity]();
	if (new_value_string == NULL) return;

	memcpy(new_value_string, this->value_string, this->length);
	delete(this->value_string);

	this->capacity = new_capacity;
	this->value_string = new_value_string;
}

int BigInteger::get_ll_length(long long value) {
	while (true) {
		if (value == 0) {
			this->length = 1;
			break;
		}
		if (value < 0) {
			value = -value;
		}
		this->length += 1;
		value = value / 10;
		if (value < 10) {
			this->length += 1;
			break;
		}
	}
	return length;
}

BigInteger::COMPARE_RESULT BigInteger::compare_absolute_value(const BigInteger& big_integer) const {
	int start_index = 0;

	int length = this->length;
	int given_length = big_integer.length;

	if (length > given_length) {
		return BigInteger::COMPARE_RESULT::COMPARE_LARGER;
	}
	else if (length < given_length) {
		return BigInteger::COMPARE_RESULT::COMPARE_SMALLER;
	}
	else {
		for (int place_index = 0; place_index < length; place_index++) {
			if (this->value_string[place_index + start_index] > big_integer.value_string[place_index + start_index]) {
				return BigInteger::COMPARE_RESULT::COMPARE_LARGER;
			}
			else if (this->value_string[place_index + start_index] < big_integer.value_string[place_index + start_index]) {
				return BigInteger::COMPARE_RESULT::COMPARE_SMALLER;
			}
		}
	}
	return BigInteger::COMPARE_RESULT::COMPARE_EQUAL;
}

// Method (Interface)
BigInteger::BigInteger() {
	/* Should be implemented */
	initialize_properties();
}

BigInteger::BigInteger(int value) {
	this->initialize_properties();
	int temp = value;

	this->sign = (value >= 0) ? true : false;  // ��ȣ �Ǻ�


	/* value�� length ���ϱ� */
	while (true) {
		// ���� 0�̸� ���� 1
		if (value == 0) {  
			this->length = 1;
			break;
		}
		// ���� ������ ����� �ٲ㼭 ������ ���̸� ������ �� �ֵ���
		if (value < 0) {  
			value = -value;
		}

		this->length += 1;  // ���� +1
		value = value / 10;  // 10���� ������ ���� �ڸ����� �ִ��� Ȯ��

		if (value < 10) {  // ���� �ڸ����� ������
			this->length += 1;  // ���������� �߰��ϰ� �ݺ��� ����
			break;
		}
	}
	length++;  //  null���� �� ����
	value = temp;  // ���� value������ �ٽ� value ����

	this->null_length = length;  // length�� �̹� null���ڱ��� ���Խ��ױ� ������ �׳� length������ ����
	
	while (capacity < length)  // ���̿� �´� ����� capacity Ȯ��
		doubling_capacity();

	if (value < 0)  // ���ڿ��� ��ȯ ����
		value *= -1;  // ������ �������� �ٲ��ֱ�

	snprintf(value_string, length, "%d", value);  // ���ڿ��� ��ȯ
}

BigInteger::BigInteger(long long value) {
	this->initialize_properties();

	this->sign = (value >= 0) ? true : false;  // ��ȣ �Ǻ�
	this->length = get_ll_length(value);  // �Լ��� value�� ���̸� ����
	length++;  // null���� �� ����

	while (capacity < length)  // ���̿� �´� ����� capacity Ȯ��
		doubling_capacity();
	
	this->null_length = length;  // length�� �̹� null���ڱ��� ���Խ��ױ� ������ �׳� length������ ����

	if (value < 0)  // ���ڿ��� ��ȯ ����
		value *= -1;  // ������ �������� �ٲ��ֱ�

	snprintf(value_string, length, "%lld", value);  // ���ڿ��� ��ȯ
}

BigInteger::BigInteger(std::string value) {
	this->initialize_properties();

	if (value[0] == '-')
		this->sign = false;
	else sign = true;
	
	length = value.size();  // ���ڿ� ���� ����

	if (value[0] == '-')
		length--;  // -�� ���ڿ����� ������ ���̹Ƿ� ������ ���� -1

	while (capacity < length)  // ���̿� �´� ����� capacity Ȯ��
		doubling_capacity();

	if (value[0] == '-') {
		value.erase(value.begin());  // - ����
	}
	
	this->null_length = length+1;
	memset(value_string, 0, length*sizeof(char));
	strncpy(value_string, value.c_str(), length);  // null_length�� �����ϰ� �� ����
	// ���ڰ� ����ִ� ������ ���̸� �ޱ� ������ string�� length�� �ٸ� �����ڿ� �ٸ��� null�� ���̰� ���ԵǾ����� �ʴ�.
	// �׷��� ���� null_length�� �̿��� ����ϰ� ��
}

BigInteger::BigInteger(const BigInteger& big_integer) {
	this->initialize_properties();

	char* new_value_string = new char[big_integer.capacity]();
	if (new_value_string != NULL) {
		if (this->value_string != NULL) {
			delete(this->value_string);
			this->sign = true;
			this->length = 0;
			this->capacity = 0;
		}

		this->value_string = new_value_string;
		memcpy(this->value_string, big_integer.get_string(), big_integer.capacity);
		this->sign = big_integer.sign;
		this->length = big_integer.length;
		this->capacity = big_integer.capacity;
	}
}

BigInteger::~BigInteger() {
	if (this->value_string != NULL) {
		delete(this->value_string);
		this->sign = true;
		this->length = 0;
		this->capacity = 0;
	}
}

std::string BigInteger::get_name() const {
	return name;
}

char* BigInteger::get_string() const {
	return this->value_string;
}

BigInteger& BigInteger::operator = (const BigInteger& big_integer) {
	char* new_value_string = new char[big_integer.capacity]();
	if (new_value_string != NULL) {
		if (this->value_string != NULL) {
			delete(this->value_string);
			this->sign = true;
			this->length = 0;
			this->capacity = 0;
		}

		this->value_string = new_value_string;
		memcpy(this->value_string, big_integer.get_string(), big_integer.capacity);
		this->sign = big_integer.sign;
		this->length = big_integer.length;
		this->capacity = big_integer.capacity;
	}

	return *this;
}

bool BigInteger::operator == (const BigInteger& big_integer) const {
	if (this->length != big_integer.length) {
		return false;
	}

	if (this->sign != big_integer.sign) {
		return false;
	}

	for (unsigned int place_index = 0; place_index < big_integer.length; place_index++) {
		if (this->value_string[place_index] != big_integer.value_string[place_index]) {
			return false;
		}
	}

	return true;
}

bool BigInteger::operator > (const BigInteger& big_integer) const {
	BigInteger::COMPARE_RESULT compare_result;

	// If sign is the same
	if (this->sign == big_integer.sign) {
		// Compare two absolute values
		compare_result = this->compare_absolute_value(big_integer);

		// Compare two positive values
		if (this->sign) {
			if (compare_result == this->COMPARE_LARGER) {
				return true;
			}
			else {
				return false;
			}
		}
		// Compare two negative values
		else {
			if (compare_result == this->COMPARE_SMALLER) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	// No need to compare
	else {
		if (this->sign) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool BigInteger::operator < (const BigInteger& big_integer) const {
	return (big_integer > *this);
}

bool BigInteger::operator >= (const BigInteger& big_integer) const {
	return !(big_integer > *this);
}

bool BigInteger::operator <= (const BigInteger& big_integer) const {
	return !(big_integer < *this);
}

BigInteger BigInteger::operator + (const BigInteger& big_integer) const {
	BigInteger result;
	std::string s1;  // this�� ����
	std::string s2;  // big_integer�� ����

	// char*�� string���� ��ȯ�� ����
	// �̶� ���� ��ȣ�� �� ��. �� s1�� s2�� ����
	for (int i = 0; i < this->null_length - 1; i++)
		s1 += std::to_string((int)this->value_string[i] - '0');  // �ƽ�Ű�ڵ����� ����ؼ� '0'=48�� ���༭ ����

	for (int i = 0; i < big_integer.null_length - 1; i++)  // ���ڿ��� ��ȯ
		s2 += std::to_string((int)big_integer.value_string[i] - '0');

	// �� ������ sign�� ���� ��
	if (this->sign == big_integer.sign) {

		std::string s_result(std::max(s1.size(), s2.size()), '0');  // ������� �ִ� ���̷�
		bool carry = false;  // ���� �ڸ����� +�� ���� �ִ����� ���� ����

		for (int i = 0; i < s_result.size(); i++) {  // ���������� ���ϱ�
			int temp = carry;  // �ø� ���� �ִٸ� temp�� (true)1 �߰���ä�� ����
			carry = false;  // �ٽ� �ٸ� �ڸ��� ���� ������ �� false�� �ʱ�ȭ

			if (i < s1.size()) {
				temp += s1[s1.size() - 1 - i] - '0';  // -1�� �迭�� 0���� �����ؼ�, �ƽ�Ű�ڵ����� ����� -'0'
			}

			if (i < s2.size()) {
				temp += s2[s2.size() - 1 - i] - '0';
			}

			if (temp >= 10) {
				carry = true;  // �ø� �� ����
				temp -= 10;  // 10�� �� �������� ����
			}
			s_result[s_result.size() - 1 - i] = temp + '0';  // '0'�� ���� �ƽ�Ű�ڵ尪���� �����Ѵ�.
		}
		// for���� ������ carry�� true��� ���ڸ� �� �÷������
		if (carry)
			s_result.insert(s_result.begin(), '1');  // �̷��� �����ϸ� �������� �ذ�

		if (this->sign == false)  // �����϶���
			s_result.insert(s_result.begin(), '-');  // �Ǿտ� '-' �ٿ��ֱ�

		result = BigInteger(s_result);  // ���ڿ��� �ٽ� Biginteger�� �ٲ㼭 ����
	}


	// �� ������ sign�� �ٸ� ��
	// ������ ū ������ ���� ���� ����
	// �� �Ŀ� ��ȣ �Ǵ�
	if (this->sign != big_integer.sign) {
		bool s1_sign = this->sign;

		if (BigInteger(s1) == BigInteger(s2))  // ������ ������
			result = BigInteger(0);  // 0��ȯ

		else 
		{   // ������ ū�� s1����
			if (BigInteger(s1) < BigInteger(s2)) {    // s2�� ������ �� ũ��
				std::string swap; 
				swap = s1;
				s1 = s2;
				s2 = swap;
				s1_sign = big_integer.sign;
				// s1�� s2�� �ٲ��ش�, sign�� ���� s2�� sign���� ����
			}

			std::string s_result(s1.size(), '0');  // s1�� ������ ������ ũ�Ƿ� s1ũ��� ����
			int carry = 0;  // ���� �ڸ����� -�� ���� �ִ����� ���� ����
			int end = -1;  // s2�� ����� �ݺ��� ������ ���� �˸� ����

			for (int i = 0; i < s_result.size(); i++) {  // ���������� ����
				int temp = carry;  // ���� ���� �ִٸ� temp�� -1 �߰���ä�� ����
				carry = 0;  // �ٽ� �ٸ� �ڸ��� ���� ������ �� false�� �ʱ�ȭ

				if (i < s1.size()) {
					temp += s1[s1.size() - 1 - i] - '0';  // s1���� s2�� �����ϹǷ� s1�� temp�� ���ϰ�
				}

				if (i < s2.size()) {
					temp -= s2[s2.size() - 1 - i] - '0';  // s2�� temp���� ����

					if (i == s2.size())  // s2�� ������ �ݺ��� ������
						end++;  // end=0
				}

				if (end < 1) {
					if (temp < 0) {
						carry = -1;  // ���� �� ����
						temp += 10;  // 10���ؼ� ����
					}
					if(end==0)
						end++;  // end=1�� ���̻� temp+=10�� ���� ����
				}
				s_result[s_result.size() - 1 - i] = temp + '0';  // '0'�� ���� �ƽ�Ű�ڵ尪���� �����Ѵ�.
			}

			// �տ� ���� 0�� ����� ����
			int non_zero_index = s_result.size();
			for (int i = 0; i < s_result.size(); i++)
			{
				if (s_result[i] != '0')
				{
					non_zero_index = i;  // 0�� �� ������ ù ���� ����
					break;
				}
			}

			// ���ʷ� 0�� �ƴ� �ڸ������� ���ڵ��� ��ȯ
			s_result = s_result.substr(non_zero_index);

			// ��ȣ ���� ����
			if (s1_sign == false)  // �����϶���
				s_result.insert(s_result.begin(), '-');  // �Ǿտ� '-' �ٿ��ֱ�

			result = BigInteger(s_result); // ���ڿ��� �ٽ� Biginteger�� �ٲ㼭 ����
		}
	}

	return result; 
}

BigInteger BigInteger::operator - (const BigInteger& big_integer) const {
	BigInteger result;
	std::string s1;  // this�� ����
	std::string s2;  // big_integer�� ����

	// char*�� string���� ��ȯ�� ����
	// �̶� ���� ��ȣ�� �� ���°� ����
	for (int i = 0; i < this->null_length - 1; i++)
		s1 += std::to_string((int)this->value_string[i] - '0');  // �ƽ�Ű�ڵ����� ����ؼ� '0'=48�� ���༭ ����
	for (int i = 0; i < big_integer.null_length - 1; i++)  // ���ڿ��� ��ȯ
		s2 += std::to_string((int)big_integer.value_string[i] - '0');

	if ((this->sign==true)&&(big_integer.sign == false)) {  // x-(-y) = x+y �� �̹Ƿ� ���񰪳��� �����ֱ�
		result = BigInteger(s1) + BigInteger(s2);
	}

	else if ((this->sign == false) && (big_integer.sign == true)) {  // -x-y = (-x)+(-y)�̹Ƿ� ���ڿ��� - �־��༭ ����
		s1.insert(s1.begin(), '-');
		s2.insert(s2.begin(), '-');
		result = BigInteger(s1) + BigInteger(s2);
	}

	else if ((this->sign == true) && (big_integer.sign == true)) {
		s2.insert(s2.begin(), '-');
		result = BigInteger(s1) + BigInteger(s2);
	}
	
	else if ((this->sign == false) && (big_integer.sign == false)) {
		s1.insert(s1.begin(), '-');
		result = BigInteger(s1) + BigInteger(s2);
	}

	return  result;
}

BigInteger BigInteger::operator * (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

BigInteger BigInteger::operator / (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

BigInteger BigInteger::operator % (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

std::ostream& operator << (std::ostream& out, const BigInteger& big_integer) {
	// Print minus sign
	if (!big_integer.sign) {
		out << std::string("-");
	}

	// Print values
	out << std::string(big_integer.get_string(), big_integer.length);
	return out;
}

std::istream& operator >> (std::istream& in, BigInteger& big_integer) {
	std::string input_string;
	in >> input_string;

	big_integer = BigInteger(input_string);

	return in;
}