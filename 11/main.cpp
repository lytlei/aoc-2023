#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<vector<char>> expandImage(vector<vector<char>>& image) {
    int m = image.size();
    int n = image[0].size();
    int mExpand = m;
    int nExpand = n;

    unordered_set<int> emptyRows;
    unordered_set<int> emptyCols;

    for (int i = 0; i < m; i++) {
        bool isEmpty = true;
        for (char c: image[i]) {
            if (c == '#') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            mExpand++;
            emptyRows.insert(mExpand-m+i);
        }
    }

    for (int j = 0; j < n; j++) {
        bool isEmpty = true;
        for (int i = 0; i < m; i++) {
            if (image[i][j] == '#') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            nExpand++;
            emptyCols.insert(nExpand-n+j);
        }
    }

    vector<vector<char>> expandedImage(mExpand, vector<char>(nExpand));
    int curRow = 0;

    for (int i = 0; i < mExpand; i++) {
        int curCol = 0;
        bool emptyRow = (emptyRows.find(i) != emptyRows.end());
        for (int j = 0; j < nExpand; j++) {
            bool emptyCol = (emptyCols.find(j) != emptyCols.end());
            if (emptyRow) {
                expandedImage[i][j] = '.';
            } else if (emptyCol) {
                expandedImage[i][j] = '.';
            } else {
                expandedImage[i][j] = image[curRow][curCol];
                curCol++;
            }
        }

        if (!emptyRow) curRow++;
    }


    return expandedImage;
}

int solve(vector<vector<char>>& image) {
    int sum = 0;

    vector<vector<char>> expandedImage = expandImage(image);
    int m = expandedImage.size();
    int n = expandedImage[0].size();
    

    vector<pair<int, int>> galaxies;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (expandedImage[i][j] == '#') {
                galaxies.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i+1; j < galaxies.size(); j++) {
            sum += abs(galaxies[i].first-galaxies[j].first);
            sum += abs(galaxies[i].second-galaxies[j].second);
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

    cout << "The solution to part one is " << solve(image) << endl;


    return 0;
}