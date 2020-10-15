/**
 * Author: Mohammed Nurul Hoque
 */

#include <iostream>
#include <exception>
#include "tcpp.h"

int main(int argc, char *argv[]) {
    RWSocket socket(argv[1], atoi(argv[2]));

    try {
        for (int i=0; i<10; ++i) {
            socket << i;
            std::cout << "sent " << i << '\n';
            socket >> i;
            std::cout << "rcvd " << i << '\n';
        }
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
    
}