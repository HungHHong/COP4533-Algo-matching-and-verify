#include <bits/stdc++.h>
#include "matcher.cpp"
using namespace std;

int verifier() {

    MatchResult res = matcher();

    auto& hospPref = res.hospPref;
    auto& studentRank = res.studentRank;
    auto& check = res.match;

    set<int> h;
    set<int> s;

    //Checks for no duplicates
    for (const auto& pair : check) {

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
    int size = check.size();


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
    return 0;
}

int main(){
    verifier();
    return 0;
}