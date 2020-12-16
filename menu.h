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

void decodeBinary() {
    std::string fileName, hftree, code;
    std::cout << "Enter the name of the file you'd like to decompress: ";
    std::cin >> fileName;
    readFileForDecompress(fileName, hftree, code);
    std::vector<std::pair<char, std::string>> pairs = stringToVectorCodePairs(hftree);
    HuffmanTree *decodedTree = new HuffmanTree(pairs);
    std::string originalContent = decodedTree->decode_string(code);
    std::cout << "Enter the name for the file with original content: ";
    std::string fileNameDecompressed;
    std::cin >> fileNameDecompressed;
    saveStringToFile(fileNameDecompressed, originalContent);
}

void decodeDebug() {
    std::string fileName, hftree, code;
    std::cout << "Enter the name of the file you'd like to decompress: ";
    std::cin >> fileName;
    readFileForDebugDecompress(fileName, hftree, code);
    std::vector<std::pair<char, std::string>> pairs = stringToVectorCodePairs(hftree);
    HuffmanTree *decodedTree = new HuffmanTree(pairs);
    std::string originalContent = decodedTree->decode_string(code);
    std::cout << "Enter the name for the file with original content: ";
    std::string fileNameDecompressed;
    std::cin >> fileNameDecompressed;
    saveStringToFile(fileNameDecompressed, originalContent);
}

void encodeBinary() {
    std::string originalFileName, fileContent, pairsAsString, binaryString, compressedFileName, forStorage;
    std::cout << "Enter the name of the file you'd like to compress: ";
    std::cin >> originalFileName;

    fileContent = readWholeFile(originalFileName);
    HuffmanTree *tree = new HuffmanTree(fileContent.c_str());
    std::vector<std::pair<char, std::string>> pairs;
    tree->makePairs(pairs);
    pairsAsString = vectorCodePairsToString(pairs);
    binaryString = encodeString(fileContent, pairs);
    forStorage = pairsAsString + "\n" + binaryString;

    std::cout << "Enter a name for the compressed file: ";
    std::cin >> compressedFileName;
    saveStringToFile(compressedFileName, forStorage);
}


void encodeDebug() {
    std::cout << "Enter the name of the file to be compressed: ";
    std::string originalFileName, fileContent, pairsAsString, binaryContent, compressedFileName, numbersForSaving;
    std::cin >> originalFileName;

    fileContent = readWholeFile(originalFileName);
    HuffmanTree *tree = new HuffmanTree(fileContent.c_str());
    std::vector<std::pair<char, std::string>> pairs;
    tree->makePairs(pairs);
    pairsAsString = vectorCodePairsToString(pairs);
    binaryContent = encodeString(fileContent, pairs);

    numbersForSaving = contentAsNumbers(binaryContent);

    // @TODO better way to add the char ;(
    char num = binaryContent.size() % 8 + '0';
    std::stringstream ss;
    ss << num;
    std::string forStorage;
    ss >> forStorage;
    forStorage += pairsAsString + "\n" + numbersForSaving;

    std::cout << "Enter a name for the compressed file: ";
    std::cin >> compressedFileName;
    saveStringToFile(compressedFileName, forStorage);
}




#endif //HUFFMANALGORITHM_MENU_H
