/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 tests.cpp
* @version:
* @Time:
* @Description:
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

void printVector(const vector<int>& data) ;


int main() {
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	// vector<int> test(11, -1) , data{10, 22, 31, 4, 15, 28, 17, 88, 59,} ;
	// for (int i = 0; i < 9; ++i) {
	// 	for (int j = 0; j < 11; j++) {
	// 		// int hash = ( data[i] + 1 + (data[i] % 10)) % 11;
	// 		int hash = (data[i] + j) % 11;
	// 		cout << i << " " << j << " " << hash << endl;
	// 		if (test[hash] == -1) {
	// 			test[hash] = data[i];
	// 			break;
	// 		}
	// 	}
	// }
	// printVector(test);
	// printVector(data);
	for (auto i = 0.01; i < 1; i += 0.01)
		cout << i << "\t" << (1 - i) / i * log(1 / ( 1 - i)) - 0.5 << endl;

	cout << endl;
	system("pause");
	return 0;
}

void printVector(const vector<int>& data) {
	cout << "-------start of print vector-------" << endl;
	int count = 0;
	for (auto k : data) {
		cout << k ;
		if (++count == 5) {
			count -= 5;
			cout << endl;
		}
		else
			cout << "\t";
	}
	cout << endl;
	cout << "-------end of print vector-------" << endl << endl;
}
