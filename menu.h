//
// Created by bozhidar on 12/5/20.
//

#ifndef HUFFMANALGORITHM_MENU_H
#define HUFFMANALGORITHM_MENU_H

#include <iostream>
#include "tree.h"
#include "fileUtils.h"
#include "stringUtils.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <cmath>
#include <bitset>


void menu() {
    std::cout << "Welcome!\n";
    std::cout << "Please choose an action!\n"
                 "Press 1 to compress a file;\n"
                 "Press 2 to decompress a file;\n"
                 "Press 3 to quit;\n";
    int choice;
    do {
        std::cout << "Make a choice: ";
        std::cin >> choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid choice! Please enter an integer! " << std::endl;
            std::cin.clear();                            // reset any error flags
            std::cin.ignore(10000, '\n');       // ignore any characters in the input buffer
        } else if (choice == 1 || choice == 2 || choice == 3) {
            if (choice == 1) {
                std::cout
                        << "This is the compression functionality. Two versions of compression are supported(Choose one): \n"
                           "Press 1 for binary compress;\n"
                           "Press 2 for numeric compress;\n";

            } else if (choice == 2) {
                std::cout
                        << "This is the decompression functionality. Two versions of decompression are supported(Choose one): \n"
                           "Press 1 to decompress a binary compressed file;\n"
                           "Press 2 to decompress a numeric compressed file;\n";

            } else if (choice == 3) {
                //
            }
        }
    } while (choice != 3);
}

std::string decodeBinary(const std::string &fileName) {
    std::string hftree, code, originalContent;

    readFileForDecompress(fileName, hftree, code);
    std::vector<std::pair<char, std::string>> pairs = stringToVectorCodePairs(hftree);
    HuffmanTree *decodedTree = new HuffmanTree(pairs);
    originalContent = decodedTree->decode_string(code);

    return originalContent;
}

std::string decodeDecimal(const std::string &fileName) {
    std::string hftree, code, originalContent;

    readFileForDecimalDecompress(fileName, hftree, code);
    std::vector<std::pair<char, std::string>> pairs = stringToVectorCodePairs(hftree);
    HuffmanTree *decodedTree = new HuffmanTree(pairs);
    originalContent = decodedTree->decode_string(code);

    return originalContent;
}

void decode(bool binary) {
    std::string fileName, fileNameDecompressed, originalContent;
    std::cout << "Enter the name of the file you'd like to decompress: ";
    std::cin >> fileName;

    if (binary) {
        originalContent = decodeBinary(fileName);
    } else {
        originalContent = decodeDecimal(fileName);
    }

    std::cout << "Enter the name for the file with original content: ";
    std::cin >> fileNameDecompressed;
    saveStringToFile(fileNameDecompressed, originalContent);
}


std::string encodeBinary(const std::string &originalFileName) {
    std::string fileContent, pairsAsString, binaryString, forStorage;

    fileContent = readWholeFile(originalFileName);
    HuffmanTree *tree = new HuffmanTree(fileContent.c_str());
    std::vector<std::pair<char, std::string>> pairs;
    tree->makePairs(pairs);
    pairsAsString = vectorCodePairsToString(pairs);
    binaryString = encodeString(fileContent, pairs);
    forStorage = pairsAsString + "\n" + binaryString;

    compareSizes(fileContent, binaryString);

    return forStorage;
}

std::string encodeDecimal(const std::string &originalFileName) {
    std::string fileContent, pairsAsString, binaryString, numbersForSaving, forStorage;

    fileContent = readWholeFile(originalFileName);
    HuffmanTree *tree = new HuffmanTree(fileContent.c_str());
    std::vector<std::pair<char, std::string>> pairs;
    tree->makePairs(pairs);
    pairsAsString = vectorCodePairsToString(pairs);
    binaryString = encodeString(fileContent, pairs);

    numbersForSaving = contentAsNumbers(binaryString);

    // @TODO better way to add the char ;(
    char num = binaryString.size() % 8 + '0';
    std::stringstream ss;
    ss << num;
    ss >> forStorage;

    forStorage += pairsAsString + "\n" + numbersForSaving;

    return forStorage;
}


void encode(bool binary) {
    std::string originalFileName, compressedFileName, forStorage;

    std::cout << "Enter the name of the file to be compressed: ";
    std::cin >> originalFileName;

    if (binary) {
        forStorage = encodeBinary(originalFileName);
    } else {
        forStorage = encodeDecimal(originalFileName);
    }

    std::cout << "Enter a name for the compressed file: ";
    std::cin >> compressedFileName;
    saveStringToFile(compressedFileName, forStorage);
}

void debug() {
    std::string fileName, fileNameDecompressed, decimalContent, binaryCode;
    std::cout << "Enter the name of the compressed file you'd like to debug: ";
    std::cin >> fileName;

    std::string hftree;

    readFileForDecompress(fileName, hftree, binaryCode);

    decimalContent = contentAsNumbers(binaryCode);

    std::cout << "Enter the name for the file with original content: ";
    std::cin >> fileNameDecompressed;
    saveStringToFile(fileNameDecompressed, decimalContent);
}

#endif //HUFFMANALGORITHM_MENU_H
