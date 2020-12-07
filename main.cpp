#include <iostream>
#include "tree.h"
#include "utils.h"
#include <cstring>
#include <fstream>
#include <sstream>

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
    std::string originalContent = decodedTree->decode_file(code);
    std::cout << "Enter the name for the file with original content: ";
    std::string fileNameDecompressed;
    std::cin >> fileNameDecompressed;
    saveStringToFile(fileNameDecompressed, originalContent);
}

int main() {

//    encode();
    decode();


    return 0;
}


