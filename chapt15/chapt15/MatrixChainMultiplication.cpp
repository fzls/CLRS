/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:    MatrixChainMultiplication.cpp
* @version:
* @Time:
* @Description: when dealing with DP problem , first think problem with index 1~n, only when
*               use a specific language to implement it, we change the index accordingly,
*               for example we change i to i-1 in c++, so the index would be 0~n-1, or we
*               create a n+1 size array , and only make use of the last n position.
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
#pragma warning(disable:4996)
using namespace std;

void init_vector_from_file(vector<int> &random) {
    int temp;

    while (cin >> temp) {
        random.push_back(temp);
    }
}

class Problem {
  public:
    Problem(int size = 0);
    ~Problem();
    int solve();
  private:
    vector<int> price;
    vector<vector<int>> path;
    vector<vector<int>> result;
    int MatrixChainMultiplication(int start, int end);
    void print(int, int);
};

Problem::Problem(int size): price(size + 1, 0), path(size, vector<int>(size, -1)), result(size, vector<int>(size, INT32_MAX)) {
    for (int i = 0; i < size + 1; ++i) {
        cin >> price[i];
    }
}


Problem::~Problem() {
}

int Problem::solve() {
    int temp = MatrixChainMultiplication(0, price.size() - 2);
    print(0, price.size() - 2);
    return temp;
}

int Problem::MatrixChainMultiplication(int start, int end) {
    ////recursive
    //if (result[start][end] != INT32_MAX) {
    //    return result[start][end];
    //}

    //if (start == end) {
    //    return result[start][end] = 0;
    //}

    //for (int k = start; k < end; ++k) {
    //    int temp = MatrixChainMultiplication(start, k) + MatrixChainMultiplication(k + 1,
    //               end) + price[start] * price[k + 1] * price[end + 1];

    //    if (temp < result[start][end]) {
    //        result[start][end] = temp;
    //        path[start][end] = k;
    //    }
    //}

    //return result[start][end];

    //iterative
    for (int i = 0; i < result.size(); ++i) {
        result[i][i] = 0;
    }

    for (int l = 2; l <= result.size(); ++l)
        for (int i = 0; i <= result.size() - l; ++i) {
            int j = i + l - 1;

            for (int k = i; k < j; ++k) {
                int temp = result[i][k] + result[k + 1][j] + price[i] * price[k + 1] * price[j + 1];

                if (temp < result[i][j]) {
                    result[i][j] = temp;
                    path[i][j] = k;
                }
            }
        }

    return result[start][end];
}

void Problem::print(int left, int right) {
    //TODO
    if(left == right) {
        cout << "A" << left + 1;
    } else {
        cout << "(";
        print(left, path[left][right]);
        print(path[left][right] + 1, right);
        cout << ")";

        if (left == 0 && right == price.size() - 2) {
            cout << endl;
        }
    }
}

int main() {
    #pragma region START_CODE
    #ifdef ONLINE_JUDGE
    #else
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    #endif
    #pragma endregion
    //TODO
    int size;
    cin >> size;
    Problem problem(size);
    cout << problem.solve();
    #pragma region END_CODE
    #ifdef ONLINE_JUDGE
    #else
    cout << endl;
    system("pause");
    #endif
    return 0;
    #pragma endregion
}
