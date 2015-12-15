/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 2_1.cpp
* @version:
* @Time: 		 2015-11-04 16:36:27
* @Description:  2-1 Insertion sort on small arrays in merge sort
Although merge sort runs in ‚.nlgn/ worst-case time and insertion sort runs
in ‚.n 2 / worst-case time, the constant factors in insertion sort can make it faster
in practice for small problem sizes on many machines. Thus, it makes sense to
coarsen the leaves of the recursion by using insertion sort within merge sort when
40 Chapter 2 Getting Started
subproblems become sufficiently small. Consider a modification to merge sort in
which n=k sublists of length k are sorted using insertion sort and then merged
using the standard merging mechanism, where k is a value to be determined.
a. Show that insertion sort can sort the n=k sublists, each of length k, in ‚.nk/
worst-case time.
b. Show how to merge the sublists in ‚.nlg.n=k// worst-case time.
c. Given that the modified algorithm runs in ‚.nk C nlg.n=k// worst-case time,
what isthe largest value of k as afunction ofn for which the modified algorithm
has the same running time as standard merge sort, in terms of ‚-notation?
d. How should we choose k in practice?
*
+----------------------------------------------------------
*/
const int BOUNDS = 0;
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
static int _inversion;
using namespace std;

void mergeSort(vector<int> &V) ;
void mergeSort(vector<int> &V, vector<int>&T, int left, int right) ;
void merge(vector<int> &V, vector<int> &T, int left, int right) ;
void print(const vector<int>&V) ;
void insertionSort(vector<int> &V, int left, int right);



void mergeSort(vector<int> &V) {
	const int n = static_cast<int>(V.size());
	vector<int> T =  vector<int>(n);
	_inversion = 0;
	mergeSort(V, T, 0, n - 1);
}
void mergeSort(vector<int> &V, vector<int>&T, int left, int right) {
	if (left < right - BOUNDS) {
		int middle = left + (right - left) / 2;
		mergeSort(V, T, left, middle);
		mergeSort(V, T, middle + 1, right);
		merge(V, T, left, right);
	}
	else
		insertionSort(V, left, right);
}
void merge(vector<int> &V, vector<int> &T, int left, int right) {
	int middle = (left + right) / 2;
	int i = left, j = middle + 1, t = 0;
	while (i <= middle && j <= right)
		if (V[i] <= V[j])
			T[t++] = V[i++];
		else {
			T[t++] = V[j++];
			_inversion += middle - i + 1;
		}
	while (i <= middle)
		T[t++] = V[i++];
	while (j <= right)
		T[t++] = V[j++];
	for (i = left, t = 0; i <= right; i++, t++)
		V[i] = T[t];
}
void insertionSort(vector<int> &V, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int key = V[i], j = i - 1;
		while (j >= left && V[j] > key) {
			V[j + 1] = V[j];
			j--;
		}
		V[j + 1] = key;
	}
}


void print(const vector<int>&V) {
	for (auto i = V.begin(); i != V.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
	cout << "_inversion is " << _inversion << endl;

}

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	int x;
	vector<int> V ;
	while (cin >> x)
		V.push_back(x);
	mergeSort(V);
	print(V);

	cout << endl;
	system("pause");
	return 0;
}

