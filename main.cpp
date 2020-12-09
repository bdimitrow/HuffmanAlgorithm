#include <iostream>
#include "tree.h"
#include "utils.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <cmath>

void encode() {
    std::cout << "Enter the name of the file you'd like to compress: ";
    std::string nameFileForCompress;
    std::cin >> nameFileForCompress;
    std::string fileContent = readWholeFile(nameFileForCompress);
    HuffmanTree *tree = new HuffmanTree(fileContent.c_str());
    std::vector<std::pair<char, std::string>> pairs;
    tree->makePairs(pairs);
    std::string pairsAsString = vectorCodePairsToString(pairs);
    std::string binaryString = convertStringToBinary(fileContent, pairs);
    std::cout << "Enter a name for the compressed file: ";
    std::string nameCompressedFile;
    std::cin >> nameCompressedFile;
    saveTreeAndBinaryToFile(pairsAsString, binaryString, nameCompressedFile);
}

void decode() {
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

int binaryToNumber(std::string binary) {
    int num = 0;
    for (int i = 0, power = 7; i < binary.size(); ++i, --power) {
        if (binary[i] - '0' == 1)
            num += pow(2, power);
    }
    return num;
}

void debugOption() {
    std::cout << "Enter the name of the file to be decompressed: ";
    std::string fileName, code;
    std::cin >> fileName;
    readForDebugOption(fileName, code);

    int arrSize = code.size() / 8 + 1;
    std::string arr[arrSize];
    for (int i = 0, j = 0; i < code.size(); i += 8, ++j) {
        std::string substirng = code.substr(i, 8);
        arr[j] = substirng;
    }
    if (arr[arrSize - 1].size() < 8) {
        int leadingZeros = 8 - arr[arrSize - 1].size();
        for (int i = 0; i < leadingZeros; ++i) {
            arr[arrSize - 1] = '0' + arr[arrSize - 1];
        }
    }
    for (const auto &el :arr) {
        std::cout << binaryToNumber(el) << " ";
    }
}

int main() {

    encode();
//    decode();

    debugOption();

    return 0;
}


