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

/**
 * \file Containg the menu.
 * @fn std::string encodeBinary(const std::string &originalFileName)
 * That is the first option from the menu. Used to transform the original file content into a binary sequence. The returned
 * string is what should be saved into the file.
 * @param const std::string &originalFileName
 * @return std::string forStorage
 */
std::string encodeBinary(const std::string &originalFileName);

/**
 * @fn std::string encodeDecimal(const std::string &originalFileName)
 * That is the fifth option form the menu. Used to transform the original file content into a binary sequence. After that
 * this binary sequence is transformed into decimal sequence. Which is returned for saving.
 * @param const std::string &originalFileName
 * @return std::string forStorage
 */
std::string encodeDecimal(const std::string &originalFileName);


/**
 * @fn void encode(bool binary)
 * Used to compress a file. The program supports two kinds of compressing(binary and decimal). That is the reason for the
 * parameter 'binary'. The function body is in between a try-catch block because the file you would like to compress might be
 * an empty one or such a file might not exist.
 * @param binary
 */
void encode(bool binary);

/**
 * @fn std::string decodeBinary(const std::string &fileName)
 * This function is the second option in the menu. It reads an already compressed(in binary) file and returns the original content as string.
 * @param const std::string &fileName
 * @return std::string forStorage
 */
std::string decodeBinary(const std::string &fileName);

/**
 * @fn std::string decodeDecimal(const std::string &fileName)
 * This function is the sixth option in the menu. It reads an already compressed(in decimal) file and returns the original content as string.
 * @param const std::string &fileName
 * @return std::string forStorage
 */
std::string decodeDecimal(const std::string &fileName);

/**
 * @fn void decode(bool binary)
 * Used to decompress a file. The program supports two kinds of compressing(binary and decimal). So it should support two
 * types of decompression(binary and decimal). That is the reason for the parameter 'binary'. The function body is in between a try-catch block
 * because either the file can be empty or some information can be deleted or corrupted or a file with that name might not exist.
 * @param bool binary
 */
void decode(bool binary);

/**
 * @fn void debug(const std::string &fileName)
 * This is the third option in the menu. The function takes an already compressed(in binary) file and prints to the console
 * the binary sequence divided into 8 bits in decimal numbers.
 * @param fileName
 */
void debug(const std::string &fileName);

std::string decodeBinary(const std::string &fileName) {
    std::string hftree, code, originalContent;

    readFileForDecompress(fileName, hftree, code);

    if (hftree.empty() || code.empty()) {
        throw std::invalid_argument("The file you are trying to decompress is empty or corrupted!");
    }

    std::vector<std::pair<char, std::string>> pairs = stringToVectorCodePairs(hftree);
    HuffmanTree *decodedTree = new HuffmanTree(pairs);
    originalContent = decodedTree->decode_string(code);

    return originalContent;
}

std::string decodeDecimal(const std::string &fileName) {
    std::string hftree, code, originalContent;

    readFileForDecimalDecompress(fileName, hftree, code);

    if (hftree.empty() || code.empty()) {
        throw std::invalid_argument("The file you are trying to decompress is empty or corrupted!");
    }

    std::vector<std::pair<char, std::string>> pairs = stringToVectorCodePairs(hftree);
    HuffmanTree *decodedTree = new HuffmanTree(pairs);
    originalContent = decodedTree->decode_string(code);

    return originalContent;
}

void decode(bool binary) {
    try {
        std::string fileName, fileNameDecompressed, originalContent;
        std::cout << "Enter the name of the file you'd like to decompress: ";
        std::cin >> fileName;

        if (binary) {
            originalContent = decodeBinary(fileName);
        } else { // decimal
            originalContent = decodeDecimal(fileName);
        }

        std::cout << "Enter the name for the file with original content: ";
        std::cin >> fileNameDecompressed;
        saveStringToFile(fileNameDecompressed, originalContent);
    } catch (std::runtime_error &error) {
        std::cout << error.what() << std::endl;
    } catch (std::invalid_argument &errorM) {
        std::cout << errorM.what() << std::endl;
    }
}

std::string encodeBinary(const std::string &originalFileName) {
    std::string fileContent, pairsAsString, binaryString, forStorage;

    fileContent = readWholeFile(originalFileName);

    if (fileContent.empty()) {
        throw std::invalid_argument("The file you are trying to compress is empty!");
    }

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

    if (fileContent.empty()) {
        throw std::invalid_argument("The file you are trying to compress is empty!");
    }

    HuffmanTree *tree = new HuffmanTree(fileContent.c_str());
    std::vector<std::pair<char, std::string>> pairs;
    tree->makePairs(pairs);
    pairsAsString = vectorCodePairsToString(pairs);
    binaryString = encodeString(fileContent, pairs);

    numbersForSaving = contentAsNumbers(binaryString);

    char num = binaryString.size() % 8 + '0';
    std::stringstream ss;
    ss << num;
    ss >> forStorage;

    forStorage += pairsAsString + "\n" + numbersForSaving;

    return forStorage;
}

void encode(bool binary) {
    try {
        std::string originalFileName, compressedFileName, forStorage;

        std::cout << "Enter the name of the file you'd like to compress: ";
        std::cin >> originalFileName;

        if (binary) {
            forStorage = encodeBinary(originalFileName);
        } else {
            forStorage = encodeDecimal(originalFileName);
        }

        std::cout << "Enter a name for the compressed file: ";
        std::cin >> compressedFileName;
        saveStringToFile(compressedFileName, forStorage);
    } catch (std::runtime_error &error) {
        std::cout << error.what() << std::endl;
    } catch (std::invalid_argument &errorM) {
        std::cout << errorM.what() << std::endl;
    }
}

void debug(const std::string &fileName) {
    try {
        std::string binary = "01", decimalContent, binaryCode;
        std::string fileContent = readWholeFile(fileName);

        if (fileContent.empty()) {
            throw std::invalid_argument("The file you are trying to debug is empty!");
        }

        int found = fileContent.find_last_not_of(binary);
        if (found != std::string::npos) {
            binaryCode = fileContent.substr(found + 1);
        }

        decimalContent = contentAsNumbers(binaryCode);
        std::cout << "The file contains the following numbers: " << decimalContent << std::endl;

    } catch (std::runtime_error &error) {
        std::cout << error.what() << std::endl;
    } catch (std::invalid_argument &errorM) {
        std::cout << errorM.what() << std::endl;
    }
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
            } else if (choice == 4) {
                std::cout << "Thank you for using the application! \n";
                return exit(EXIT_SUCCESS);
            } else if (choice == 5) {
                encode(false);
            } else {
                decode(false);
            }
        }
    } while (choice != 4);
}

#endif //HUFFMANALGORITHM_MENU_H
