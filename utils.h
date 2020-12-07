//
// Created by bozhidar on 12/3/20.
//

#ifndef HUFFMANALGORITHM_UTILS_H
#define HUFFMANALGORITHM_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "tree.h"


std::string readWholeFile(const std::string &fileOpenName) {
    std::string fileContent;

    std::ifstream in;
    in.open(fileOpenName);
    if (in.is_open()) {
        std::ostringstream ss;
        ss << in.rdbuf(); //reading the file into the stream
        fileContent = ss.str();
        in.close();
    } else {
        std::cout << "Unable to open the file!\n";
    }

    return fileContent;
}

void readFileForDecompress(const std::string &fileName, std::string &bintree, std::string &code) {
    std::ifstream in;
    std::string buffer, codePart, wholeContent;
    std::string binary = "01";
    in.open(fileName);
    if (in.is_open()) {
        std::ostringstream ss;
        ss << in.rdbuf();
        wholeContent = ss.str();
        in.close();

        int found = wholeContent.find_last_not_of(binary);
        if (found != std::string::npos) {
            code = wholeContent.substr(found + 1);
            bintree = wholeContent.erase(found + 1);
        }
    } else {
        std::cout << "Unable to open the file\n";
    }
}

/// converting a sentence to a binary sentence
std::string convertStringToBinary(std::string realContent, std::vector<std::pair<char, std::string>> &codePairs) {
    std::string output;
    int i = 0;
    while (realContent[i]) {
        for (auto el : codePairs) {
            if (realContent[i] == el.first) {
                output += el.second;
            }
        }
        ++i;
    }
    return output;
}

void saveStringToFile(const std::string &fileName, const std::string &forStorage) {
    std::ofstream out;
    out.open(fileName, std::ios::trunc);
    if (out.is_open()) {
        out << forStorage;
        out.close();
    } else {
        std::cout << "Unable to open the file!\n";
    }
}

/// saving the binary string to a file
void
saveTreeAndBinaryToFile(const std::string &encodedTree, const std::string &forStorage, const std::string &fileName) {
    std::ofstream out;
    out.open(fileName, std::ios::trunc);
    if (out.is_open()) {
        out << encodedTree;
        out << "\n";
        out << forStorage;
        out.close();
    } else {
        std::cout << "Unable to open the file! \n";
    }
}

std::string vectorCodePairsToString(std::vector<std::pair<char, std::string>> &codePairs) {
    std::string result;
    for (auto el : codePairs) {
        result += el.second;
        result += el.first;
    }
    return result;
}

std::vector<std::pair<char, std::string>> stringToVectorCodePairs(std::string str) {
    std::vector<std::pair<char, std::string>> result;
    std::string code;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '0' || str[i] == '1') {
            code += str[i];
        } else {
            result.push_back(std::make_pair(str[i], code));
            code = "";
        }
    }
    return result;
}


#endif //HUFFMANALGORITHM_UTILS_H
