#define FORWARD 0
#define BACKWARD 1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// recursive solution to extrapolate sequences
int extrapolate(vector<int>& nums, int type) {
    bool zeros = true;

    for (int num: nums) {
        if (num != 0) {
            zeros = false;
            break;
        }
    }
 
    if (zeros) {
        return 0;
    }

    vector<int> nextSeq;

    for (int i = 1; i < nums.size(); i++) {
        nextSeq.push_back(nums[i] - nums[i-1]);
    }

    if (type == FORWARD) {
        return nums.back() + extrapolate(nextSeq, type);
    } else {
        return nums.front() - extrapolate(nextSeq, type);
    }

}

int solve(vector<vector<int>>& nums, int type) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += extrapolate(nums[i], type);
    }

    return sum;
}

int main() {
    string fileName = "input.txt";
    ifstream inputFile(fileName);

    string line;

    vector<vector<int>> nums;

    while (getline(inputFile, line)) {
        line += " ";

        int pos;
        nums.push_back({});

        while ((pos = line.find(" ")) != -1) {
            nums.back().push_back(stoi(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
    }

    cout << "The solution to part one is " << solve(nums, FORWARD) << endl;
    cout << "The solution to part two is " << solve(nums, BACKWARD) << endl;

    return 0;
}