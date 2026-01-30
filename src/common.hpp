#pragma once
#include <vector>
#include <map>
using namespace std;

struct MatchResult {
    vector<vector<int>> hospPref;
    vector<vector<int>> studentRank;
    map<int,int> match; // hospital -> student
};