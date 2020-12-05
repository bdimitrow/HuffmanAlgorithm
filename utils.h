//
// Created by bozhidar on 12/3/20.
//

#ifndef HUFFMANALGORITHM_UTILS_H
#define HUFFMANALGORITHM_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "tree.h"


std::string readFile() {
    std::string fileOpenName, fileContent;
//    std::cout << "Enter the name of the file you'd like to compress: ";
//    std::cin >> fileOpenName;

    std::ifstream in;
    in.open("testString.txt"/*fileOpenName*/);
    if (in.is_open()) {
        std::ostringstream ss;
        ss << in.rdbuf(); //reading the file into the stream
        fileContent = ss.str();
        in.close();
    } else { std::cout << "Unable to open the file!"; }

    return fileContent;
}

std::string convertStringToBinary(std::string realContent, std::vector<std::pair<char, std::string>> &codePairs) {
    std::string output;
    int i =0;
    while (realContent[i]) {
        for (auto el : codePairs) {
            if (realContent[i] == el.first) {
                output += el.second;
            }
        }
        ++i;
    }
    return output;
}

void saveBinaryStringToFile(std::string forStorage){
    std::string compressedFileName;
    std::cout << "Enter the name for the compressed file: ";
    std::cin >> compressedFileName;

    std::ofstream out;
    out.open(compressedFileName);
    if(out.is_open()){
        out << forStorage;
        out.close();
    } else {
        std::cout << "Unable to open the file! \n";
    }

}



//
//void makePairs(HuffmanTree::HuffmanTreeNode *root, std::string str, std::vector<std::pair<char, std::string>> &vec) {
//    if (root->left) {
//        makePairs(root->left, str + '0', vec);
//    }
//    if (root->right) {
//        makePairs(root->right, str + '1', vec);
//    }
//    if (root != nullptr && root->left == nullptr && root->right == nullptr) {
//        vec.push_back(std::make_pair(root->symbol, str));
//    }
//}


#endif //HUFFMANALGORITHM_UTILS_H
