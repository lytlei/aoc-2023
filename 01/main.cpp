#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

// Part 1
int solve1(vector<string>& input) {
    int sum = 0;

    for (string s: input) {
        int first = 0;
        int last = 0;

        // iterate from beginning to find first number
        for (char c: s) {
            if (c >= '0' && c <= '9') {
                first = c-'0';
                break;
            }
        }

        // iterate from end to find last number
        for (int i = s.size()-1; i >= 0; i--) {
            if (s[i] >= '0' && s[i] <= '9') {
                last = s[i]-'0';
                break;
            }
        }

        sum += (first*10 + last); // convert digits to num
    }

    return sum;

}

// Part 2
int solve2(vector<string>& input) {
    // map number string to number char
    unordered_map<string, int> store;
    store["one"] = 1;
    store["two"] = 2;
    store["three"] = 3;
    store["four"] = 4;
    store["five"] = 5;
    store["six"] = 6;
    store["seven"] = 7;
    store["eight"] = 8;
    store["nine"] = 9;

    int sum = 0;

    for (string s: input) {
        int first = 0;
        int last = 0;
        int firstIndex = input.size();
        int lastIndex = -1;

        // iterate from beginning to find first number
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '1' && s[i] <= '9') {
                first = s[i]-'0';
                firstIndex = i;
                break;
            }
        }

        // iterate from end to find last number
        for (int i = s.size()-1; i >= 0; i--) {
            if (s[i] >= '1' && s[i] <= '9') {
                last = s[i]-'0';
                lastIndex = i;
                break;
            }
        }

        // search for numbers as strings in s
        for (auto& it: store) {
            string toMatch = it.first;
            int matchL = s.find(toMatch);
            int matchR = s.rfind(toMatch);

            if (matchL != -1 && firstIndex > matchL) {
                firstIndex = matchL;
                first = it.second;
            }

            if (matchR != -1 && lastIndex < matchR) {
                lastIndex = matchR;
                last = it.second;
            }
        }

        sum += (first*10 + last); // convert digits to num
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

    cout << "The solution to part 1 is " << solve1(input) << endl;
    cout << "The solution to part 2 is " << solve2(input) << endl;

    return 0;
}