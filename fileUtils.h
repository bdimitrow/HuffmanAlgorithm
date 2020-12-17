//
// Created by bozhidar on 12/3/20.
//

#ifndef HUFFMANALGORITHM_FILEUTILS_H
#define HUFFMANALGORITHM_FILEUTILS_H

#include "tree.h"
#include "stringUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


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
    std::string buffer, codePart, wholeContent, binary = "01";
    std::ifstream in;
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


void readFileForDecimalDecompress(const std::string &fileName, std::string &bintree, std::string &code) {
    std::string lastSize, buffer, codePart, wholeContent, decimal = " 0123456789", codeNumbers, sinlgeNum;

    std::ifstream in;
    in.open(fileName);
    if (in.is_open()) {
        std::ostringstream ss;
        ss << in.rdbuf();
        wholeContent = ss.str();
        in.close();

        int found = wholeContent.find_last_not_of(decimal);
        if (found != std::string::npos) {
            codeNumbers = wholeContent.substr(found + 1);
            bintree = wholeContent.erase(found + 1);
            lastSize = bintree.substr(0, 1);
            bintree = bintree.substr(1);
        }
        while (codeNumbers != "") {
            int pos = codeNumbers.find(' ');
            sinlgeNum = codeNumbers.substr(0, pos);
            codeNumbers = codeNumbers.erase(0, pos + 1);
            if (codeNumbers != "") {
                code += decimalToBinary(sinlgeNum);
            }
        }
        sinlgeNum = decimalToBinary(sinlgeNum);
        if (sinlgeNum.size() > (lastSize[0] - '0')) {
            sinlgeNum = sinlgeNum.substr(8 - (lastSize[0] - '0'));
        }
        code += sinlgeNum;

    } else {
        std::cout << "Unable to open the file\n";
    }
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

void compareSizes(const std::string &originalContent, const std::string &encoded) {
    std::cout << "The original file size is " << 8 * originalContent.size() << " bits and the compressed file will be "
              << encoded.size() << " bites. That means the compresssed file is "
              << encoded.size() / ((float) 8 * originalContent.size() / 100) << "% of the original one!\n";
}

#endif //HUFFMANALGORITHM_FILEUTILS_H
