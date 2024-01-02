#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>

enum direction {
    LEFT, RIGHT, DOWN, UP, LR, UD, UNKNOWN
};

direction nextDirection(direction curDirection, char curMirror) {
    switch (curMirror) {
        case '|':
            if (curDirection == LEFT || curDirection == RIGHT) return UD;
            return curDirection;
        case '-':
            if (curDirection == UP || curDirection == DOWN) {
                return LR;
            }
            return curDirection;
        case '/':
            if (curDirection == LEFT) return DOWN;
            if (curDirection == RIGHT) return UP;
            if (curDirection == DOWN) return LEFT;
            if (curDirection == UP) return RIGHT;
        case '\\':
            if (curDirection == LEFT) return UP;
            if (curDirection == RIGHT) return DOWN;
            if (curDirection == DOWN) return RIGHT;
            if (curDirection == UP) return LEFT;
        case '.':
            return curDirection;
        default:
            return UNKNOWN;
    }
}

std::string beamToString(std::tuple<int, int, direction>& beam) {
    std::string beamString = "";

    beamString += std::to_string(std::get<0>(beam));
    beamString += ",";
    beamString += std::to_string(std::get<1>(beam));
    beamString += ",";
    beamString += std::to_string(std::get<2>(beam));

    return beamString;
}

int solve(std::vector<std::string>& mirrors, int startRow, int startCol, direction startDir) {
    int m = mirrors.size();
    int n = mirrors[0].size();
    std::vector<std::vector<bool>> isEnergized(m, std::vector<bool>(n));
    std::queue<std::tuple<int, int, direction>> q; // stores beams and directions
    std::unordered_set<std::string> beamsSeen;

    // set up initial beam
    direction initialDirection = nextDirection(startDir, mirrors[startRow][startCol]);
    if (initialDirection == LR) {
        q.push({startRow, startCol, LEFT});
        q.push({startRow, startCol, RIGHT});
    } else if (initialDirection == UD) {
        q.push({startRow, startCol, UP});
        q.push({startRow, startCol, DOWN});
    } else {
        q.push({startRow, startCol, initialDirection});
    }

    beamsSeen.insert(beamToString(q.front()));

    while (!q.empty()) {
        std::tuple<int, int, direction> curBeam = q.front();
        q.pop();
        int curRow = std::get<0>(curBeam);
        int curCol = std::get<1>(curBeam);
        direction curDirection = std::get<2>(curBeam);

        do {
            isEnergized[curRow][curCol] = true;
            switch (curDirection) {
                case LEFT:
                    curCol--;
                    break;
                case RIGHT:
                    curCol++;
                    break;
                case UP:
                    curRow--;
                    break;
                case DOWN:
                    curRow++;
                    break;
            }
            if (curRow < 0 || curRow >= m || curCol < 0 || curCol >= n) break;
        } while (mirrors[curRow][curCol] == '.');

        if (curRow < 0 || curRow >= m || curCol < 0 || curCol >= n) {
            continue;
        }

        isEnergized[curRow][curCol] = true;
        direction nextDir = nextDirection(curDirection, mirrors[curRow][curCol]);

        if (nextDir == LR) {
            std::tuple<int, int, direction> left = {curRow, curCol, LEFT};
            std::tuple<int, int, direction> right = {curRow, curCol, RIGHT};
            if (!beamsSeen.count(beamToString(left))) {
                q.push(left);
                beamsSeen.insert(beamToString(left));
            }
            if (!beamsSeen.count(beamToString(right))) {
                q.push(right);
                beamsSeen.insert(beamToString(right));
            }
        } else if (nextDir == UD) {
            
            std::tuple<int, int, direction> up = {curRow, curCol, UP};
            std::tuple<int, int, direction> down = {curRow, curCol, DOWN};
            if (!beamsSeen.count(beamToString(up))) {
                q.push(up);
                beamsSeen.insert(beamToString(up));
            }
            if (!beamsSeen.count(beamToString(down))) {
                q.push(down);
                beamsSeen.insert(beamToString(down));
            }
        } else {
            std::tuple<int, int, direction> nextBeam = {curRow, curCol, nextDir};
            if (!beamsSeen.count(beamToString(nextBeam))) {
                q.push(nextBeam);
                beamsSeen.insert(beamToString(nextBeam));
            }
        }
        
    }

    int count = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            count += (isEnergized[i][j]) ? 1 : 0;
        }
    }

    return count;
}

// part two (solve problem starting from any edge)
int solveEveryEdge(std::vector<std::string>& mirrors) {
    int maxEnergy = 0;
    int m = mirrors.size();
    int n = mirrors[0].size();

    for (int i = 0; i < m; i++) {
        maxEnergy = std::max(maxEnergy, solve(mirrors, i, 0, RIGHT));
        maxEnergy = std::max(maxEnergy, solve (mirrors, 0, n-1, LEFT));
    }

    for (int j = 0; j < n; j++) {
        maxEnergy = std::max(maxEnergy, solve(mirrors, 0, j, DOWN));
        maxEnergy = std::max(maxEnergy, solve (mirrors, n-1, j, UP));
    }

    return maxEnergy;
}

int main() {
    std::ifstream inputFile("input.txt");

    std::string line;
    std::vector<std::string> input;

    while (std::getline(inputFile, line)) {
        input.push_back(line);
    }

    std::cout << "The solution to part one is " << solve(input, 0, 0, RIGHT) << std::endl;
    std::cout << "The solution to part two is " << solveEveryEdge(input) << std::endl;


    return 0;
}