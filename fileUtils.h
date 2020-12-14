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
    std::ifstream in;
    std::string buffer, codePart, wholeContent, binary = "01";
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



void readFileForDebugDecode(const std::string &fileName, std::string &bintree, std::string &code) {
    std::ifstream in;
    std::string buffer, codePart, wholeContent, decimal = " 0123456789", codeNumbers, sinlgeNum;
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
        }
        // @TODO remove leading zeros from last number
        while (codeNumbers != "") {
            int pos = codeNumbers.find(' ');
            sinlgeNum = codeNumbers.substr(0, pos);
            codeNumbers = codeNumbers.erase(0, pos + 1);
            if (codeNumbers != "") {
                code += numToBinaryEightBits(sinlgeNum);
            }
        }
        // remove leading zeros;
        int pos = sinlgeNum.find('1');
        sinlgeNum = sinlgeNum.substr(pos);

        code += numToBinaryEightBits(sinlgeNum);

    } else {
        std::cout << "Unable to open the file\n";
    }
}

void readForDebugEncode(const std::string &fileName, std::string &code) {
    std::ifstream in;
    std::string content, binary = "01";
    in.open(fileName);
    if (in.is_open()) {
        std::ostringstream ss;
        ss << in.rdbuf();
        content = ss.str();
        in.close();

        int pos = content.find_last_not_of(binary);
        if (pos != std::string::npos) {
            code = content.substr(pos + 1);
        }
    } else {
        std::cout << "Unable to open the file! \n";
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

/// saving the binary string to a file
void saveTreeAndBinaryToFile(const std::string &tree, const std::string &forStorage, const std::string &fileName) {
    std::ofstream out;
    out.open(fileName, std::ios::trunc);
    if (out.is_open()) {
        out << tree;
        out << "\n";
        out << forStorage;
        out.close();
    } else {
        std::cout << "Unable to open the file! \n";
    }
}


#endif //HUFFMANALGORITHM_FILEUTILS_H
