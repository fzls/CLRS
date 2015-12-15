/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 fibonacci.cpp
* @version:
* @Time:
* @Description: using divide and conquer technique to implement fibonacci function with O(log(N)) complexity. (two method , one using float multiplication with the loss of precision, and the other one with 2X2 matrix multiplication without loss of precision.);
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;
const double Golden = pow(5, 0.5);
int fib(int n);

int fib_dac(int n);
double power(double x, int n);

int fib_dac_with_matrix(int n);
vector<int> powerMatrix(vector<int>& matrix, int n);
vector<int> multipy(vector<int>& left, vector<int>& right);


int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	clock_t _time = clock();
	default_random_engine _e(_time);
	int temp;

	for (int i = 0; i < 20; i++) {
		temp =  10 + _e() % 30;
		cout <<  temp << "\t:" << fib(temp) << "\t"  << fib_dac(temp) << "\t" << fib_dac_with_matrix(temp) << endl;
	}


	cout << endl;
	system("pause");
	return 0;
}

int fib(int n) {
	int last = 1;
	int current = 1;
	if (n == 1 || n == 2)
		return 1;
	else {
		for (int i = 3; i <= n; ++i) {
			current += last;
			last = current - last;
		}
		return current;
	}
}

int fib_dac(int n) {
	return static_cast<int>((power((1 + Golden) / 2, n) - power((1 - Golden) / 2, n) ) / Golden);
	// return static_cast<int>(power((1 + Golden) / 2, n ) / Golden);
}
double power(double x, int n) {
	if (n == 0)
		return 1;
	else if (n % 2 == 0) {
		double result = power(x, n / 2);
		return result * result;
	}
	else {
		double result = power(x, (n - 1) / 2);
		return result * result * x;
	}
}

int fib_dac_with_matrix(int n) {
	vector<int> Base{1, 1, 1, 0,};
	return powerMatrix(Base, n)[1];
}
vector<int> powerMatrix(vector<int>& matrix, int n) {
	if (n == 0) {
		vector<int> temp{1, 0, 0, 1};
		return temp;
	}
	else if (n % 2 == 0) {
		vector<int> temp = powerMatrix(matrix, n / 2);
		return multipy(temp, temp);
	}
	else {
		vector<int> temp = powerMatrix(matrix, (n - 1) / 2);
		temp = multipy(temp, temp);
		return multipy(temp, matrix);
	}
}


vector<int> multipy(vector<int>& left, vector<int>& right) {
	vector<int> result(4, 0);
	result[0] = left[0] * right[0] + left[1] * right[2];
	result[1] = left[0] * right[1] + left[1] * right[3];
	result[2] = left[2] * right[0] + left[3] * right[2];
	result[3] = left[2] * right[1] + left[3] * right[3];
	return result;
}
