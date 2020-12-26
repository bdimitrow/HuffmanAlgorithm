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


void debug(std::string fileName) {
    std::string binary = "01", decimalContent, binaryCode;
    std::string fileContent = readWholeFile(fileName);

    if(fileContent.empty()) return;

    int found = fileContent.find_last_not_of(binary);
    if (found != std::string::npos) {
        binaryCode = fileContent.substr(found + 1);
    }

    decimalContent = contentAsNumbers(binaryCode);
    std::cout << "The file contains the following numbers: " << decimalContent << std::endl;
}


void menu() {
    std::cout << "Welcome!\n";
    std::cout << "Please choose an action!\n"
                 "Press 1 to compress a file(original to binary compress);\n"
                 "Press 2 to decompress a file(binary compressed to original);\n"
                 "Press 3 to debug(binary compressed to decimal numbers);\n"
                 "Press 4 to exit;\n"
                 "Press 5 to compress a file(original to decimal compress);\n"
                 "Press 6 to decompress a file(decimal compressed to original);";
    int choice;
    do {
        std::cout << "\nMake a choice: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid choice! Please enter an integer! " << std::endl;
            std::cin.clear();                            // reset any error flags
            std::cin.ignore(10000, '\n');       // ignore any characters in the input buffer
        } else if (choice >= 1 && choice <= 6) {
            if (choice == 1) {
                encode(true);

            } else if (choice == 2) {
                decode(true);

            } else if (choice == 3) {
                std::string fileDebugName;
                std::cout << "Enter the name of the file to be debugged: ";
                std::cin >> fileDebugName;
                debug(fileDebugName);
            } else if(choice == 4){
                std::cout << "Goodbye have a nice day! \n";
                return exit(EXIT_SUCCESS);
            } else if(choice == 5){
                encode(false);
            } else {
                decode(false);
            }
        }
    } while (choice != 3);
}

#endif //HUFFMANALGORITHM_MENU_H
