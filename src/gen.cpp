#include <bits/stdc++.h>
using namespace std;

// Generates random preference lists for the hospital-student
// matching problem.

// Output format matches the assignment specification:
// n
// n lines of hospital preferences
// n lines of student preferences

int main(int argc, char** argv) {

    // Check if n is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " n\n";
        return 0;
    }

    int n = stoi(argv[1]);

    // print number of hospitals/students
    cout << n << endl;

    // seed
    srand(123);

    // Base preference list: 1..n
    vector<int> prefs;
    for (int i = 1; i <= n; i++) {
        prefs.push_back(i);
    }

    // generating hospital preference lists
    for (int h = 1; h <= n; h++) {
        random_shuffle(prefs.begin(), prefs.end());

        for (int i = 0; i < n; i++) {
            cout << prefs[i];
            if (i + 1 < n) cout << " ";
        }
        cout << endl;
    }

    // generating student preference lists
    for (int s = 1; s <= n; s++) {
        random_shuffle(prefs.begin(), prefs.end());

        for (int i = 0; i < n; i++) {
            cout << prefs[i];
            if (i + 1 < n) cout << " ";
        }
        cout << endl;
    }

    return 0;
}