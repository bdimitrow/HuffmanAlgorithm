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

/**
 * @file
 * @fn std::string encodeString(std::string realContent, std::vector<std::pair<char, std::string>> &codePairs)
 * This function accepts string and vector of pairs(char, string) as arguments. The string in the pair is the binary
 * code for the char. The result is a binary sequence of the real content.
 * @param std::string realContent
 * @param std::vector<std::pair<char, std::string>> &codePairs
 * @return std::string binarySequence
 */
std::string encodeString(std::string realContent, std::vector<std::pair<char, std::string>> &codePairs) {
    std::string binarySequence;
    int i = 0;
    while (realContent[i]) {
        for (const auto &el : codePairs) {
            if (realContent[i] == el.first) {
                binarySequence += el.second;
            }
        }
        ++i;
    }

    return binarySequence;
}

/**
 * @fn std::string vectorCodePairsToString(std::vector<std::pair<char, std::string>> &codePairs)
 * Transforming vector of pairs into a string.
 * @param std::vector<std::pair<char, std::string>> codePairs
 * @return std::string pairStr
 */
std::string vectorCodePairsToString(std::vector<std::pair<char, std::string>> &codePairs) {
    std::string pairStr;
    for (const auto &el : codePairs) {
        pairStr += el.second;
        pairStr += '`';
        pairStr += el.first;
        pairStr += '`';
    }

    return pairStr;
}

/**
 * @fn std::vector<std::pair<char, std::string>> stringToVectorCodePairs(std::string pairStr)
 * Accepting a string as argument and transforms it into a vector of pairs(char-binary sequence).
 * @param std::string pairStr
 * @return std::vector<std::pair<char, std::string>> codePairs
 */
std::vector<std::pair<char, std::string>> stringToVectorCodePairs(std::string pairStr) {
    std::vector<std::pair<char, std::string>> codePairs;
    std::string code;
    for (int i = 0; i < pairStr.size(); ++i) {
        // added in order to be able to encode 0s and 1s;
        if (pairStr[i] == '`' && pairStr[i + 2]) {
            codePairs.push_back(std::make_pair(pairStr[i + 1], code));
            code = "";
            i += 2;
        } else {
            code += pairStr[i];
        }
    }

    return codePairs;
}

/**
 * @fn std::string binaryToDecimal(std::string binary)
 * Transforming a string(storing binary number) into a string(storing a decimal number).
 * @example "01111" -> "15"
 * @param std::string binary
 * @return std::string decimal
 */
std::string binaryToDecimal(std::string binary) {
    std::string decimal;
    int number = 0;
    for (int i = binary.size() - 1, power = 0; i >= 0; --i, ++power) {
        if (binary[i] == '1') {
            number += pow(2, power);
        }
    }
    while (number) {
        decimal += (number % 10 + '0');
        number /= 10;
    }
    std::reverse(decimal.begin(), decimal.end());

    return decimal;
}

/**
 * @fn std::string decimalToBinary(const std::string &binary)
 * Transforming a string(storing a decimal number) into a string(storing a binary number - 8 bits long).
 * @example "15" -> "00001111"
 * @param std::string decimal
 * @result std::string binary
 */
std::string decimalToBinary(const std::string &binary) {
    int number = 0;
    for (auto character : binary) {
        number = number * 10 + (character - '0');
    }
    std::string decimal = std::bitset<8>(number).to_string();

    return decimal;
}

/**
 * @fn std::string contentAsNumbers(const std::string &binaryContent)
 * Takes a string consisting just of 0s and 1s. Splits the string into substrings of length == 8 and transforms this
 * 8 bits binary number into decimal ones. Returns them as a string.
 * @param std::string binaryContent
 * @return std::string numericContent
 */
std::string contentAsNumbers(const std::string &binaryContent) {
    int arrSize = binaryContent.size() / 8 + 1;
    std::string arrBinaryNums[arrSize], numericContent;

    for (int i = 0, j = 0; i < binaryContent.size(); i += 8, ++j) {
        std::string subString = binaryContent.substr(i, 8);
        arrBinaryNums[j] = subString;
    }

    for (const auto &el :arrBinaryNums) {
        numericContent += binaryToDecimal(el) + " ";
    }

    return numericContent;
}

#endif //HUFFMANALGORITHM_STRINGUTILS_H
