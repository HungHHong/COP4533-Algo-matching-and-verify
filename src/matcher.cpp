#include <bits/stdc++.h>
#include "common.hpp"
#include <chrono>

using namespace std;



tuple<vector<vector<int>>,vector<vector<int>>> readInput(){

    // 1. read n
    int n;
    if (!(cin >> n)) return {}; // base: do nothing if n = 0

    // 2. read hospital prefs list
    // hospPref[h][k] = kth student on hospital h's list (1 index)
    vector<vector<int>> hospPref(n + 1, vector<int>(n + 1));
    for (int h = 1; h <= n; h++) {
        for (int k = 1; k <= n; k++) {
            cin >> hospPref[h][k];
        }
    }

    // 3. read student prefs
    // compare if s have an like h more than h'
    // studentRank[s][h] = position (1..n) of hospital h in student s preference list
    vector<vector<int>> studentRank(n + 1, vector<int>(n + 1, 0));
    for (int s = 1; s <= n; s++) {
        for (int k = 1; k <= n; k++) {
            int h;
            cin >> h;
            studentRank[s][h] = k;
        }
    }
    
    // Tuple in which first value is hosp pref and second is stud pref.
    tuple<vector<vector<int>>,vector<vector<int>>> ans(hospPref,studentRank);

    return ans;

}

MatchResult matcher() {
    
    tuple <vector<vector<int>>,vector<vector<int>>> input = readInput();

    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> hospPref=get<0>(input);
    vector<vector<int>> studentRank=get<1>(input);

    int n=hospPref.size()-1;

    // mark all hospitals free
    // 0 in h or s = unmatch
    // hospitalMatch[h] = student matched to hospital h
    vector<int> hospitalMatch(n + 1, 0);

    // mark all students free
    // studentMatch[s] = hospital matched to student s
    vector<int> studentMatch(n + 1, 0);

    // for each hospital: keep track of who they already proposed to
    // nextIdx[h] = which position in hospPref[h] we propose to next
    vector<int> nextIdx(n + 1, 1);

    // keep a list/queue of free hospitals to "pick that hospital h"
    queue<int> freeHospitals;
    for (int h = 1; h <= n; h++) freeHospitals.push(h);

    // while (there is some hospital h that is free AND h has not proposed to everyone)
    while (!freeHospitals.empty()) {
        int h = freeHospitals.front();
        freeHospitals.pop();

        // if h already matched, we skip
        if (hospitalMatch[h] != 0) continue;

        // if h proposed to everyone already, edge case
        if (nextIdx[h] > n) continue;

        // let s = next student on h's list
        int s = hospPref[h][nextIdx[h]];
        nextIdx[h]++; // now h has proposed to s

        // if s is free: match h with s
        if (studentMatch[s] == 0) {
            studentMatch[s] = h;
            hospitalMatch[h] = s;
        } else {
            // else: let h2 = current hospital matched with s
            int h2 = studentMatch[s];

            // if s likes h more than h2: switch
            if (studentRank[s][h] < studentRank[s][h2]) {
                studentMatch[s] = h;
                hospitalMatch[h] = s;

                hospitalMatch[h2] = 0;     // make h2 free
                freeHospitals.push(h2);    // h2 will propose again later
            } else {
                // else: s rejects h, so h stays free
                freeHospitals.push(h);
            }
        }
    }
    
    map<int,int> ans;

    // after loop: print matching
    for (int h = 1; h <= n; h++) {
        ans.emplace(h,hospitalMatch[h]);
        cout << h << " " << hospitalMatch[h] << "\n";
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    
    cout << "Time taken: " << elapsed.count() << " seconds\n";

    return {hospPref, studentRank, ans};
}

int main(){
    matcher();
    return 0;
}
// note:
// - hospitals propose not students
// - student chooses best hospital so far
// - eventually no hospital can improve
