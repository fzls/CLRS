/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 bucketSort.cpp
* @version:
* @Time: 		 2015-11-13 23:23:02
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
#include <list>

using namespace std;
void prepareData(vector<int>& data) ;
void printVector(const vector<int>& data) ;
int findMax(const vector<int> &data) ;

void bucketSort(vector<int> &data);

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	vector<int> data ;
	prepareData(data);
	vector<int> test(data);
	printVector(data);
	bucketSort(data);
	sort(test.begin(), test.end());
	printVector(data);
	printVector(test);

	cout << endl;
	system("pause");
	return 0;
}
void bucketSort(vector<int> &data) {
	const int _length = static_cast<int>(data.size());
	vector<list<int>> temp(_length);
	int max = findMax(data) + 1;
	for (auto k : data)
		temp[static_cast<int>(_length * k / max)].push_back(k);
	int index = 0;

	for (auto lists : temp) {
		lists.sort();
		while (!lists.empty()) {
			data[index++] = lists.front();
			lists.pop_front();
		}
	}

}

void prepareData(vector<int>& data) {
	clock_t _time = clock();
	default_random_engine _e(_time);
	for (auto times = 100 + _e() % 10; times > 0; times--)
		data.push_back(_e() % 100);
}

void printVector(const vector<int>& data) {
	cout << "-------start of print vector-------" << endl;
	for (auto k : data)
		cout << k << "\t";
	cout << endl;
	cout << "-------end of print vector-------" << endl << endl;
}

int findMax(const vector<int> &data) {
	int max = INT_MIN;
	for (auto k : data)
		if (k > max)
			max = k;
	return max;
}
