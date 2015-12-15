/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 randomizedSelect.cpp
* @version:
* @Time: 		 2015-11-13 23:57:29
* @Description:  clrs page 216 chapt9
* pay attention to the Partition algorithm in the quick sort or the other, especial what to do when left + 1 = right;
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

int randomizedSelect(vector<int> &data, int order);
int randomizedSelect(vector<int> &data, int first, int last, int order);
int randomizedPartition(vector<int> &data, int first, int last);
int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	clock_t _time = clock();
	default_random_engine _e(_time);
	for (int i = 0; i < 100; i++)
	{	vector<int> data ;
		prepareData(data);
		const int _length = static_cast<int>(data.size());

		int order = 1 + _e() % _length;

		// cout << "the " << order << "th statistics is \t" << randomizedSelect(data, order) << endl;
		sort(data.begin(), data.end());
		// cout << "the answer should be  \t" << data[order - 1] << endl;
		cout << randomizedSelect(data, order) - data[order - 1] << endl;
		// cout << "--------------" << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}

int randomizedSelect(vector<int> &data, int order) {
	const int _length = static_cast<int>(data.size());
	return randomizedSelect(data, 0, _length - 1, order);
}
int randomizedSelect(vector<int> &data, int first, int last, int order) {
	int pivot = randomizedPartition(data, first, last);
	int pivot_order = pivot - first + 1;
	if (order == pivot_order)
		return data[pivot];
	else if (order < pivot_order)
		return randomizedSelect(data, first, pivot - 1, order);
	else
		return randomizedSelect(data, pivot + 1, last, order - pivot_order);
}
int randomizedPartition(vector<int> &data, int first, int last) {
	clock_t _time = clock();
	default_random_engine _e(_time);
	swap(data[first], data[first + _e() % (last - first + 1)]) ;
	int pivot = data[first];
	int lowerBound = first + 1, upperBound = last;
	while (lowerBound <= upperBound) {
		while (lowerBound <= last && data[lowerBound] < pivot)
			++lowerBound;
		while (data[upperBound] > pivot)
			--upperBound;
		if (lowerBound < upperBound)
			swap(data[lowerBound++], data[upperBound--]);
		else
			lowerBound++;
	}
	swap(data[first] , data[upperBound]);
	return upperBound;
}

void prepareData(vector<int>& data) {
	clock_t _time = clock();
	default_random_engine _e(_time);
	for (auto times = 20 + _e() % 10; times > 0; times--)
		data.push_back(10 + _e() % 100);
}
void printVector(const vector<int>& data) {
	cout << "-------start of print vector-------" << endl;
	int count = 1;
	for (auto k : data)
		cout << count++ << ":" << k << "\t";
	cout << endl;
	cout << "-------end of print vector-------" << endl << endl;
}

