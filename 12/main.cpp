#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// solution:
// use backtracking and each time replace a ? with #
// this will probably work since each spring is a string that is
// not too long
// we will iterate through the chars of each spring
// if we see a '?' then we try replace it with '#'
// then we replace it with '.'

long long backtrack(string& spring, vector<int>& group, int start) {
    if (start == spring.size()) {

        int curLength = 0;
        int groupIdx = 0;

        for (char c: spring) {
            if (c == '#') curLength++;
            else {
                if (curLength == group[groupIdx]) groupIdx++;
                else if (curLength != 0) return 0;

                curLength = 0;
            }
        }

        if (groupIdx == group.size() && curLength == 0) return 1;
        else if (groupIdx == group.size()-1 && curLength == group.back()) return 1;
        else return 0;
    }

    long long sum = 0;
    for (int i = start; i < spring.size(); i++) {
        if (spring[i] == '?') {
            spring[i] = '#';
            sum += backtrack(spring, group, i+1);
            spring[i] = '.';
            sum += backtrack(spring, group, i+1);
            spring[i] = '?';
            break;
        } else if (i == spring.size() - 1) {
            sum += backtrack(spring, group, i+1);
        }
    }

    return sum;
}

long long solve(vector<string>& springs, vector<vector<int>>& groups) {
    int n = springs.size();
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        sum += backtrack(springs[i], groups[i], 0);
    }

    return sum;
}

int main() {
    ifstream inputFile("input.txt");

    string line;
    vector<string> springs;
    vector<vector<int>> groups;

    while (getline(inputFile, line)) {
        groups.push_back({});
        string spring = line.substr(0, line.find(' '));
        string group = line.substr(line.find(' ')+1);

        springs.push_back(spring);

        istringstream groupStream(group);
        string token;
        while (getline(groupStream, token, ',')) {
            groups.back().push_back(stoi(token));
        }
    }

    cout << "The solution to part one is " << solve(springs, groups) << endl;

    return 0;
}