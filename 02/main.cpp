#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int solve1(vector<vector<vector<int>>>& cubes) {
    int sum = 0;

    for (int i = 0; i < cubes.size(); i++) {
        int gameId = i+1;
        vector<int> red = cubes[i][0];
        vector<int> blue = cubes[i][1];
        vector<int> green = cubes[i][2];

        bool valid = true;
        for (int j = 0; j < red.size(); j++) {
            if (red[j] > 12 || green[j] > 13 || blue[j] > 14) {
                valid = false;
                continue;
            };
        }

        if (valid) sum += gameId;

    }
    

    return sum;
}

int solve2(vector<vector<vector<int>>>& cubes) {
    int sum = 0;

    for (int i = 0; i < cubes.size(); i++) {
        int gameId = i+1;
        vector<int> red = cubes[i][0];
        vector<int> blue = cubes[i][1];
        vector<int> green = cubes[i][2];
        
        int minRed = 0, minBlue = 0, minGreen = 0;

        bool valid = true;
        for (int j = 0; j < red.size(); j++) {
            minRed = max(minRed, red[j]);
            minGreen = max(minGreen, green[j]);
            minBlue = max(minBlue, blue[j]);
        }

        sum += (minRed * minBlue * minGreen);

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

    vector<vector<vector<int>>> cubes;

    for (string s: input) {
        cubes.push_back({});
        for (int i = 0; i < 3; i++) {
            cubes.back().push_back({});
        }
        int red = 0;
        int green = 0;
        int blue = 0;

        int i = 0;
        string curString = "";
        while (i < s.size()) {
            if (i < s.size()) {
                curString += s[i];
            }
            if (s[i] == ':') {
                i++;
                curString = "";
            } else if (s[i] == ',' || s[i] == ';' || i == s.size()-1) {
                i++;
                int matchIdx = -1;
                if (matchIdx = curString.find("red") != -1) {
                    red = stoi(curString.substr(0, matchIdx+1));
                    curString = "";
                } else if (matchIdx = curString.find("blue") != -1) {
                    blue = stoi(curString.substr(0, matchIdx+1));
                    curString = "";
                } else if (matchIdx = curString.find("green") != -1) {
                    green = stoi(curString.substr(0, matchIdx+1));
                    curString = "";
                }

                if (s[i-1] == ';' || i == s.size()) {
                    curString = "";
                    cubes.back()[0].push_back(red);
                    cubes.back()[1].push_back(blue);
                    cubes.back()[2].push_back(green);
                    red = 0;
                    blue = 0;
                    green = 0;
                    
                    }
            }
            i++;
        }
        
    }

    cout << "The solution to part 1 is " << solve1(cubes) << endl;
    cout << "The solution to part 2 is " << solve2(cubes) << endl;

    return 0;
}