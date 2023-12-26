#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

long long solve(vector<string> reflector) {
    int sum = 0;
    int m = reflector.size();
    int n = reflector[0].size();

    for (int j = 0; j < n; j++) {
        int curPos = 0;
        for (int i = 0; i < m; i++) {
            if (reflector[i][j] == '#') {
                curPos = i+1;
            } else if (reflector[i][j] == 'O') {
                reflector[i][j] = '.';
                reflector[curPos][j] = 'O';
                curPos++;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (reflector[i][j] == 'O') sum += m-i;
        }
    }

    return sum;
}

int main() {
    ifstream inputFile("input.tXt");

    string line;
    vector<string> reflector;
    while (getline(inputFile, line)) {
        reflector.push_back(line);
    }

    cout << "The solution to part one is " << solve(reflector) << endl;

    return 0;
}