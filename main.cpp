#include <iostream>
#include "tree.h"
#include "fileUtils.h"
#include "stringUtils.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <cmath>
#include <bitset>

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

void encodeBinary() {
    std::cout << "Enter the name of the file you'd like to compress: ";
    std::string nameFileForCompress;
    std::cin >> nameFileForCompress;
    std::string fileContent = readWholeFile(nameFileForCompress);
    HuffmanTree *tree = new HuffmanTree(fileContent.c_str());
    std::vector<std::pair<char, std::string>> pairs;
    tree->makePairs(pairs);
    std::string pairsAsString = vectorCodePairsToString(pairs);
    std::string binaryString = encodeString(fileContent, pairs);
    std::cout << "Enter a name for the compressed file: ";
    std::string nameCompressedFile;
    std::cin >> nameCompressedFile;
    saveTreeAndBinaryToFile(pairsAsString, binaryString, nameCompressedFile);
}

void encodeDebug() {
    std::cout << "Enter the name of the file to be compressed: ";
    std::string fileNameForCompress, code;
    std::cin >> fileNameForCompress;
    std::string fileContent = readWholeFile(fileNameForCompress);
    HuffmanTree *tree = new HuffmanTree(fileContent.c_str());
    std::vector<std::pair<char, std::string>> pairs;
    tree->makePairs(pairs);
    std::string pairsAsString = vectorCodePairsToString(pairs);
    std::string binaryContent = encodeString(fileContent, pairs);


    int arrSize = binaryContent.size() / 8 + 1;
    std::string arrBinaryNums[arrSize];
    for (int i = 0, j = 0; i < binaryContent.size(); i += 8, ++j) {
        std::string subStirng = binaryContent.substr(i, 8);
        arrBinaryNums[j] = subStirng;
    }

    std::string numbersForSaving;
    for (const auto &el :arrBinaryNums) {
        numbersForSaving += binaryToNumber(el) + " ";
    }

    std::cout << "Enter a name for the compressed file: ";
    std::string nameCompressedFile;
    std::cin >> nameCompressedFile;
    saveTreeAndBinaryToFile(pairsAsString, numbersForSaving, nameCompressedFile);

}

void decodeDebug() {
    std::string fileName, hftree, code;
    std::cout << "Enter the name of the file you'd like to decompress: ";
    std::cin >> fileName;
    readFileForDebugDecode(fileName, hftree, code);
    std::vector<std::pair<char, std::string>> pairs = stringToVectorCodePairs(hftree);
    HuffmanTree *decodedTree = new HuffmanTree(pairs);
    std::string originalContent = decodedTree->decode_string(code);
    std::cout << "Enter the name for the file with original content: ";
    std::string fileNameDecompressed;
    std::cin >> fileNameDecompressed;
    saveStringToFile(fileNameDecompressed, originalContent);
}


int main() {

    encodeBinary();
    decodeBinary();

//    encodeDebug();
//    decodeDebug();
//
//    std::string bin = "00001110";
//    std::cout << binaryToNumber(bin);

//    std::string sinlgeNum = "00000";
//    int pos = sinlgeNum.find('1');
//    sinlgeNum = sinlgeNum.substr(pos);
//
//    std::cout << sinlgeNum;
    return 0;
}


// testString.txt