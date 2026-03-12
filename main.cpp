#include <cstdlib>
#include <iostream>

void start_server(int port);

int main() {
    int port = 8080;

    if (const char* env_port = std::getenv("PORT")) {
        try {
            port = std::stoi(env_port);
        } catch (...) {
            std::cerr << "PORT invalido, usando 8080\n";
        }
    }

    start_server(port);
    return 0;
}
