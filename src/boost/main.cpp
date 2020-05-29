#include "echo_client.h"
#include "echo_server.h"

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        if (std::string(argv[1]) == "-c") {
            if (argc != 4) {
                std::cerr << "Usage: -c <host> <port>\n";
                return 1;
            } else {
                echo_client(std::string(argv[2]), std::string(argv[3]));
            }
        } else if (std::string(argv[1]) == "-s") {
            if (argc != 3) {
                std::cerr << "Usage: -s <port>\n";
                return 1;
            } else {
                echo_server(argv[2]);
            }
        }
    } else {
        std::cout << "run client: -c <host> <port>" << std::endl;
        std::cout << "run server: -s <port>" << std::endl;
    }

    return 0;
}