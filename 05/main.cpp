#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <limits.h>
#include <algorithm>

using namespace std;

// Part one
long long solve1(vector<long long>& seeds, vector<vector<vector<long long>>>& maps) {
    long long minLoc = LLONG_MAX;

    vector<vector<tuple<long long, long long, long long>>> mapSrcRange(maps.size());

    for (vector<vector<long long>> map: maps) {
        mapSrcRange.push_back({});

        for (vector<long long> srcToCat: map) {
            mapSrcRange.back().push_back({srcToCat[1], srcToCat[1]+srcToCat[2]-1, srcToCat[0]});
        }
        sort(mapSrcRange.back().begin(), mapSrcRange.back().end());
    }

    for (long long seed: seeds) {
        long long curLoc = seed;

        for (vector<tuple<long long, long long, long long>> map: mapSrcRange) {
            int l = 0;
            int r = map.size()-1;
            int res = -1;

            while (l <= r) {
                int m = (l+r)/2;
                if (get<0>(map[m]) <= curLoc) {
                    res = m;
                    l = m+1;
                } else {
                    r = m-1;
                }
            }

            if (res != -1) {
                if (curLoc <= get<1>(map[res])) {
                    curLoc = get<2>(map[res]) + (curLoc - get<0>(map[res]));
                }
            }
        }

        minLoc = min(minLoc, curLoc);

    }

    return minLoc;
}

int main() {
    string fileName = "input.txt";
    ifstream fileInput(fileName);

    string line;
    vector<long long> seeds;
    vector<vector<vector<long long>>> maps;

    getline(fileInput, line);
    line = line.substr(line.find(":")+2);
    line += " ";
    int pos = 0;
    string delimiter = " ";
    string token;
    while ((pos = line.find(delimiter)) != -1) {
        token = line.substr(0, pos);
        seeds.push_back(stoll(token));
        line.erase(0, pos+delimiter.size());
    }

    while (getline(fileInput, line)) {
        if (line == "") {
            getline(fileInput, line);
            maps.push_back({});
            continue;
        }
        line += " ";
        vector<long long> curLine = {};
        
        
        while ((pos = line.find(" ")) != -1) {
            token = line.substr(0, pos);
            curLine.push_back(stoll(token));
            line.erase(0, pos+delimiter.size());
        }
        maps.back().push_back(curLine);

    }

    cout << "The solution to part one is " << solve1(seeds, maps) << endl;


    return 0;
}