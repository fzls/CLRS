/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 stacks.cpp
* @version:
* @Time: 		 2015-11-14 18:11:31
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

using namespace std;

template<typename T>
class Stack
{
private:
	int _capcity;
	int _size;
	vector<T> _data;

public:
	Stack(int capcity): _capcity(capcity), _size(0), _data(_capcity) {}
	~Stack() {}
	bool empty() {
		return _size == 0;
	}
	void push(T value) {
		if (_size == _capcity)
			cout << "Stack is full" << endl;
		else
			_data[_size++] = value;
	}
	T& pop() {
		if (_size == 0) {
			cout << "Stack is empty" << endl;
		}
		else
			return _data[--_size];
	}
	void print() {
		cout << "-------print stack--------" << endl;
		for (int i = 0; i < _size; ++i)
			cout << _data[i] << "\t";
		cout << endl << endl;
	}
};


int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	Stack<int> stack(10);
	stack.print();
	for (int i = 0; i < 15; ++i)
		stack.push(i * i);
	stack.print();
	for (int i = 0; i < 15; ++i)
		stack.pop();
	stack.print();

	cout << endl;
	system("pause");
	return 0;
}
