#define TYPE_ONE 1
#define TYPE_TWO 2

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Part one
bool cmp1(pair<string, int>& a, pair<string, int>& b) {
    unordered_map<char, int> aChars;
    unordered_map<char, int> bChars;
    unordered_map<char, int> order;

    order['2'] = 0;
    order['3'] = 1;
    order['4'] = 2;
    order['5'] = 3;
    order['6'] = 4;
    order['7'] = 5;
    order['8'] = 6;
    order['9'] = 7;
    order['T'] = 8;
    order['J'] = 9;
    order['Q'] = 10;
    order['K'] = 11;
    order['A'] = 12;

    for (char c: a.first) {
        aChars[c]++;
    }

    for (char c: b.first) {
        bChars[c]++;
    }

    vector<int> aCounts;
    vector<int> bCounts;

    for (auto it: aChars) aCounts.push_back(it.second);
    for (auto it: bChars) bCounts.push_back(it.second);

    sort(aCounts.begin(), aCounts.end(), greater<>());
    sort(bCounts.begin(), bCounts.end(), greater<>());

    for (int i = 0; i < aCounts.size(); i++) {
        if (aCounts[i] > bCounts[i]) return false;
        else if (aCounts[i] < bCounts[i]) return true; 
    }

    for (int i = 0; i < a.first.size(); i++) {
        if (order[a.first[i]] < order[b.first[i]]) return true;
        else if (order[a.first[i]] > order[b.first[i]]) return false;
    }

    return false;
}

// Part two
bool cmp2(pair<string, int>& a, pair<string, int>& b) {
    unordered_map<char, int> aChars;
    unordered_map<char, int> bChars;
    unordered_map<char, int> order;

    order['J'] = -1;
    order['2'] = 0;
    order['3'] = 1;
    order['4'] = 2;
    order['5'] = 3;
    order['6'] = 4;
    order['7'] = 5;
    order['8'] = 6;
    order['9'] = 7;
    order['T'] = 8;
    order['Q'] = 10;
    order['K'] = 11;
    order['A'] = 12;

    for (char c: a.first) {
        aChars[c]++;
    }

    for (char c: b.first) {
        bChars[c]++;
    }

    vector<int> aCounts = {0};
    vector<int> bCounts = {0};

    int aJokerCount = 0;
    int bJokerCount = 0;

    for (auto it: aChars) {
        if (it.first != 'J') {
            aCounts.push_back(it.second);
        } else {
            aJokerCount = it.second;
        }
        
    }
    for (auto it: bChars) {
        if (it.first != 'J') {
            bCounts.push_back(it.second);
        } else {
            bJokerCount = it.second;
        }
    }

    sort(aCounts.begin(), aCounts.end(), greater<>());
    sort(bCounts.begin(), bCounts.end(), greater<>());
    
    aCounts[0] += aJokerCount;
    bCounts[0] += bJokerCount;

    for (int i = 0; i < aCounts.size(); i++) {
        if (aCounts[i] > bCounts[i]) return false;
        else if (aCounts[i] < bCounts[i]) return true; 
    }

    for (int i = 0; i < a.first.size(); i++) {
        if (order[a.first[i]] < order[b.first[i]]) return true;
        else if (order[a.first[i]] > order[b.first[i]]) return false;
    }

    return false;
}

// main algorithm
long long solve(vector<string>& cards, vector<int>& bids, int type) {
    int n = cards.size();
    vector<pair<string, int>> hand;

    for (int i = 0; i < n; i++) {
        hand.push_back({cards[i], bids[i]});
    }

    if (type == TYPE_ONE) {
        sort(hand.begin(), hand.end(), cmp1);
    } else if (type == TYPE_TWO) {
        sort(hand.begin(), hand.end(), cmp2);
    }
    

    int res = 0;

    for (int i = 0; i < n; i++) {
        res += (i+1) * hand[i].second;
    }

    return res;
}

int main() {
    ifstream fileInput("input.txt");

    if (!fileInput.is_open()) {
        cout << "Error opening file!";
        return 1;
    }

    string line;
    vector<string> cards;
    vector<int> bids;

    while (getline(fileInput, line)) {
        int pos = line.find(" ");
        cards.push_back(line.substr(0, pos));
        bids.push_back(stoi(line.substr(pos+1)));
    }

    cout << "The solution to part one is " << solve(cards, bids, TYPE_ONE) << endl;
    cout << "The solution to part one is " << solve(cards, bids, TYPE_TWO) << endl;

    return 0;
}