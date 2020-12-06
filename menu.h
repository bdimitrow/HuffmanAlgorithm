//
// Created by bozhidar on 12/5/20.
//

#ifndef HUFFMANALGORITHM_MENU_H
#define HUFFMANALGORITHM_MENU_H

#include<iostream>


void menu(){
    std::cout << "Welcome!\n";
    std::cout << "Please choose an action!\n"
                 "Press 'c' to compress a file;\n"
                 "Press 'd' to decompress a file;\n"
                 "Press 'q' to quit;";

    char ch;
    std::cin >> ch;
    switch (ch) {
        case 'c' : ///
        break;
        case 'd' : ///
        break;
        case 'q' : ///
        break;
        default:
            std::cout << "Invalid choice!\n";
    }
}


#endif //HUFFMANALGORITHM_MENU_H
