#include "tcpp.h"

int main(int argc, char* argv[]) {
    ServerSocket srv(atoi(argv[1]));
    RWSocket socket = srv.accept();
    try {
        int n;
        while (1) {
            socket >> n;
            std::cout << n << std::endl;
            socket << n+1;
        }
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}