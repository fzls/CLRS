/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 permuteBySorting.cpp
* @version:
* @Time: 		 2015-11-07 22:59:01
* @Description:  introduction to the algorithms: page 125
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


using namespace std;

void sortByPriority(vector<int>& permutation, vector<int>& priorities);
void print(const vector<int>& data);
void randomizeInPlace(vector<int>& permutation);

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	vector<int> permutation, priorities ;
	clock_t _time = clock();
	default_random_engine _e(_time);
	int t = 10 + _e() % 10;
	for (int i = 1; i <= t; ++i) {
		permutation.push_back(i);
		priorities.push_back(_e() % 100);
	}
	print(permutation);
	// print(priorities);
	// sortByPriority(permutation, priorities);
	randomizeInPlace(permutation);
	print(permutation);
	// print(priorities);

	cout << endl;
	system("pause");
	return 0;
}

void randomizeInPlace(vector<int>& permutation) {
	clock_t _time = clock();
	default_random_engine _e(_time);
	const int _length = static_cast<int>(permutation.size());
	for (int i = 0; i < _length; ++i)
		swap(permutation[i], permutation[i + _e() % (_length - i)]);
}

void sortByPriority(vector<int>& permutation, vector<int>& priorities) {
	const int n = static_cast<int>(permutation.size());
	for (int i = 1, j; i < n; ++i) {
		int keyPri = priorities[i];
		int keyPer = permutation[i];
		for (j = i - 1; j >= 0 && priorities[j] > keyPri; --j) {
			priorities[j + 1] = priorities[j];
			permutation[j + 1] = permutation[j];
		}
		priorities[j + 1] = keyPri;
		permutation[j + 1] = keyPer;
	}
}
void print(const vector<int>& data) {
	for (auto k : data)
		cout << k << "\t";
	cout << endl;
}
