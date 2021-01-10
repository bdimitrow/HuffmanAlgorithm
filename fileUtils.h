#ifndef HUFFMANALGORITHM_FILEUTILS_H
#define HUFFMANALGORITHM_FILEUTILS_H

static const char *const DECIMAL_STRING = " 0123456789";

static const char *const BINARY_STRING = "01";

#include "tree.h"
#include "stringUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

/**
 * \file
 * @fn std::string readWholeFile(const std::string &fileOpenName)
 * The function takes a string(name of the file to be opened) as an argument and returns the whole file content in a string.
 * @param const std::string &fileOpenName
 * @return std::string fileContent
 */
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
        throw std::runtime_error("Unable to open the file! ");
    }

    return fileContent;
}

/**
 * @fn void readFileForDecompress(const std::string &fileName, std::string &bintree, std::string &code)
 * This function is used for binary decompression. The file with name 'filename' is opened if there is such a file.
 * The file content is extracted into a string 'wholeContent'. Then this string is divided into two parts. The first
 * one 'bintree' contains the needed information to rebuild the tree. The second one is called 'code' and holds the binary
 * sequence. The two parts are returned as reference arguments.
 * @param const std::string &fileName
 * @param std::string &bintree
 * @param std::string &code
 */
void readFileForDecompress(const std::string &fileName, std::string &bintree, std::string &code) {
    std::string codePart;
    std::string wholeContent = readWholeFile(fileName);

    int found = wholeContent.find_last_not_of(BINARY_STRING);
    if (found != std::string::npos) {
        code = wholeContent.substr(found + 1);
        bintree = wholeContent.erase(found + 1);
    }
}

/**
 * @fn void readFileForDecimalDecompress(const std::string &fileName, std::string &bintree, std::string &code)
 * This function is used for decimal decompression. The file with name 'fileName' is opened if there such a file.
 * The file content is extracted into a string 'wholeContent'. This stirng is splitted into three parts. 'lastSize' which
 * denotes the number of bits the last number should be. Then comes the information needed for rebuilding the tree. And the
 * 'codeNumbers' part which is changed from decimal to binary sequence('code'). The 'bintree' and 'code' are returned as
 * reference arguments.
 * @param const std::string &fileName
 * @param std::string &bintree
 * @param std::string &code
 */
void readFileForDecimalDecompress(const std::string &fileName, std::string &bintree, std::string &code) {
    std::string lastSize, codePart, codeNumbers, singleNum;
    std::string wholeContent = readWholeFile(fileName);

    int found = wholeContent.find_last_not_of(DECIMAL_STRING);
    if (found != std::string::npos) {
        codeNumbers = wholeContent.substr(found + 1);
        bintree = wholeContent.erase(found + 1);
        lastSize = bintree.substr(0, 1);
        bintree = bintree.substr(1);
    }
    while (!codeNumbers.empty()) {
        int pos = codeNumbers.find(' ');
        singleNum = codeNumbers.substr(0, pos);
        codeNumbers = codeNumbers.erase(0, pos + 1);
        if (!codeNumbers.empty()) {
            code += decimalToBinary(singleNum);
        }
    }
    singleNum = decimalToBinary(singleNum);
    if (singleNum.size() > (lastSize[0] - '0')) {
        singleNum = singleNum.substr(8 - (lastSize[0] - '0'));
    }
    code += singleNum;
}

/**
 * @fn void saveStringToFile(const std::string &fileName, const std::string &forStorage)
 * The function opens the file with 'fileName' name and save the 'forStorage' string it in if the opening was successful.
 * @param const std::string &fileName
 * @param const std::string &forStorage
 */
void saveStringToFile(const std::string &fileName, const std::string &forStorage) {
    std::ofstream out;
    out.open(fileName, std::ios::trunc);
    if (out.is_open()) {
        out << forStorage;
        out.close();
    } else {
        throw std::runtime_error("Unable to open the file!\n");
    }
}

/**
 * @fn void compareSizes(const std::string &originalContent, const std::string &encoded)
 * This function takes two strings as arguments. The first one is the whole content of a file before compressing and the
 * second one is the content compressed. The function calculates the bytes of both and compares them. The result is
 * printed on the console.
 * @param const std::string &originalContent
 * @param const std::string &encoded
 */
void compareSizes(const std::string &originalContent, const std::string &encoded) {
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(2);
    std::cout << "\nThe original file size is " << 8 * originalContent.size()
              << " bits and the compressed file will be "
              << encoded.size() << " bites. That means the compresssed file is "
              << encoded.size() / ((float) 8 * originalContent.size() / 100) << "% of the original one!\n\n";
}

#endif //HUFFMANALGORITHM_FILEUTILS_H
