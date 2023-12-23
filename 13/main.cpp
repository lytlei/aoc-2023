#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

long long countReflection(vector<vector<string>>& mirrors) {
    long long count = 0;

    for (vector<string>& mirror: mirrors) {
        for (int i = 1; i < mirror.size(); i++) {
            if (mirror[i] == mirror[i-1]) {
                int l = i-2;
                int r = i+1;
                bool isReflect = true;

                while (l >= 0 && r < mirror.size()) {
                    if (mirror[l] != mirror[r]) {
                        isReflect = false;
                        break;
                    }
                    l--;
                    r++;
                }

                if (isReflect) {
                    count += i;
                }
            }
        }
    }

    return count;
}

long long solve(vector<vector<string>>& mirrors) {
    vector<vector<string>> horizontalMirrors;
    
    for (vector<string>& mirror: mirrors) {
        horizontalMirrors.push_back({});
        
        for (int j = 0; j < mirror[0].size(); j++) {
            string curLine = "";
            for (int i = 0; i < mirror.size(); i++) {
                curLine += mirror[i][j];
            }
            horizontalMirrors.back().push_back(curLine);
        }
    }


    return 100 * countReflection(mirrors) + countReflection(horizontalMirrors);
}

int main() {
    ifstream inputFile("input.txt");

    string line;
    vector<vector<string>> mirrors;
    mirrors.push_back({});

    while (getline(inputFile, line)) {
        if (line == "") {
            mirrors.push_back({});
        } else {
            mirrors.back().push_back(line);
        }
    }

    cout << "The solution to part one is " << solve(mirrors) << endl;

    return 0;
}