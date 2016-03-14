/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    linearProgramming.cpp
* @version:      v1.0
* @Time:         2016-03-12 12:57:50
* @Description:
*
+----------------------------------------------------------
*/
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:66777216")

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
#pragma region DebugSetting
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif
#pragma endregion

const int INF = 0x7FFFFFFF;

class LP {
  public:
    LP();
    ~LP();

  private:
    vector<double> b, c, B, N;
    vector<vector<double>> A;
    map<string, int> v2idx;
    double objective();

    void init();

    void ignore_space();

    inline bool isspace(char c)  {
        return c == ' ' || c == '\t';
    }
};

LP::LP() {
    init();
}

LP::~LP() {
}

void LP::init() {
    string goal;
    cin >> goal;//maximize
    int sign = 1;
    string val;
    int cnt = 0;

    //get c and x
    while (true) {
        ignore_space();
        double coeff = 1.0;

        if (cin.peek() == '\n') {
            break;
        }

        //get sign
        if(cin.peek() == '-' || cin.peek() == '+') {
            sign = cin.peek() == '-' ? -1 : 1;
            cin.get(); ignore_space();
        }

        //get coeff and val

        if (isdigit(cin.peek())) {
            cin >> coeff;
        }

        coeff *= sign;
        c.push_back(coeff);
        cin >> val;
        v2idx[val] = cnt;
        N.push_back(cnt);
        cnt++;
    }

    cin.ignore();
    string sub;
    getline(cin, sub);
    cin.ignore();

    //get A and b
    while(true) {
        //B
        if (!(cin >> val)) {
            break;
        }

        v2idx[val] = cnt;
        B.push_back(cnt);
        c.push_back(0.0);
        cnt++;
        //rhs
        ignore_space();
        cin.get();//ignore =
        ignore_space();
        double _b;
        cin >> _b;
        b.push_back(_b);
        vector<double> ai(N.size(), 0);

        //get A and N
        while(true) {
            ignore_space();

            if (cin.peek() == '\n' || cin.peek() == EOF) {
                break;
            }

            sign = cin.get() == '-' ? -1 : 1;
            ignore_space();
            double coeff = 1.0;

            if(isdigit(cin.peek())) {
                cin >> coeff;
            }

            coeff *= sign;
            cin >> val;
            int sub_index = v2idx[val];
            ai[sub_index] = coeff;
        }

        A.push_back(ai);
    }

    cout << goal << " : ";

    for (int i = 0; i < N.size(); ++i) {
        bool minus = c[i] < 0;

        if (i != 0) {
            cout << (minus ? " - " : " + ");
        } else {
            cout << (minus ? " - " : "");
        }

        if (abs(c[i]) != 1) {
            cout << abs(c[i]);
        }

        cout << "x" << N[i] + 1;
    }

    cout << endl;
    cout << sub << endl;

    for (int i = 0; i < B.size(); ++i) {
        cout << "\tx" << B[i] + 1 << " = " << b[i];

        for (int j = 0; j < N.size(); ++j) {
            cout << (A[i][j] < 0 ? " - " : " + ");

            if (abs(A[i][j]) != 1) {
                cout << abs(A[i][j]);
            }

            cout << "x" << j + 1;
        }

        cout << endl;
    }
}

void LP::ignore_space() {
    while(isspace(cin.peek())) {
        cin.get();
    }
}

int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    LP lp;
    return 0;
}
