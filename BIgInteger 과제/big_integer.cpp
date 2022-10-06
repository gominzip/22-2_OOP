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

	this->sign = (value >= 0) ? true : false;  // 부호 판별


	/* value의 length 구하기 */
	while (true) {
		// 값이 0이면 길이 1
		if (value == 0) {  
			this->length = 1;
			break;
		}
		// 값이 음수면 양수로 바꿔서 문자의 길이만 측정할 수 있도록
		if (value < 0) {  
			value = -value;
		}

		this->length += 1;  // 길이 +1
		value = value / 10;  // 10으로 나눠서 다음 자릿수가 있는지 확인

		if (value < 10) {  // 다음 자릿수가 없으면
			this->length += 1;  // 마지막으로 추가하고 반복문 종료
			break;
		}
	}
	length++;  //  null문자 들어갈 공간
	value = temp;  // 기존 value값으로 다시 value 저장

	this->null_length = length;  // length에 이미 null문자까지 포함시켰기 때문에 그냥 length값으로 저장
	
	while (capacity < length)  // 길이에 맞는 충분한 capacity 확보
		doubling_capacity();

	if (value < 0)  // 문자열로 변환 전에
		value *= -1;  // 음수는 절댓값으로 바꿔주기

	snprintf(value_string, length, "%d", value);  // 문자열로 변환
}

BigInteger::BigInteger(long long value) {
	this->initialize_properties();

	this->sign = (value >= 0) ? true : false;  // 부호 판별
	this->length = get_ll_length(value);  // 함수로 value의 길이를 얻음
	length++;  // null문자 들어갈 공간

	while (capacity < length)  // 길이에 맞는 충분한 capacity 확보
		doubling_capacity();
	
	this->null_length = length;  // length에 이미 null문자까지 포함시켰기 때문에 그냥 length값으로 저장

	if (value < 0)  // 문자열로 변환 전에
		value *= -1;  // 음수는 절댓값으로 바꿔주기

	snprintf(value_string, length, "%lld", value);  // 문자열로 변환
}

