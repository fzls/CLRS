/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 maxSumSubarray.cpp
* @version:
* @Time: 		 2015-11-05 18:35:45
* @Description:  find the subarray which has the max sum
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <climits>

using namespace std;
//tuple<left,right,maxsum>
tuple<int, int, int> find_max_sum_subarray_DAC(vector<int>& data);
tuple<int, int, int> find_max_sum_subarray_DAC(vector<int>& data, int left, int right);
tuple<int, int, int> cross_max_sum_array(vector<int>& data, int left, int right);

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	vector<int> test ;
	int data;
	while (cin >> data)
		test.push_back(data);
	tuple<int, int, int> result = find_max_sum_subarray_DAC(test);
	cout << "start: " << get<0>(result) << " end: " << get<1>(result) << " maxSum: " << get<2>(result) << endl;
	cout << endl;
	system("pause");
	return 0;
}
tuple<int, int, int> find_max_sum_subarray_DAC(vector<int>& data) {
	int n = static_cast<int>(data.size());
	return find_max_sum_subarray_DAC(data, 0, n - 1);
}
tuple<int, int, int> find_max_sum_subarray_DAC(vector<int>& data, int left, int right) {
	if (left == right)
		return tuple<int, int, int>(left, right, data[left]);
	else {
		int middle = (left + right) / 2;
		auto leftSum = find_max_sum_subarray_DAC(data, left, middle);
		auto rightSum = find_max_sum_subarray_DAC(data, middle + 1, right);
		auto crossSum = cross_max_sum_array(data, left, right);
		if (get<2>(leftSum) >= get<2>(rightSum) && get<2>(leftSum) >= get<2>(crossSum))
			return leftSum;
		else if (get<2>(rightSum) >= get<2>(leftSum) && get<2>(rightSum) >= get<2>(crossSum))
			return rightSum;
		else
			return crossSum;
	}
}
tuple<int, int, int> cross_max_sum_array(vector<int>& data, int left, int right) {
	int middle = (left + right) / 2;
	int left_index, right_index;
	int leftSum = 0;
	int leftMaxSum = INT_MIN;
	for (int i = middle; i >= left; --i) {
		leftSum += data[i];
		if (leftSum > leftMaxSum) {
			leftMaxSum = leftSum;
			left_index = i;
		}
	}

	int rightSum = 0;
	int rightMaxSum = INT_MIN;
	for (int i = middle + 1; i <= right; ++i) {
		rightSum += data[i];
		if (rightSum > rightMaxSum) {
			rightMaxSum = rightSum;
			right_index = i;
		}
	}

	return tuple<int, int, int>(left_index, right_index, leftMaxSum + rightMaxSum);
}
