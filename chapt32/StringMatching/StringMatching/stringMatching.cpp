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
#include <thread>

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
void print_result(string &text, string &pattern, int s);
void measure_time(string text, string pattern, string algorithm_name, match_algo match) {
    auto start = std::chrono::high_resolution_clock::now();
    match(text, pattern);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time for " << algorithm_name << " is : " << chrono::duration<double, milli>(end - start).count() << " ms\n";
    cout << "----------------------------------------------------\n";
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

void compute_prefix_function(string &pattern, vector<int> &next) {
    int m = pattern.length(),//index start from 0
        k = 0;//number of chars that has matched
    next[0] = 0;

    for (int q = 1; q < m; ++q) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = next[k - 1];
        }

        if (pattern[k] == pattern[q]) {
            ++k;
        }

        next[q] = k;
    }
}

void knuth_morris_pratt_matcher(string &text, string &pattern) {
    int n = text.length(),
        m = pattern.length(),//index begin at 0
        q = 0;//number of chars matched
    vector<int> next(pattern.length());
    compute_prefix_function(pattern, next);

    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern[q] != text[i]) {//pattern[q] is the q+1 elem
            q = next[q - 1];
        }

        if (pattern[q] == text[i]) {
            ++q;
        }

        if(q == m) {
            print_result(text, pattern, i + 1 - m);
            q = next[q - 1];
        }
    }
}

void improve_prefix_function(string &pattern, vector<int> &next) {
    vector<int> original(next);
    int m = next.size();

    for (int q = 0; q < m - 1; ++q) {
        if(original[q] == 0) {
            next[q] = 0;
        } else {
            if (pattern[original[q]] == pattern[q + 1]) {
                next[q] = next[original[q] - 1];
            } else {
                next[q] = original[q];
            }
        }
    }
}

void knuth_morris_pratt_matcher_improved_v1(string &text, string &pattern) {
    int n = text.length(),
        m = pattern.length(),//index begin at 0
        q = 0;//number of chars matched
    vector<int> next(pattern.length());
    compute_prefix_function(pattern, next);
    improve_prefix_function(pattern, next);

    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern[q] != text[i]) {//pattern[q] is the q+1 elem
            q = next[q - 1];
        }

        if (pattern[q] == text[i]) {
            ++q;
        }

        if (q == m) {
            print_result(text, pattern, i + 1 - m);
            q = next[q - 1];
        }
    }
}
void check_cyclic_rotation(string &text, string &pattern) {
    int n = text.length(),
        m = pattern.length(),//index begin at 0
        q = 0;//number of chars matched

    if(n != m) {
        cout << "NOT a cyclic rotation\n";
        return;
    }

    vector<int> next(pattern.length());
    compute_prefix_function(pattern, next);
    improve_prefix_function(pattern, next);
    bool pass_first_part = false, pass_second_part = true;

    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern[q] != text[i]) {//pattern[q] is the q+1 elem
            q = next[q - 1];
        }

        if (pattern[q] == text[i]) {
            if(i == n - 1) {
                pass_first_part = true;
            }

            ++q;
        }
    }

    if(pass_first_part) {
        for (int i = 0; i < n - q; ++i)
            if(pattern[q + i] != text[i]) {
                pass_second_part = false;
                break;
            }
    }

    if(pass_first_part && pass_second_part) {
        cout << "YES : " << text << "<-> and <->" << pattern << " are cyclic rotaitons of each other" << endl;
        cout << "with a left rotation shift of " << n - q << " steps\n";
    } else {
        cout << "NOT a cyclic rotation\n";
    }
}

void init_transition_function_improved_v1(vector<vector<int>> &transition, string &pattern, unordered_map<char, int> &alphabetMap) {
    int m = pattern.length();
    vector<int> next(pattern.length());
    compute_prefix_function(pattern, next);

    for (auto a : alphabetMap) {
        transition[0][a.second] = pattern[0] == a.first ? 1 : 0;
    }

    for (int q = 1; q <= m; ++q) {
        for (auto a : alphabetMap) {
            if (q == m || pattern[q] != a.first) {
                transition[q][a.second] = transition[next[q - 1]][a.second];
                continue;
            }

            transition[q][a.second] = q + 1;
        }
    }
}

