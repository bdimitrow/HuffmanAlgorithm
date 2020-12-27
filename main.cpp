#include "menu.h"


int main() {

//    encode(true);
//    decode(true);
//
//    encode(false);
//    decode(false);

//    debug();

    menu();


    return 0;
}


// testString.txt
// testEqual.txt

/** \mainpage About Project
 *
 *   \section First Project's aim
 *    The aim of this project is to create an application that supports compression and decompression of text files
 *   using the Huffman algorithm. When started a menu appears on the screen and the user should input a digit between
 *   1 and 6 in order to choose an action to be performed. The main functionality of the project is to support COMPRESS
 *   function that takes a file, reads its content and transforms it into a binary string. Moreover when a file is
 *   being compressed the compression ratio is printed on the screen whereas the binary sequence including an extra
 *   information about the Huffman tree(used when decompressing) are saved in a file. Another functionality is the
 *   DECOMPRESS function that takes an already compressed file and creates a new file containing the original content.
 *   The next function is called debug. It takes an already compressed file and prints the binary sequence as decimal
 *   numbers. When pressing 4 the program terminates. With 5 a text file is taken and compressed. The difference is from
 *   option 1 is that the binary sequence is translated into decimal sequence. By pressing 6 the user is able to decompress
 *   such files.
 *
 *  \subsection Github
 *  https://github.com/bdimitrow/HuffmanAlgorithm
 *
 *  \section Second Happy path
 *

 */
