
#ifdef _WIN32
  #ifndef WINVER
    #define WINVER 0x0A00
  #endif
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0A00
  #endif
#endif

#include <cstdlib>
#include <iostream>
#include "httplib.h"

int main() {
    // Obtener el puerto que asigna Render
    const char* port_env = std::getenv("PORT");
    int port = port_env ? std::stoi(port_env) : 8080;

    httplib::Server svr;

    // Ruta principal
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("Hola, soy Asalia desde C++ en Render", "text/plain");
    });

    // Ruta de prueba
    svr.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("ok", "text/plain");
    });

    std::cout << "Escuchando en 0.0.0.0:" << port << std::endl;

    // IMPORTANTE: usar 0.0.0.0 para Render
    svr.listen("0.0.0.0", port);

    return 0;
}