#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

bool find(pair<char, char>& pair, char match) {
    if (pair.first == match || pair.second == match) return true;
    return false;
}

void solve(vector<vector<char>>& pipes) {
    int m = pipes.size();
    int n = pipes[0].size();
    int count = 0;
    pair<int, int> startPos;
    pair<int, int> currPos;
    vector<vector<bool>> visited(m, vector<bool>(n));

    // Map to determine what sides a piece connects to
    unordered_map<char, pair<char, char>> connects;
    connects['|'] = {'N', 'S'};
    connects['-'] = {'E', 'W'};
    connects['L'] = {'N', 'E'};
    connects['J'] = {'N', 'W'};
    connects['7'] = {'S', 'W'};
    connects['F'] = {'S', 'E'};
    connects['.'] = {' ', ' '};

    // travel through pipes
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (pipes[i][j] == 'S') {
                visited[i][j] = true;
                startPos = {i, j};
                if (i-1 >= 0 && find(connects[pipes[i-1][j]], 'S')) currPos = {i-1, j};
                if (i+1 < m && find(connects[pipes[i+1][j]], 'N')) currPos = {i+1, j};
                if (j-1 >= 0 && find(connects[pipes[i][j-1]], 'E')) currPos = {i, j-1};
                if (j+1 < n && find(connects[pipes[i][j+1]], 'W')) currPos = {i, j+1};
                count = 1;
                goto jump;
            }
        }
    }

    jump:
        // Part one
        while (pipes[currPos.first][currPos.second] != 'S') {
            int i = currPos.first;
            int j = currPos.second;
            visited[i][j] = true;

            if (i-1 >= 0 && !visited[i-1][j] && find(connects[pipes[i][j]], 'N')) {
                if (find(connects[pipes[i-1][j]], 'S')) {
                    currPos = {i-1, j};
                    count++;
                }
            }
            if (i+1 < m && !visited[i+1][j] && find(connects[pipes[i][j]], 'S')) {
                if (find(connects[pipes[i+1][j]], 'N')) {
                    currPos = {i+1, j};
                    count++;
                }
            }
            if (j-1 >= 0 && !visited[i][j-1] && find(connects[pipes[i][j]], 'W')) {
                if (find(connects[pipes[i][j-1]], 'E')) {
                    currPos = {i, j-1};
                    count++;
                }
            }
            if (j+1 < n && !visited[i][j+1] && find(connects[pipes[i][j]], 'E')) {
                if (find(connects[pipes[i][j+1]], 'W')) {
                    currPos = {i, j+1};
                    count++;
                }
            }

            if (currPos.first == i && currPos.second == j) {
                count++;
                break;
            }
        }

        cout << "The solution to part one is " << count / 2 << endl;

    return;
}

int main() {
    ifstream inputFile("input.txt");

    string line;
    vector<vector<char>> pipes;

    while (getline(inputFile, line)) {
        pipes.push_back({});

        for (char c: line) {
            pipes.back().push_back(c);
        }
    }

    solve(pipes);

    return 0;
}