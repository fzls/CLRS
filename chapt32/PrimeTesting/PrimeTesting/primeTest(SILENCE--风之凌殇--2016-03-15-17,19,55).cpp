/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    primeTest.cpp
* @version:      v1.0
* @Time:         2016-03-15 16:17:05
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
#include <chrono>

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


clock_t __time = clock();
default_random_engine __e(__time);

bool is_prime(int n) {
    if(n < 2) {
        return false;
    }

    if(n == 2) {
        return true;
    }

    if(n % 2 == 0) {
        return false;
    }

    int _sqrt = static_cast<int>(sqrt(n));

    for (int i = 3; i <= _sqrt; i += 2)
        if(n % i == 0) {
            return false;
        }

    return true;
}

int modular_exponentiation(int a, int b, int n) {
    int c = 0,
        d = 1;

    for (int i = 31; i >= 0; --i) {
        c <<= 1;
        d = (d * d) % n;
        int bi = (b & (1 << i)) >> i;

        if((b & (1 << i)) >> i == 1) {
            ++c;
            d = (d * a) % n;
        }
    }

    return d;
}

bool witness(int a, int n) {
    int t = 0, u = n - 1;

    while(u % 2 == 0) { //if u is even
        ++t;
        u /= 2;
    }

    modular_exponentiation(7, 560, 561);
    int x = modular_exponentiation(a, u, n), p = x;

    for (int i = 0; i < t; ++i) {
        x = (p * p) % n;

        if(x == 1 && p != 1 && p != n - 1) {
            return true;
        }

        p = x;
    }

    if(x != 1) {
        return true;
    }

    return false;
}

bool miller_rabin(int n, int s) {
    for (int i = 0; i < s; ++i) {
        int a = 1 + __e() % (n - 1);

        if (witness(a, n)) {
            return false;
        }
    }

    return true;
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
    clock_t _time = clock();
    default_random_engine _e(_time);
    int MAX_TIME = 10000, s = 1000;
    chrono::duration<double, milli> naive_t(0), miller_t(0);
    int error_cnt = 0;

    for (int i = 0; i < MAX_TIME; ++i) {
        int tmp = _e() % 0x7FFFFFFF;
        auto first = chrono::high_resolution_clock::now();
        bool naive = is_prime(tmp);
        auto second = chrono::high_resolution_clock::now();
        bool mr = miller_rabin(tmp, s);
        auto third = chrono::high_resolution_clock::now();

        if(naive != mr) {
            ++error_cnt;
            cout << "error test " << tmp << " which is " << (naive ? "" : "not ") << "a prime\n";
        }

        naive_t += second - first;
        miller_t += third - second;
    }

    cout << "time for test " << MAX_TIME << " primes\n";
    cout << "naive algorithm           : " << naive_t.count() << " ms\n";
    cout << "miller_rabin algorithm    : " << miller_t.count() << " ms\n";
    cout << "error rate is " << setprecision(2) << 100.0 * error_cnt / MAX_TIME << "%" << endl;
    return 0;
}
