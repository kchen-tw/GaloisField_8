#include <iostream>
#include <vector>

using namespace std;

class GaloisField {
private:
	const int size = 8; // GF(2^3)中的元素數量
	std::vector<int> exp_table; // 指數表
	std::vector<int> log_table; // 對數表

public:
	// 建構子
	GaloisField() {
		// 如果未初始化，則計算指數表和對數表
		if (exp_table.empty()) {
			exp_table.resize(size);
			exp_table[0] = 1;
			for (int i = 1; i < size - 1; ++i) {
				int temp = exp_table[i-1] << 1;  // g(i) = g(i-1) * g
				if (temp & size)
					temp ^= 0b1011; // 假設原始多項式為 x^3 + x^1 + 1
				exp_table[i] = temp;
			}
		}
		if (log_table.empty()) {
			log_table.resize(size);
			for (int i = 0; i < size - 1; ++i) {
				log_table[exp_table[i]] = i;
			}
		}

	}

	// 在Galois Field中的加法
	int add(int a, int b) {
		return a ^ b;
	}

	// 在Galois Field中的減法
	int subtract(int a, int b) {
		return a ^ b;
	}

	// 在Galois Field中的乘法
	int multiply(int a, int b) {
		if (a == 0 || b == 0) {
			return 0;
		}
		return exp_table[(log_table[a] + log_table[b]) % 7];
	}

	// 在Galois Field中的除法
	int divide(int a, int b) {
		int result_log = (log_table[a] - log_table[b] + 7) % 7;
		return exp_table[result_log];
	}
};


int main() {


	GaloisField gf;

	//int a = 4; // 範例元素 a
	//int b = 5; // 範例元素 b
	//int sum = gf.add(a, b);
	//int difference = gf.subtract(a, b);
	//int product = gf.multiply(a, b);
	//int quotient = gf.divide(a, b);

	//cout << "a + b = " << sum << endl;
	//cout << "a - b = " << difference << endl;
	//cout << "a * b = " << product << endl;
	//cout << "a / b = " << quotient << endl;
	//cout << "7 / 5 = " << gf.divide(7, 5) << endl;

	// 加法表
	cout << "加法表：" << endl;
	cout << "+ ";
	for (int i = 0; i < 8; ++i) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; ++i) {
		cout << i << " ";
		for (int j = 0; j < 8; ++j) {
			cout << gf.add(i, j) << " ";
		}
		cout << endl;
	}

	// 乘法表
	cout << "\n乘法表：" << endl;
	cout << "* ";
	for (int i = 0; i < 8; ++i) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; ++i) {
		cout << i << " ";
		for (int j = 0; j < 8; ++j) {
			cout << gf.multiply(i, j) << " ";
		}
		cout << endl;
	}

	return 0;
}
