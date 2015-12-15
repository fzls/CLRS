/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 quickSort.cpp
* @version:
* @Time: 		 2015-11-10 17:10:38
* @Description:  implementation of the quickSort
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

void prepareData(vector<int>& data) ;
void printVector(const vector<int>& data) ;
void quickSort(vector<int>& data);
void quickSort(vector<int>& data, int left, int right);
int partion(vector<int>&data, int left, int right);

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	vector<int> data;
	prepareData(data);
	printVector(data);


	quickSort(data);
	printVector(data);

	cout << endl;
	system("pause");
	return 0;
}

void quickSort(vector<int>& data) {
	const int _length = static_cast<int>(data.size());
	int maxIndex = 0;
	for (int i = 0; i < _length; ++i)
		if (data[i] > data[maxIndex])
			maxIndex = i;
	swap(data[maxIndex], data[_length - 1]);

	quickSort(data, 0, _length - 2);
}
void quickSort(vector<int>& data, int left, int right) {

	// if (left < right) {
	// 	int pivot = partion(data, left, right);
	// 	quickSort(data, left, pivot - 1);
	// 	quickSort(data, pivot + 1, right);
	// }
	while (left < right) {
		int pivot = partion(data, left, right);
		if (pivot - left < right - pivot) {
			quickSort(data, left, pivot - 1);
			left = pivot + 1;
		}
		else {
			quickSort(data, pivot + 1 , right);
			right = pivot - 1;
		}

	}
}
int partion(vector<int>&data, int left, int right) {
	swap(data[left], data[(left + right) / 2]);
	int pivot = data[left];
	int i = left + 1, j = right;
	while (i <= j) {//use <= rather than <, because if at the begining, the i == j, then we should not just skip the loop, because if so the swap after the while would always swap the left and right, no matter which one is larger. with <= , if the situation happened, then we can enter the loop body, but the first two won't run, so we have to write a else clause to deal with this situation , which can be either increase i or decrease j or both(not necessarily);
		while (data[i] < pivot)
			++i;
		while (data[j] > pivot)
			--j;
		if (i < j)
			swap(data[i++], data[j--]);
		else
			++i;
	}
	swap(data[left], data[j]);
	return j;
}

void prepareData(vector<int>& data) {
	clock_t _time = clock();
	default_random_engine _e(_time);
	for (auto times = 10 + _e() % 10; times > 0; times--)
		data.push_back(_e() % 100);
}

void printVector(const vector<int>& data) {
	cout << "-------start of print vector-------" << endl;
	for (auto k : data)
		cout << k << "\t";
	cout << endl;
	cout << "-------end of print vector-------" << endl << endl;
}
