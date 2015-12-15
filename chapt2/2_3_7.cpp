/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 2_3_7.cpp
* @version:
* @Time: 		 2015-11-04 09:05:20
* @Description:  2.3-7 ?
Describe a ‚.nlgn/-time algorithm that, given a set S of n integers and another
integer x, determines whether or not there exist two elements in S whose sum is
exactly x.
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
private:
	vector<int> S ;
	vector<int> T ;
	vector<int> R ;
	int _sum;

public:
	Solution(int sum): _sum(sum) {
		int temp;
		while (cin >> temp) {
			S.push_back(temp);
			T.push_back(_sum - temp);
		}
	}
	~Solution() {}
	void check() {
		sort(S.begin(), S.end());
		remove_identical(S);
		sort(T.begin(), T.end());
		remove_identical(T);
		// print(S);
		// print(T);
		merge(S, T);
		// print(R);
		if (check(R))
			cout << "Yes";
		else
			cout << "No";
	}
private:
	void print(const vector<int>&V) {
		for (auto i = V.begin(); i != V.end(); ++i)
		{
			cout << *i << " ";
		}
		cout << endl;

	}
	void remove_identical(vector<int>& V) {
		for (std::vector<int>::iterator i = V.begin(); i + 1 != V.end();)
		{
			if (*i == *(i + 1)) {
				i = V.erase(i);
			} else {
				i++;
			}
		}
	}
	void merge(vector<int> &left, vector<int> &right) {
		std::vector<int>::iterator i = left.begin(), j = right.begin();
		while (i != left.end() && j != right.end())
			if (*i < *j)
				R.push_back(*i++);
			else
				R.push_back(*j++);
		while (i != left.end())
			R.push_back(*i++);
		while (j != right.end())
			R.push_back(*j++);
	}
	bool check(const vector<int> &V) {

		for (auto i = V.begin(); i + 1 != V.end(); ++i)
			if (*i == *(i + 1))
				return true;
		return false;

	}
};

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	int x;
	cin >> x;
	Solution s{x};
	s.check();

	cout << endl;
	system("pause");
	return 0;
}

