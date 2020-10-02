#include <iostream>
#include <exception>
#include "tcpp.h"

int main() {
    int n;
    RWSocket socket("127.0.0.1", 2000);

    try {
        while (1) {
            socket >> n;
            std::cout << n << std::endl;
        }
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
    
}