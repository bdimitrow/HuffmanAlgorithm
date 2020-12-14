//
// Created by bozhidar on 12/12/20.
//

#ifndef HUFFMANALGORITHM_STRINGUTILS_H
#define HUFFMANALGORITHM_STRINGUTILS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <bitset>

/// converting a sentence to a binary sentence
std::string encodeString(std::string realContent, std::vector<std::pair<char, std::string>> &codePairs) {
    std::string output;
    int i = 0;
    while (realContent[i]) {
        for (const auto &el : codePairs) {
            if (realContent[i] == el.first) {
                output += el.second;
            }
        }
        ++i;
    }
    return output;
}

std::string vectorCodePairsToString(std::vector<std::pair<char, std::string>> &codePairs) {
    std::string result;
    for (const auto &el : codePairs) {
        result += el.second;
        result += '`';
        result += el.first;
        result += '`';
    }
    return result;
}

std::vector<std::pair<char, std::string>> stringToVectorCodePairs(std::string str) {
    std::vector<std::pair<char, std::string>> result;
    std::string code;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '`' && str[i + 2]) {
            result.push_back(std::make_pair(str[i + 1], code));
            code = "";
            i += 2;
        } else {
            code += str[i];
        }
    }
    return result;
}

std::string binaryToNumber(std::string binary) {
    std::string result;
    int num = 0;
    for (int i = binary.size() - 1, power = 0; i >= 0; --i, ++power) {
        if (binary[i] == '1') {
            num += pow(2, power);
        }
    }
    while (num) {
        result += num % 10 + '0';
        num /= 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string numToBinaryEightBits(const std::string &num) {
    int number = 0;
    for (auto el : num) {
        number = number * 10 + (el - '0');
    }
    std::string result = std::bitset<8>(number).to_string();
    return result;
}

#endif //HUFFMANALGORITHM_STRINGUTILS_H