void finite_automaton_matcher_improved_v1(string &text, string &pattern) {
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
    init_transition_function_improved_v1(transition, pattern, alphabetMap);
    int n = text.size(),
        m = pattern.size(),
        q = 0;

    for (int i = 0; i < n; ++i) {
        q = transition[q][alphabetMap[text[i]]];

        if (q == m) {
            print_result(text, pattern, i - m + 1);
        }
    }
}

void print_result(string &text, string &pattern, int s) {
    return;
    cout << "Pattern occurs with shift " << s << "  : " << text.substr(0, s) << "___" << text.substr(s, pattern.size()) << "___" << text.substr(s + pattern.size()) << endl;
}

struct Matcher {
    string name;
    match_algo pFunction;

    Matcher(string name, match_algo p_function)
        : name(name),
          pFunction(p_function) {
    }
};

void repetition_factor(string &pattern, vector<int> &factors) {
    for (int i = 1; i <= pattern.size(); ++i) {
        int l = 1;
        factors[i - 1] = 1;
        bool valid;

        for (; l <= i  / 2; ++l) {
            valid = true;

            if(i % l != 0) {
                continue;
            }

            for (int j = 1; j <= l; ++j) {
                for (int p = j; p + l <= i; p += l)
                    if(pattern[p - 1] != pattern[p + l - 1]) {
                        valid = false;
                        goto Invalid;
                    }
            }

            if (valid) {
                factors[i - 1] = i / l;
                break;
            }

        Invalid:
            ;//place holder
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
    string pattern, text ;
    getline(cin, pattern);
    getline(cin, text);
    cout << "pattern " << pattern << " with size of " << pattern.size() << endl;
    cout << "text with size of " << text.size() << endl;
    cout << "----------------------------------------------------\n";
    vector<Matcher> matchers;
    matchers.push_back(Matcher("naive_string_matcher", naive_string_matcher));
    matchers.push_back(Matcher("rabin_karp_matcher", rabin_karp_matcher));
    matchers.push_back(Matcher("finite_automaton_matcher", finite_automaton_matcher));
    matchers.push_back(Matcher("finite_automaton_matcher_improved_v1", finite_automaton_matcher_improved_v1));
    matchers.push_back(Matcher("knuth_morris_pratt_matcher", knuth_morris_pratt_matcher));
    matchers.push_back(Matcher("knuth_morris_pratt_matcher_improved_v1", knuth_morris_pratt_matcher_improved_v1));
    matchers.push_back(Matcher("check_cyclic_rotation", check_cyclic_rotation));
    //thread version
    vector<thread> threads;

    for (auto &matcher : matchers) {
        threads.push_back(
            move(
                thread(
                    measure_time,
                    text,
                    pattern,
                    matcher.name,
                    matcher.pFunction
                )
            )
        );
    }

    for (auto &t : threads) {
        t.join();
    }

    ////non therad version
    //for(auto &matcher : matchers) {
    //    measure_time(
    //        text,
    //        pattern,
    //        matcher.name,
    //        matcher.pFunction
    //    );
    //}
    //
    //
    //
    ////32-1
    //vector<int> factors(pattern.size());
    //repetition_factor(pattern, factors);
    //for (auto f : pattern) {
    //    cout << f << "\t";
    //}
    //cout << endl;
    //for (auto f : factors) {
    //    cout << f << "\t";
    //}
    //cout << endl;
    //return 0;
}





// test data
//pattern aa....aa with size of 9996
//text aa....aaaaa with size of 59976
//----------------------------------------------------
//NOT a cyclic rotation
//Time for check_cyclic_rotation is : 0.0078 ms
//----------------------------------------------------
//Time for knuth_morris_pratt_matcher is : 339.11 ms
//----------------------------------------------------
//Time for knuth_morris_pratt_matcher_improved_v1 is : 448.079 ms
//----------------------------------------------------
//Time for finite_automaton_matcher_improved_v1 is : 2416.89 ms
//----------------------------------------------------
//Time for finite_automaton_matcher is : 68166.3 ms
//----------------------------------------------------
//Time for rabin_karp_matcher is : 656768 ms
//----------------------------------------------------
//Time for naive_string_matcher is : 657601 ms
//----------------------------------------------------
