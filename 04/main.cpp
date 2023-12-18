#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <numeric>

using namespace std;

// Part one
int solve1(vector<vector<int>>& winningNums, vector<vector<int>>& nums) {
    int sum = 0;

    for (int i = 0; i < winningNums.size(); i++) {
        vector<int> winCard = winningNums[i];
        vector<int> yourCard = nums[i];

        unordered_map<int, int> winNums;
        for (int winNum: winCard) {
            winNums[winNum] = 1;
        }

        int points = 0;

        for (int num: yourCard) {
            if (winNums[num]) points = (points == 0) ? 1 : points * 2;
        }

        sum += points;
    }

    return sum;
}

// Part two
int solve2(vector<vector<int>>& winningNums, vector<vector<int>>& nums) {
    vector<int> copies(nums.size(), 1);

    for (int i = 0; i < winningNums.size(); i++) {
        vector<int> winCard = winningNums[i];
        vector<int> yourCard = nums[i];

        unordered_map<int, int> winNums;
        for (int winNum: winCard) {
            winNums[winNum] = 1;
        }

        int count = 0;

        for (int num: yourCard) {
            if (winNums[num]) count++;
        }
        
        for (int j = 1; j <= count; j++) {
            copies[i+j] += copies[i];
        }

    }

    return accumulate(copies.begin(), copies.end(), 0);
}

int main() {
    string fileName = "input.txt";
    ifstream inputfile(fileName);

    if (!inputfile.is_open()) {
        cout << "Error opening file!";
        return 1;
    }

    string line;
    vector<vector<int>> winningNums;
    vector<vector<int>> nums;

    while (getline(inputfile, line)) {
        string delim = " ";
        string token;
        int pos = 0;
        line = line.substr(line.find(":")+2);
        line += " ";
        bool win = true;

        winningNums.push_back({});
        nums.push_back({});

        while ((pos = line.find(delim)) != -1) {
            token = line.substr(0, pos);

            if (token == "|") win = false;
            else if (token != "") {
                if (win) winningNums.back().push_back(stoi(token));
                else nums.back().push_back(stoi(token));
            }

            line.erase(0, pos + delim.size());
        }
    }

    cout << "The solution to part one is " << solve1(winningNums, nums) << endl;
    cout << "The solution to part two is " << solve2(winningNums, nums) << endl;

    return 0;
}