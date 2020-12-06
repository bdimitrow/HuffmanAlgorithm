#include <iostream>
#include "tree.h"
#include "utils.h"
#include <cstring>
#include <fstream>
#include <sstream>



int main() {
//    auto *t = new HuffmanTree(readWholeFile().c_str());
//
//
//    std::vector<std::pair<char, std::string>> pairs;
//    t->makePairs(pairs);
////    std::cout << pairs.at(0).second.size();
////
//    auto *hf = new HuffmanTree(pairs);

//    std::string str = readWholeFile();
//    std::cout << "str: " << str << std::endl;
//    saveStringToFile(convertStringToBinary(str, pairs));
//
//    std::string bina = convertStringToBinary(str, pairs);
//
//    std::string outa = t->decode_file(bina);
//    std::cout << "encoded: " << bina << "\n";
//    std::cout << "decoded: " << outa << "\n";
//    t->printCode();

//    std::cout << "original: " << readWholeFile()<<std::endl;
//    auto *treeRead = new HuffmanTree(readWholeFile().c_str());
//    std::vector<std::pair<char, std::string>> pair;
//    treeRead->makePairs(pair);
//    std::string binary = convertStringToBinary(readWholeFile(),pair);
//    std::cout << "encoded: " << binary << std::endl;
//    std::string encodedTree = vectorCodePairsToString(pair);
//    saveStringToFile(encodedTree+"\n","");
//    saveStringToFile(binary, "");
//    std::vector<std::pair<char, std::string>> rebuild = stringToVectorCodePairs(encodedTree);
//    auto *rebuildTree = new HuffmanTree(rebuild);
//    std::cout<<"restored: " << rebuildTree->decode_file(binary) << std::endl;

    std::ifstream in;
    in.open("compressed.txt");
    std::string str,str2,buffer;
    std::getline(in, str);
    while (std::getline(in, buffer)) {
        str2 += '\n' + buffer;
    }
    std::cout << str;// << std::endl;
    std::cout << str2 << std::endl;
    std::cout << " dada";
    return 0;
}


//    std::ofstream out;
//    out.open("testString.txt");
//    if (out.is_open()) {
//        out << "dada nee de s !, sd k\n";
//        out.close();
//    } else { std::cout << "unable to open\n"; }

//    HuffmanTree *tree;
//    std::string str;
//    std::ifstream in;
//    in.open("testString.txt");
//    if (in.is_open()) {
//            std::ostringstream ss;
//            ss << in.rdbuf();
//            str = ss.str();
//        in.close();
//    }
