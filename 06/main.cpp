#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

long long solve(vector<long long> times, vector<long long> distances) {
    
    int n = times.size();
    long long ans = 1;

    for (int i = 0; i < n; i++) {
        long long t = times[i];
        long long record = distances[i];

        long long l = 0;
        long long r = t/2;
        long long res = -1;
        

        while (l <= r) {
            long long m = (l+r)/2;

            // binary search on the convex function d=t(x-t)
            // where x is length of race and t is time charging
            if (m*(t-m) > record) {
                r = m - 1;
                res = m;
            } else {
                l = m + 1;
            }
        }

        if (res != -1) {
            ans *= (t-2*res+1);
        }
    }

    return ans;
}

int main() {
    string fileName = "input.txt";
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error opening file!";
        return 1;
    }

    string line;
    vector<long long> times1;
    vector<long long> distances1;

    vector<long long> times2;
    vector<long long> distances2;

    string timeTotal = "";
    string distTotal = "";
    
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string token;
        bool isTime = false;
        
        while (getline(iss, token, ' ')) {
            if (!token.empty()) {
                if (token == "Time:") isTime = true;
                else if (token == "Distance:") isTime = false;
                else {
                    if (isTime) {
                        times1.push_back(stoll(token));
                        timeTotal += token;
                    } else {
                        distances1.push_back(stoll(token));
                        distTotal += token;
                    }
                }
            }
        }
    }

    times2.push_back(stoll(timeTotal));
    distances2.push_back(stoll(distTotal));

    cout << "The solution to part one is " << solve(times1, distances1) << endl;
    cout << "The solution to part one is " << solve(times2, distances2) << endl;

    return 0;
}