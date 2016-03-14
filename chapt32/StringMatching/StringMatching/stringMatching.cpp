/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    stringMatching.cpp
* @version:      v1.0
* @Time:         2016-03-14 20:14:27
* @Description:  naive / Rabin-Karp / Finite autumation / KMP
*               当数字可能很大时，注意溢出问题
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
const int ALPHABET_SIZE = 256;

typedef void(*match_algo)(string &, string &);

void measure_time(string text, string pattern, string algorithm_name, match_algo match) {
    auto start = std::chrono::high_resolution_clock::now();
    match(text, pattern);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time for " << algorithm_name << " is : " << chrono::duration<double, milli>(end - start).count() << " ms\n";
}
void print_result(string &text, string &pattern, int s) {
    //    return;
    cout << "Pattern occurs with shift " << s << "  : " << text.substr(0, s) << "___" << text.substr(s, pattern.size()) << "___" << text.substr(s + pattern.size()) << endl;
}
bool matches(string &text, string &pattern, int s) {
    for (int i = 0; i < pattern.size(); ++i) {
        if (pattern[i] != text[s + i]) {
            return false;
        }
    }

    return true;
}
void naive_string_matcher(string &text, string &pattern) {
    int n = text.length();
    int m = pattern.length();

    for (int s = 0; s <= n - m; ++s) {
        if(matches(text, pattern, s)) {
            print_result(text, pattern, s);
        }
    }
}

bool is_prime(int n) {
    if (n < 2) {
        return false;
    }

    if(n == 2) {
        return true;
    }

    if(n % 2 == 0) {
        return false;
    }

    int _sqrt = static_cast<int>(sqrt(n));

    for (int i = 3; i <= _sqrt; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}


int max_prime(int d) {
    int result = 2047;//if q is too large , eg.2^12, the divide and conquer method of power might overflow in line 124

    while(!is_prime(result)) {
        result -= 2;
    }

    return result;
}
int power_mod_q(int x, int n, int q) {
    if (n == 0) {
        return 1;
    }

    //    return (power_mod_q(x, n - 1, q) * x) % q;
    if(n % 2 == 0) {
        int half = power_mod_q(x, n / 2, q);
        return (half * half) % q;
    } else {
        int half = power_mod_q(x, n / 2, q);
        return (half * half * x) % q;
    }
}
void rabin_karp_matcher(string &text, string &pattern) {
    int d = 1 << 8,
        q = max_prime(d),
        n = text.length(),
        m = pattern.length(),
        h = power_mod_q(d, m - 1, q),//right
        p = 0,
        t = 0;

    //preprocessing
    for (int i = 0; i < m; ++i) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    //matching
    for (int s = 0; s <= n - m; ++s) {
        if (p == t)
            if (matches(text, pattern, s)) {
                print_result(text, pattern, s);
            }

        if(s < n - m) {//eg: 1~2345|6 -> 1|2345~6
            t = (d * (q + t - (text[s] * h) % q) + text[s + m]) % q;
        }
    }
}


bool suffix(string &pattern, int k, int q, int a) { //p[k] == p[q]a?
    if (k == -1) { //e
        return true;
    }

    if (pattern[k] != a) {
        return false;
    }

    for (int i = k - 1; i >= 0; --i, --q)
        if (pattern[i] != pattern[q]) {
            return false;
        }

    return true;
}

void init_transition_function(vector<vector<int>> &transition, string &pattern, unordered_map<char, int> &alphabetMap) {
    int m = pattern.length();

    for (int q = 0; q <= m; ++q) {
        for (auto a : alphabetMap) {
            int k = min(m, q + 1);

            while (!suffix(pattern, k - 1, q - 1, a.first)) {//compare P_k and P_q+a
                k--;
            }

            transition[q][a.second] = k;
        }
    }
}

void finite_automaton_matcher(string &text, string &pattern) {
    unordered_map<char, int> alphabetMap;
    int idx = 0;

    //find out the set of alphabets
    for (auto c : text)
        if (alphabetMap.find(c) == alphabetMap.end()) {
            alphabetMap[c] = idx++;
        }

    for (auto c : pattern)
        if (alphabetMap.find(c) == alphabetMap.end()) {
            alphabetMap[c] = idx++;
        }

    vector<vector<int>> transition(pattern.size() + 1, vector<int>(alphabetMap.size()));
    init_transition_function(transition, pattern, alphabetMap);
    int n = text.size(),
        m = pattern.size(),
        q = 0;

    for (int i = 0; i < n; ++i) {
        q = transition[q][alphabetMap[text[i]]];

        if(q == m) {
            print_result(text, pattern, i - m + 1);
        }
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
    string pattern, text;
    getline(cin, pattern);
    getline(cin, text);
    cout << "pattern " << pattern << " with size of " << pattern.size() << endl;
    cout << "text with size of " << text.size() << endl;
    cout << "----------------------------------------------------\n";
    measure_time(text, pattern, "naive_string_matcher", naive_string_matcher);
    measure_time(text, pattern, "rabin_karp_matcher", rabin_karp_matcher);
    measure_time(text, pattern, "finite_automaton_matcher", finite_automaton_matcher);
    measure_time(text, pattern, "knuth_morris_pratt_matcher", knuth_morris_pratt_matcher);
    return 0;
}
