#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

// Part 1
int solve1(vector<vector<char>>& engine) {
    int sum = 0;
    int m = engine.size();
    int n = engine[0].size();

    // isAdj[i][j] represents if engine[i][j] is adjacent to a symbol
    vector<vector<bool>> isAdj(m, vector<bool>(n));

    // setup for isAdj
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (engine[i][j] != '.' && (engine[i][j] < '0' || engine[i][j] > '9')) {
                if (i-1 >= 0) {
                    if (j-1 >= 0) isAdj[i-1][j-1] = true;
                    isAdj[i-1][j] = true;
                    if (j+1 < n) isAdj[i-1][j+1] = true;
                }
                if (j-1 >= 0) {
                    if (i-1 >= 0) isAdj[i-1][j-1] = true;
                    isAdj[i][j-1] = true;
                    if (i+1 < m) isAdj[i+1][j-1] = true;
                }
                if (i+1 < m) {
                    if (j-1 >= 0) isAdj[i+1][j-1] = true;
                    isAdj[i+1][j] = true;
                    if (j+1 < n) isAdj[i+1][j+1] = true;
                }
                if (j+1 < n) {
                    if (i-1 >= 0) isAdj[i-1][j+1] = true;
                    isAdj[i][j+1] = true;
                    if (i+1 < m) isAdj[i+1][j+1] = true;
                }
                
            }
        }
    }

    for (int i = 0; i < m; i++) {
        string curNum = "";
        bool isValid = false;
        for (int j = 0; j < n; j++) {
            if (engine[i][j] >= '0' && engine[i][j] <= '9') {
                curNum += engine[i][j];
                if (isAdj[i][j]) isValid = true;
            }
            
            if (j == n-1 || engine[i][j] < '0' || engine[i][j] > '9') {
                if (isValid) {
                    sum += stoi(curNum);
                    isValid = false;
                }

                curNum = "";
            }
        }
    }

    return sum;

}

// Part 2
int solve2(vector<vector<char>>& engine) {
    int sum = 0;
    int m = engine.size();
    int n = engine[0].size();

    // gears represents possible positions for the gears
    unordered_map<int, int> gears;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (engine[i][j] == '*') gears[i*m+j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        string curNum = "";
        int numStart = -1;
        int numEnd = -1;
        for (int j = 0; j < n; j++) {
            if (engine[i][j] >= '0' && engine[i][j] <= '9') {
                if (numStart == -1) numStart = j;
                numEnd = j;
                curNum += engine[i][j];
            }
            
            if ((j == n-1 || engine[i][j] < '0' || engine[i][j] > '9') && numStart != -1) {
                for (int k = numStart-1; k <= numEnd+1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        int pos = (i+l)*m + k;
                        if (gears.find(pos) != gears.end()) {
                            if (gears[pos] == 0) {
                                gears[pos] -= stoi(curNum);
                            } else if (gears[pos] < 0) {
                                gears[pos] *= -stoi(curNum);
                            } else if (gears[pos] > 0) {
                                gears.erase(pos);
                            }
                        }
                    }
                }

                numStart = -1;
                numEnd = -1;
                curNum = "";
            }
        }
    }

    for (auto it: gears) {
        if (it.second > 0) sum += it.second;
    }

    return sum;
}

int main() {
    string fileName = "input.txt";
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        return 1;
    }

    vector<string> input;
    string line;

    while (getline(inputFile, line)) {
        input.push_back(line);
    }

    vector<vector<char>> engine;
    for (string s: input) {
        engine.push_back({});
        for (char c: s) {
            engine.back().push_back(c);
        }
    }
    cout << "The solution to part 1 is " << solve1(engine) << endl;
    cout << "The solution to part 2 is " << solve2(engine) << endl;

    return 0;
}