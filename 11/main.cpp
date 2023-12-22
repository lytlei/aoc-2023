#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

long long solve(vector<vector<char>>& image, int expandFactor) {
    long long sum = 0;
    int m = image.size();
    int n = image[0].size();
    

    vector<pair<int, int>> galaxies;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (image[i][j] == '#') {
                galaxies.push_back({i, j});
            }
        }
    }

    vector<bool> expandRow(m); // expandRow[i] is true if row i needs to be expanded
    vector<bool> expandCol(n); // expandCol[j] is true if column j needs to be expanded

    for (int i = 0; i < m; i++) {
        bool isEmpty = true;
        for (char c: image[i]) {
            if (c == '#') {
                isEmpty = false;
                break;
            }
        }
        expandRow[i] = isEmpty;
    }

    for (int j = 0; j < n; j++) {
        bool isEmpty = true;
        for (int i = 0; i < m; i++) {
            if (image[i][j] == '#') {
                isEmpty = false;
                break;
            }
        }
        expandCol[j] = isEmpty;
    }

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i+1; j < galaxies.size(); j++) {
            int numRows = 0; // num of rows between two galaxies we are finding dist for
            int numCols = 0; // num of cols between two galaxies we are finding dist for

            int minRow = min(galaxies[i].first, galaxies[j].first);
            int maxRow = max(galaxies[i].first, galaxies[j].first);

            int minCol = min(galaxies[i].second, galaxies[j].second);
            int maxCol = max(galaxies[i].second, galaxies[j].second);

            for (int k = minRow+1; k < maxRow; k++) {
                if (expandRow[k]) numRows++;
            }

            for (int k = minCol+1; k < maxCol; k++) {
                if (expandCol[k]) numCols++;
            }

            // here we find distance between two galaxies while taking into account the expansion
            sum += abs(galaxies[i].first-galaxies[j].first) + (numRows * (expandFactor-1));
            sum += abs(galaxies[i].second-galaxies[j].second) + (numCols * (expandFactor-1));
        }
    }

    return sum;
}


int main() {
    ifstream inputFile("input.txt");

    string line;
    vector<vector<char>> image;

    while (getline(inputFile, line)) {
        image.push_back({});
        for (char c: line) {
            image.back().push_back(c);
        }
    }

    cout << "The solution to part one is " << solve(image, 2) << endl;
    cout << "The solution to part two is " << solve(image, 1000000) << endl;

    return 0;
}