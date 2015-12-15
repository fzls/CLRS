/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 countingSort.cpp
* @version:
* @Time: 		 2015-11-13 22:07:38
* @Description:  clrs 8.2 counting sort
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
#include <climits>

using namespace std;

void countingSort(vector<int> &data);
int findMax(const vector<int> &data);

void radixSort(vector<int> &data);
void countingSort(vector<int> &data, int factor, int base);
void bitRadixSort(vector<int> &data);

void printVector(const vector<int>& data) ;

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	clock_t _time = clock();
	default_random_engine _e(_time);
	vector<int> data;
	for (int length = 35 + _e() % 10; length > 0; --length)
		data.push_back(_e() % 500);
	vector<int> test(data);
	printVector(data);
	bitRadixSort(data);
	countingSort(test);
	printVector(data);
	printVector(test);
	cout << endl;
	system("pause");
	return 0;
}

void radixSort(vector<int> &data) {
	int max = findMax(data), base = 10;
	int digits;
	for (digits = 1; max /= base; ++digits)
		;
	for (int factor = 1; digits > 0; --digits, factor *= base)
		countingSort(data, factor, base);
}

void bitRadixSort(vector<int> &data) {
	int r = 8, b = 32, base = 1 << r;
	int digits = (b + r - 1) / r;
	for (int factor = 1; digits > 0; --digits, factor *= base)
		countingSort(data, factor, base);
}


void countingSort(vector<int> &data, int factor, int base) {
	const int _length = static_cast<int>(data.size());
	vector<int> C(base, 0), temp(data);
	for (int val : data)
		C[val / factor % base]++;
	for (int i = 1; i < base; ++i)
		C[i] += C[i - 1];
	for (int i = _length - 1; i >= 0; --i)
		data[-1 + C[temp[i] / factor % base]--] = temp[i];
}

void printVector(const vector<int>& data) {
	cout << "-------start of print vector-------" << endl;
	for (auto k : data)
		cout << k << "\t";
	cout << endl;
	cout << "-------end of print vector-------" << endl << endl;
}

void countingSort(vector<int> &data) {
	const int _length = static_cast<int>(data.size());
	//find the max item and then initialize the Count vector and the temp vector
	int k = findMax(data);
	vector<int> C(k + 1, 0), temp(data);
	//update the Counters
	for (int val : data)
		C[val]++;
	//preprocess
	for (int i = 1; i <= k; ++i)
		C[i] += C[i - 1];
	//put the element into the corresponding position
	for (int i = _length - 1; i >= 0; --i)
		data[-1 + C[temp[i]]--] = temp[i];
	//should minus 1 because C[value] means there are C[value] numbers less or equal to value, so value should be the C[value]th item, cause the index start from 0, so its index is C[value]-1
}
int findMax(const vector<int> &data) {
	int max = INT_MIN;
	for (auto k : data)
		if (k > max)
			max = k;
	return max;
}
