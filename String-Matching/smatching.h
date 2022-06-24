#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define ASCII 128
#define EASCII 256
#define EBCDIC 256

const int RADIX = 2;
const int PRIMENUM = 131;

typedef unsigned long long ull;

using std::cout;
using std::string;
using std::vector;

// String matching with Brute-Force Method
vector<int> find_bf(const string &str, const string &pat);

// String matching with Rabin-Karp Algorithm
vector<int> find_rk(const string &str, const string &pat);

// String matching with Boyer-Moore Algorithm
vector<int> find_bm(const string &str, const string &pat);
int compute_jump(const string &pat, const char &str);

// String matching with KMP Algorithm
vector<int> find_kmp(const string &str, const string &pat);

// Tools
bool check(string str, string pat, int index, vector<int> &result);
vector<int> failure_func(const string &pat);