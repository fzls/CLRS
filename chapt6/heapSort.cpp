/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 heapSort.cpp
* @version:
* @Time: 		 2015-11-09 13:43:45
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

static int counts ;

void printVector(const vector<int>& data) ;
void maxHeapify(vector<int>& data, int index, int _length);
void buildMaxHeap(vector<int>& data);
void initialize(vector<int>& data);
void heapSort(vector<int>& data);
void deleteHeap(vector<int>&data, int index);
void removeMax(vector<int>& data) ;
void popUp(vector<int>& data, int index) ;

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	vector<int> data ;
	initialize(data);

	printVector(data);
	// sort(data.begin(), data.end());
	// heapSort(data);
	buildMaxHeap(data);
	printVector(data);
	deleteHeap(data, 1);
	printVector(data);

	const int _length = static_cast<int>(data.size());
	cout << "counts : " << counts << endl
	     << "N: " << _length << "\t" << 1.0 * counts / _length << endl
	     << "NlogN: " << static_cast<int>(_length * log2(_length)) << "\t" << 1.0 * counts / static_cast<int>(_length * log2(_length)) << endl
	     ;
	cout << endl;
	system("pause");
	return 0;
}

void deleteHeap(vector<int>&data, int index) {
	data[index] = data[0] + 1;
	popUp(data, index);
	removeMax(data);
}

void removeMax(vector<int>& data) {
	const int _length = static_cast<int>(data.size());
	data[0] = data[_length - 1];
	maxHeapify(data, 0, _length - 1);
	data.pop_back();
}

void popUp(vector<int>& data, int index) {
	int parent = (index - 1) / 2;
	while (parent >= 0 && data[index] > data[parent]) {
		swap(data[index], data[parent]);
		index = parent;
		parent = (index - 1) / 2;
	}
}

void printVector(const vector<int>& data) {
	cout << "-------start of print vector-------" << endl;
	int count = 2 ;
	int index = 0 ;
	for (auto k : data) {
		if (++index == count) {
			cout << endl;
			count *= 2;
		}
		cout << k << "\t";
	}
	cout << endl;
	cout << "-------end of print vector-------" << endl;
}

void maxHeapify(vector<int>& data, int index, int _length) {
	int larger = index * 2 + 1 ;
	if (larger < _length - 1 && data[larger + 1] > data[larger])
		++larger;
	if (larger < _length && data[larger] > data[index]) {
		swap(data[larger], data[index]);
		counts++;
		maxHeapify(data, larger, _length);
	}
}

void buildMaxHeap(vector<int>& data) {
	const int _length = static_cast<int>(data.size());
	for (int i = _length / 2 - 1; i >= 0; --i)
		maxHeapify(data, i, _length);
}
void heapSort(vector<int>& data) {
	const int _length = static_cast<int>(data.size());
	buildMaxHeap(data);
	for (int i = _length - 1; i > 0; --i) {
		swap(data[i], data[0]);
		maxHeapify(data, 0, i);
	}
}
void initialize(vector<int>& data) {
	clock_t _time = clock();
	default_random_engine _e(_time);
	int t = 10 + _e() % 10  ;
	for (int i = 0; i < t; ++i)
		data.push_back(_e() % 100 );
	counts = 0;
}
