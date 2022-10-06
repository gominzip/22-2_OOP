#include <iostream>
#include "big_integer.h"
using namespace std;


const char* get_boolean_string(bool value) {
	if (value) {
		return "True";
	}
	else {
		return "False";
	}
}

void test_big_integer() {
	BigInteger big_integer;

	// Constructor test
	cout << "[Constructor Test]" << endl;
	cout << "Original BigInteger (integer: 1234567890): " << BigInteger(1234567890) << endl;
	cout << "Original BigInteger (longlong: 123456789012345): " << BigInteger(123456789012345) << endl;
	cout << "Original BigInteger (string: 12345678901234567890): " << BigInteger(string("12345678901234567890")) << std::endl;
	cout << "Original BigInteger (integer: -1234567890): " << BigInteger(-1234567890) << endl;
	cout << "Original BigInteger (longlong: -123456789012345): " << BigInteger(-123456789012345) << endl;
	cout << "Original BigInteger (string: -12345678901234567890): " << BigInteger(string("-12345678901234567890")) << std::endl;

	// I&O test
	cout << endl << "[I/O Test]" << endl;
	cout << "Enter a value: ";
	cin >> big_integer;
	cout << "Given value: " << big_integer << endl;

	// Comparison test
	cout << endl << "[Comparison Test]" << endl;
	cout << "(12345678901234567899 > 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") > BigInteger("12345678901234567890")) << endl;
	cout << "(12345678901234567899 < 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") < BigInteger("12345678901234567890")) << endl;
	cout << "(12345678901234567899 == 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") == BigInteger("12345678901234567890")) << endl;
	cout << "(12345678901234567890 == 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567890") == BigInteger("12345678901234567890")) << endl;
	cout << "(-12345678901234567899 > 12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") > BigInteger("12345678901234567890")) << endl;
	cout << "(12345678901234567899 > -12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") > BigInteger("-12345678901234567890")) << endl;
	cout << "(-12345678901234567899 > -12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") > BigInteger("-12345678901234567890")) << endl;
	cout << "(-12345678901234567899 < -12345678901234567890) True -> " << get_boolean_string(BigInteger("-12345678901234567899") < BigInteger("-12345678901234567890")) << endl;

	// Add test
	cout << endl << "[Add Test]" << endl;
	cout << "1234567890 + 1234567899 = 2469135789 -> " << BigInteger(1234567899) + BigInteger(1234567890) << endl;
	cout << "-1234567890 + -1234567899 = -246913578 -> " << BigInteger(-1234567899) + BigInteger(-1234567890) << endl;  // 음 + 음
	cout << "1234567899 + 1234567890 = 2469135789 -> " << BigInteger("1234567890") + BigInteger("1234567899") << endl;  // 문자열 넣었을 때 테스트
	cout << "9999 + -9999 = 0 -> " << BigInteger(-9999) + BigInteger(9999) << endl;  // 음 + 양 (절댓값 같음)
	cout << "123456 - 23967 = 99489 -> " << BigInteger(123456) + BigInteger(-23967) << endl;  // 음 + 양 > 0
	cout << "-123456 + 23967 = -99489 -> " << BigInteger(-123456) + BigInteger(23967) << endl;  // 음 + 양 < 0

	// Subtract test
	cout << endl << "[Subtract Test]" << endl;
	cout << "1234567899 - 1234567890 = 9 -> " << BigInteger(1234567899) - BigInteger(1234567890) << endl;
	cout << "1234567890 - 1234567899 = -9 -> " << BigInteger(1234567890) - BigInteger(1234567899) << endl;
	cout << "1234567899 - 1234567890 = 9 -> " << BigInteger("1234567899") - BigInteger("1234567890") << endl;
	cout << "1234567899 - -1234567890 = 2469135789 -> " << BigInteger(1234567899) - BigInteger(-1234567890) << endl;  // 양 - 음
	cout << "-1234567890 - 1234567899 = -2469135789 -> " << BigInteger(-1234567890) - BigInteger(1234567899) << endl;  // 음 - 양
	cout << "123456 - 23967 = 99489 -> " << BigInteger(123456) - BigInteger(23967) << endl;  // 양 - 양
	cout << "-123456 - -23967 = -99489 -> " << BigInteger(-123456) - BigInteger(-23967) << endl;  // 음 - 음

	// Multiply test (Optional)
	cout << endl << "[Multiply Test]" << endl;
	cout << "12345 * 67890 = 838102050 -> " << BigInteger(12345) * BigInteger(67890) << endl;
	cout << "-12345 * 67890 = -838102050 -> " << BigInteger(-12345) * BigInteger(67890) << endl;
	cout << "-12345 * -67890 = 838102050 -> " << BigInteger(-12345) * BigInteger(-67890) << endl;

	// Divide test (Optional)
	cout << endl << "[Divide Test]" << endl;
	cout << "67890 / 12345 = 5 -> " << BigInteger(67890) / BigInteger(12345) << endl;
	cout << "-67890 / 12345 = -5 -> " << BigInteger(-67890) / BigInteger(12345) << endl;
	cout << "-67890 / -12345 = 5 -> " << BigInteger(-67890) / BigInteger(-12345) << endl;

	// Remainder test (Optional)
	cout << endl << "[Remainder Test]" << endl;
	cout << "67890 % 12345 = 6156 -> " << BigInteger(67890) % BigInteger(12345) << endl;
	cout << "-67890 % 12345 = 6180 -> " << BigInteger(-67890) % BigInteger(12345) << endl;
	cout << "-67890 % -12345 = -6165 -> " << BigInteger(-67890) % BigInteger(-12345) << endl;
}

int main(int argc, char* argv[]) {
	// Test BigInteger class
	test_big_integer();

	return 0;
}