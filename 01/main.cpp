#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int solve(vector<string> input) {
    int sum = 0;

    for (string s: input) {
        char first = 0;
        char last = 0;

        for (char c: s) {
            if (c >= '0' && c <= '9') {
                if (!first) {
                    first = c;
                }

                last = c;
            }
        }

        sum += (first-'0')*10 + (last-'0'); // convert digits to num
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

    cout << "The solution is " << solve(input) << endl;

    return 0;
}