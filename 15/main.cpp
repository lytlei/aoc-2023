#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <sstream>

// part one
long long solve1(std::vector<std::string>& seq) {
    long long sum = 0;
    for (std::string s: seq) {
        int hash = 0;
        for (char c: s) {
            hash += c;
            hash *= 17;
            hash %= 256;
        }
        sum += hash;
    }

    return sum;
}

// part two
long long solve2(std::vector<std::string>& label, std::vector<char>& op, std::vector<int>& focalLength) {
    // This solution makes use of a vector of linked lists to represent boxes
    // and the order of labels in those boxes.
    // We then use a map to keep track of the focal length of a label as well as a pointer to its iterator
    // so that we can store the appropriate values to solve the problem.
    std::vector<std::list<std::string>> boxes(256);
    std::unordered_map<std::string, std::pair<int, std::list<std::string>::iterator>> map;
    int sum = 0;

    for (int i = 0; i < label.size(); i++) {
        if (op[i] == '=') {
            if (map.find(label[i]) != map.end()) { // label exists
                map[label[i]].first = focalLength[i];
            } else { // label doesn't exist
                std::vector<std::string> l = {label[i]};
                boxes[solve1(l)].push_back(label[i]);
                map[label[i]] = {focalLength[i], --boxes[solve1(l)].end()};
            }
        } else if (op[i] == '-') {
            if (map.find(label[i]) == map.end()) continue;
            std::vector<std::string> l = {label[i]};
            boxes[solve1(l)].erase(map[label[i]].second);
            map.erase(label[i]);
        }
    }

    for (int i = 0; i < boxes.size(); i++) {
        std::list<std::string> box = boxes[i];
        std::list<std::string>::iterator curr = box.begin();

        for (int j = 0; j < box.size(); j++) {
            sum += (1+i)*(1+j)*(map[*curr].first); // calculation for focusing power
            curr++;
        }
    }

    return sum;
}

int main() {
    std::ifstream inputFile("input.txt");

    std::string input;
    std::getline(inputFile, input);
    std::vector<std::string> seq;

    std::istringstream inputStream(input);
    std::string token;

    while (std::getline(inputStream, token, ',')) {
        seq.push_back(token);
    }

    std::vector<std::string> label;
    std::vector<char> op;
    std::vector<int> focalLength;

    for (std::string s: seq) {
        int pos;
        if ((pos = s.find("=")) != -1) {
            label.push_back(s.substr(0, pos));
            op.push_back('=');
            focalLength.push_back(stoi(s.substr(pos+1)));
        } else if ((pos = s.find("-")) != -1) {
            label.push_back(s.substr(0, pos));
            op.push_back('-');
            focalLength.push_back(-1);
        }
    }

    std::cout << "The solution to part one is " << solve1(seq) << std::endl;
    std::cout << "The solution to part two is " << solve2(label, op, focalLength) << std::endl;

    return 0;
}