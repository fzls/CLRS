/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 directHashTable.cpp
* @version:
* @Time: 		 2015-11-16 20:14:08
* @Description:  direct access hash table
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
#include <iomanip>

using namespace std;

class DirectAccessHashTable
{
private:
	vector<int> _data;
	int _capcity;
	int _size;
public:
	DirectAccessHashTable(int capcity): _data(vector<int>(capcity, -1)), _capcity(capcity), _size(0) {}
	~DirectAccessHashTable() {}
	void insert(int value) {
		if (_data[value] == -1)
			_data[value] = value;
		else
			cout << value << " is already in the hashtable" << endl;
	}
	void Delete(int value) {
		if (_data[value] == value)
			_data[value] = -1;
		else
			cout << value << " is not in the hashtable" << endl;
	}
	void search(int value) {
		if (_data[value] == value)
			cout << value << " found " << endl;
		else
			cout << value << " not found" << endl;
	}
	void print() {
		cout << "------print hashtable------" << endl;
		int count = 0;
		for (auto k : _data) {
			if (k != -1)
				cout << setw(2) << k << " | " ;
			else
				cout << "   | ";
			if (++count == 5) {
				cout << endl;
				count -= 5;
			}
		}
		cout << endl;
	}
};

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	int capcity = 50;
	DirectAccessHashTable testHashTable(capcity);
	clock_t _time = clock();
	default_random_engine _e(_time);
	for (int i = 0; i < capcity; ++i)
		testHashTable.insert(_e() % capcity);
	testHashTable.print();
	for (int i = 0; i < capcity; ++i)
		testHashTable.search(_e() % capcity);
	testHashTable.print();
	for (int i = 0; i < capcity; ++i)
		testHashTable.Delete(_e() % capcity);
	testHashTable.print();

	cout << endl;
	system("pause");
	return 0;
}
