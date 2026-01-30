#include <bits/stdc++.h>
#include "common.hpp"
#include <chrono>

//#include "matcher.cpp"
using namespace std;

// reads:
// n
// n lines hospital prefs
// n lines student prefs
// n lines matching: "hospital student"
MatchResult readInput(){

    MatchResult res;

    // 1. read n
    int n;
    if (!(cin >> n)) return res; // base: do nothing if empty input

    // 2. read hospital prefs list
    // hospPref[h][k] = kth student on hospital h's list (1 index)
    res.hospPref.assign(n + 1, vector<int>(n + 1, 0));
    for (int h = 1; h <= n; h++) {
        for (int k = 1; k <= n; k++) {
            cin >> res.hospPref[h][k];
        }
    }

    // 3. read student prefs
    // compare if s have an like h more than h'
    // studentRank[s][h] = position (1..n) of hospital h in student s preference list
    res.studentRank.assign(n + 1, vector<int>(n + 1, 0));
    for (int s = 1; s <= n; s++) {
        for (int k = 1; k <= n; k++) {
            int h;
            cin >> h;
            res.studentRank[s][h] = k;
        }
    }

    // 4. read matching output (n lines)
    // match[h] = student matched to hospital h
    for (int i = 0; i < n; i++) {
        int h, s;
        if (!(cin >> h >> s)) break;
        res.match[h] = s;
    }

    return res;
}

int verifier() {

    MatchResult res = readInput();

    auto start = chrono::high_resolution_clock::now();

    auto& hospPref = res.hospPref;
    auto& studentRank = res.studentRank;
    auto& check = res.match;

    //Checks for empty input
    if (hospPref.size() <= 1) {
        cout << "INVALID due to empty input" << endl;
        return 0;
    }

    int n = (int)hospPref.size() - 1;

    //Checks if matching size is correct
    if ((int)check.size() != n) {
        cout << "INVALID due to wrong number of matches" << endl;
        return 0;
    }

    set<int> h;
    set<int> s;

    //Checks for no duplicates
    for (const auto& pair : check) {

        //Checks if hospital in valid range
        if(pair.first < 1 || pair.first > n){
            cout << "INVALID due to hospital id out of range " << pair.first << endl;
            return 0;
        }

        //Checks if student in valid range
        if(pair.second < 1 || pair.second > n){
            cout << "INVALID due to student id out of range " << pair.second << endl;
            return 0;
        }

        //Checks if hosptial has a duplicate
        if(h.find(pair.first)!= h.end()){
            cout << "INVALID due to duplicate hospital " << pair.first << endl;
            return 0;
        }

        //Checks if student has duplicate
        else if(s.find(pair.second)!= s.end()){
            cout << "INVALID due to duplicate student " << pair.second << endl;
            return 0;
        }
        //Adds if no duplicates found
        else{
            h.insert(pair.first);
            s.insert(pair.second);
        }

    }

    //Checks if all students and all hospitals are in list
    int size = n;

    for(int i=1; i<=size; i++){

        //Checks if each hospital is present
        if(h.find(i)==h.end()){
            cout << "INVALID due to missing hospital " << i << endl;
            return 0;
        }

        //Checks if each student is present
        if(s.find(i)==s.end()){
            cout << "INVALID due to missing student " << i << endl;
            return 0;
        }
    }

    //Confirm there is stability, no blocking pair

    map<int,int> studentMatch;

    //
    for (auto &pair : check) {
        studentMatch[pair.second] = pair.first;
    }

    //Check student pref first and see if the other hospital did not like them as much as their current one
    for (int h = 1; h <= size; h++) {
        int assignedStudent = check[h];

        //Looks at hospitals student prefer over their match
        for (int k = 1; k <= size; k++) {
            int s = hospPref[h][k];
            if (s == assignedStudent) break; // stop once we reach current match

            int currentHospital = studentMatch[s];

            //Checks if hospital prefers them over currently mactehd hospital
            if (studentRank[s][h] < studentRank[s][currentHospital]) {
                cout << "INVALID due to blocking pair with hospital "
                    << h << " and student " << s << "\n";

                return 0;
            }
        }

    }

    //If we reached this fair, it must be a valid stable
    cout << "VALID STABLE" << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    //Print time to stderr so it doesn't mess up autograder output
    cerr << "Time taken: " << elapsed.count() << " seconds\n";

    return 0;
}

int main(){
    verifier();
    return 0;
}