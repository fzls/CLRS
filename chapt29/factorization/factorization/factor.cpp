/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    factor.cpp
* @version:      v1.0
* @Time:         2016-03-14 00:04:57
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

int gcd(int a, int b) {
    int t;

    while(b != 0) {
        t = a;
        a = b;
        b = t % b;
    }

    return a;
}

void pollard_rho(int n) {
    auto time = clock();
    std::default_random_engine e1(time);

    while(true) {
        int i = 1, x = e1() % n, y = x, k = 2, d;
        cout << "random is :" << x << endl;
        system("pause");

        while (i < n / 2) {
            ++i;
            x = (x * x - 1) % n;
            //        cout << "x :" << x << " k :" << k << endl;
            //        system("pause");
            d = gcd(abs(y - x), n);

            if (d != 1 && d != n) {
                cout << d << endl;
            }

            if (i == k) {
                y = x;
                k <<= 1;
            }
        }
    }
}

int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        //      freopen("test.in", "r", stdin);
        //      freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    int n;
    cin >> n;
    pollard_rho(n);
    return 0;
}