BigInteger::BigInteger(std::string value) {
	this->initialize_properties();

	if (value[0] == '-')
		this->sign = false;
	else sign = true;
	
	length = value.size();  // 문자열 길이 측정

	if (value[0] == '-')
		length--;  // -는 문자열에서 지워질 것이므로 음수면 길이 -1

	while (capacity < length)  // 길이에 맞는 충분한 capacity 확보
		doubling_capacity();

	if (value[0] == '-') {
		value.erase(value.begin());  // - 삭제
	}
	
	this->null_length = length+1;
	memset(value_string, 0, length*sizeof(char));
	strncpy(value_string, value.c_str(), length);  // null_length를 선언하게 된 원인
	// 문자가 들어있는 공간의 길이만 받기 때문에 string의 length는 다른 생성자와 다르게 null의 길이가 포함되어있지 않다.
	// 그래서 따로 null_length를 이용해 계산하게 됨
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
	std::string s1;  // this를 담음
	std::string s2;  // big_integer를 담음

	// char*를 string으로 변환해 저장
	// 이때 음수 부호는 안 들어감. 즉 s1과 s2는 절댓값
	for (int i = 0; i < this->null_length - 1; i++)
		s1 += std::to_string((int)this->value_string[i] - '0');  // 아스키코드임을 고려해서 '0'=48을 빼줘서 저장

	for (int i = 0; i < big_integer.null_length - 1; i++)  // 문자열로 변환
		s2 += std::to_string((int)big_integer.value_string[i] - '0');

	// 두 정수의 sign이 같을 때
	if (this->sign == big_integer.sign) {

		std::string s_result(std::max(s1.size(), s2.size()), '0');  // 결과값은 최대 길이로
		bool carry = false;  // 다음 자릿수에 +할 것이 있는지에 대한 변수

		for (int i = 0; i < s_result.size(); i++) {  // 끝에서부터 더하기
			int temp = carry;  // 올림 수가 있다면 temp에 (true)1 추가된채로 시작
			carry = false;  // 다시 다른 자릿수 덧셈 시작할 때 false로 초기화

			if (i < s1.size()) {
				temp += s1[s1.size() - 1 - i] - '0';  // -1은 배열이 0부터 시작해서, 아스키코드임을 고려해 -'0'
			}

			if (i < s2.size()) {
				temp += s2[s2.size() - 1 - i] - '0';
			}

			if (temp >= 10) {
				carry = true;  // 올림 수 있음
				temp -= 10;  // 10을 뺀 나머지를 저장
			}
			s_result[s_result.size() - 1 - i] = temp + '0';  // '0'을 더해 아스키코드값으로 저장한다.
		}
		// for문이 끝나고 carry가 true라면 한자리 더 올려줘야함
		if (carry)
			s_result.insert(s_result.begin(), '1');  // 이렇게 접근하면 공간문제 해결

		if (this->sign == false)  // 음수일때는
			s_result.insert(s_result.begin(), '-');  // 맨앞에 '-' 붙여주기

		result = BigInteger(s_result);  // 문자열을 다시 Biginteger로 바꿔서 리턴
	}


	// 두 정수의 sign이 다를 때
	// 절댓값이 큰 수에서 작은 수를 빼고
	// 그 후에 부호 판단
	if (this->sign != big_integer.sign) {
		bool s1_sign = this->sign;

		if (BigInteger(s1) == BigInteger(s2))  // 절댓값이 같으면
			result = BigInteger(0);  // 0반환

		else 
		{   // 절댓값이 큰게 s1으로
			if (BigInteger(s1) < BigInteger(s2)) {    // s2의 절댓값이 더 크면
				std::string swap; 
				swap = s1;
				s1 = s2;
				s2 = swap;
				s1_sign = big_integer.sign;
				// s1과 s2를 바꿔준다, sign도 기존 s2의 sign으로 변경
			}

			std::string s_result(s1.size(), '0');  // s1의 절댓값이 무조건 크므로 s1크기로 정의
			int carry = 0;  // 다음 자릿수에 -할 것이 있는지에 대한 변수
			int end = -1;  // s2의 계산이 반복이 끝나는 것을 알릴 변수

			for (int i = 0; i < s_result.size(); i++) {  // 끝에서부터 뻬기
				int temp = carry;  // 내림 수가 있다면 temp에 -1 추가된채로 시작
				carry = 0;  // 다시 다른 자릿수 뺄셈 시작할 때 false로 초기화

				if (i < s1.size()) {
					temp += s1[s1.size() - 1 - i] - '0';  // s1에서 s2를 빼야하므로 s1은 temp에 더하고
				}

				if (i < s2.size()) {
					temp -= s2[s2.size() - 1 - i] - '0';  // s2는 temp에서 뺀다

					if (i == s2.size())  // s2가 마지막 반복을 끝나면
						end++;  // end=0
				}

				if (end < 1) {
					if (temp < 0) {
						carry = -1;  // 내림 수 있음
						temp += 10;  // 10더해서 저장
					}
					if(end==0)
						end++;  // end=1로 더이상 temp+=10을 하지 않음
				}
				s_result[s_result.size() - 1 - i] = temp + '0';  // '0'을 더해 아스키코드값으로 저장한다.
			}

			// 앞에 남은 0을 지우는 구간
			int non_zero_index = s_result.size();
			for (int i = 0; i < s_result.size(); i++)
			{
				if (s_result[i] != '0')
				{
					non_zero_index = i;  // 0이 안 나오는 첫 구간 저장
					break;
				}
			}

			// 최초로 0이 아닌 자리부터의 숫자들을 반환
			s_result = s_result.substr(non_zero_index);

			// 부호 결정 구간
			if (s1_sign == false)  // 음수일때는
				s_result.insert(s_result.begin(), '-');  // 맨앞에 '-' 붙여주기

			result = BigInteger(s_result); // 문자열을 다시 Biginteger로 바꿔서 리턴
		}
	}

	return result; 
}

BigInteger BigInteger::operator - (const BigInteger& big_integer) const {
	BigInteger result;
	std::string s1;  // this를 담음
	std::string s2;  // big_integer를 담음

	// char*를 string으로 변환해 저장
	// 이때 음수 부호는 안 들어가는거 주의
	for (int i = 0; i < this->null_length - 1; i++)
		s1 += std::to_string((int)this->value_string[i] - '0');  // 아스키코드임을 고려해서 '0'=48을 빼줘서 저장
	for (int i = 0; i < big_integer.null_length - 1; i++)  // 문자열로 변환
		s2 += std::to_string((int)big_integer.value_string[i] - '0');

	if ((this->sign==true)&&(big_integer.sign == false)) {  // x-(-y) = x+y 꼴 이므로 절댓값끼리 더해주기
		result = BigInteger(s1) + BigInteger(s2);
	}

	else if ((this->sign == false) && (big_integer.sign == true)) {  // -x-y = (-x)+(-y)이므로 문자열에 - 넣어줘서 전달
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