#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <numeric>

using namespace std;

// Part one
int solve1(string seq, unordered_map<string, pair<string, string>>& network) {
    int n = seq.length();
    string curr = "AAA";
    int count = 0;


    while (curr != "ZZZ") {
        if (seq[count % n] == 'L') {
            curr = network[curr].first;
        } else if (seq[count % n] == 'R') {
            curr = network[curr].second;
        }
        count++;
    }

    return count;
}

// Part two
long long gcd(long long a, long long b) {
    if (b == 0) return a; 
    return gcd(b, a % b); 
} 

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b; 
}

long long solve2(string seq, unordered_map<string, pair<string, string>>& network) {
    vector<int> firstAToZ;
    int n = seq.length();

    for (auto& it: network) {
        if (it.first.back() == 'A') {
            string curr = it.first;
            int count = 0;

            // find first time any node ending with 'A' reaches a node ending with 'Z'
            while (curr.back() != 'Z') {
                if (seq[count % n] == 'L') {
                    curr = network[curr].first;
                } else if (seq[count % n] == 'R') {
                    curr = network[curr].second;
                }
                count++;
            }
            firstAToZ.push_back(count);
        }
    }

    long long res = 1;
    // find LCM of all counts from 'A' to 'Z'
    for (long long a: firstAToZ) {
        res = lcm(res, a);
    }

    return res;
}

int main() {
    ifstream inputFile("input.txt");

    string line;

    getline(inputFile, line);

    string seq = line;

    getline(inputFile, line);

    unordered_map<string, pair<string, string>> network;

    while (getline(inputFile, line)) {
        string src = line.substr(0, line.find(' '));
        line.erase(0, line.find('(')+1);
        string left = line.substr(0, line.find(','));
        line.erase(0, line.find(',')+2);
        string right = line.substr(0, line.find(')'));

        network[src] = {left, right};
    }

    cout << "The solution to part one is " << solve1(seq, network) << endl;
    cout << "The solution to part two is " << solve2(seq, network) << endl;

    return 0;
}