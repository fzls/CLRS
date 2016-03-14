/*
+----------------------------------------------------------
*
* @authors: é£Žä¹‹å‡Œæ®‡ <1054073896@qq.com>
* @FILE NAME:    LargestCommonSubsequence.cpp
* @version:
* @Time:         2015-12-29 22:13:22
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
#include <iomanip>
#pragma warning(disable:4996)

using namespace std;

class Problem {
  public:
    Problem();
    ~Problem();
    int solve();
  private:
    string X;
    string Y;
    vector<vector<int>> common;
    vector<vector<int>> path;
    void print(int , int);
    enum DIR {
        LEFT,
        UPWARD,
        DIAGONAL
    };
};

Problem::Problem() {
    cin >> X >> Y;
    common.resize(X.size() + 1);

    for (auto &v : common) {
        v.resize(Y.size() + 1);
    }

    path.resize(X.size() + 1);

    for (auto &v : path) {
        v.resize(Y.size() + 1);
    }
}

Problem::~Problem() {
}

int Problem::solve() {
    //¨I ¨J ¨K ¨L ¡ú ¡û ¡ü ¡ý
    int m = X.size();
    int n = Y.size();

    for (int i = 1; i <= m; ++i) {
        common[i][0] = 0;
    }

    for (int j = 0; j <= n; ++j) {
        common[0][j] = 0;
    }

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (X[i - 1] == Y[j - 1]) {
                common[i][j] = common[i - 1][j - 1] + 1;
                path[i][j] = DIAGONAL;
            } else if (common[i - 1][j] >= common[i][j - 1]) {
                common[i][j] = common[i - 1][j];
                path[i][j] = UPWARD;
            } else {
                common[i][j] = common[i][j - 1];
                path[i][j] = LEFT;
            }

    print(m, n);
    cout << endl;

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i && j) {
                switch (path[i][j]) {
                    case DIAGONAL:
                        cout << " ¨I ";
                        break;

                    case UPWARD:
                        cout << "   ¡ü";
                        break;

                    case LEFT:
                        cout << "    ";
                        break;

                    default:
                        break;
                }
            } else {
                cout << "\t";
            }
        }

        cout << endl;

        for (int j = 0; j <= n; ++j) {
            if (path[i][j] == LEFT && i && j) {
                cout << "¡û";
                cout << setw(3) << common[i][j];
            } else {
                cout << setw(4) << common[i][j];
            }
        }

        cout << endl;
    }

    return common[m][n];
}

void Problem::print(int m, int n) {
    if (m != 0 && n != 0) {
        //¨I ¨J ¨K ¨L ¡ú ¡û ¡ü ¡ý
        switch (path[m][n]) {
            case DIAGONAL:
                //cout << "¨I ";
                print(m - 1, n - 1);
                cout << X[m - 1];
                break;

            case UPWARD:
                //cout << "¡ü ";
                print(m - 1, n);
                break;

            case LEFT:
                //cout << "¡û ";
                print(m , n - 1);
                break;

            default:
                break;
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
    Problem problem;
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
