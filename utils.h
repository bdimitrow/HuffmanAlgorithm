//
// Created by bozhidar on 12/3/20.
//

#ifndef HUFFMANALGORITHM_UTILS_H
#define HUFFMANALGORITHM_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "tree.h"


std::string readWholeFile() {
    std::string fileOpenName, fileContent;
//    std::cout << "Enter the name of the file you'd like to compress: ";
//    std::cin >> fileOpenName;

    std::ifstream in;
    in.open("testString.txt"/*fileOpenName*/);
    if (in.is_open()) {
        std::ostringstream ss;
        ss << in.rdbuf(); //reading the file into the stream
        fileContent = ss.str();
        in.close();
    } else { std::cout << "Unable to open the file!"; }

    return fileContent;
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

/// saving the binary string to a file
// @TODO how to store the tree??
void saveStringToFile(std::string forStorage, std::string fileName) {
    std::ofstream out;
    out.open("compressed.txt", std::ios::app);
    if (out.is_open()) {
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
        if(str[i] == '0' || str[i] == '1'){
            code += str[i];
        }else {
            result.push_back(std::make_pair(str[i], code));
            code = "";
        }
    }
    return result;
}


#endif //HUFFMANALGORITHM_UTILS_H
