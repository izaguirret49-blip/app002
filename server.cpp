#include <iostream>
#include <sstream>
#include <string>

#include "httplib.h"

namespace {
std::string render_form() {
    return R"HTML(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Formulario C++ en Render</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background: #f4f6f8;
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
    }
    .card {
      width: 100%;
      max-width: 500px;
      background: white;
      padding: 32px;
      border-radius: 14px;
      box-shadow: 0 10px 30px rgba(0,0,0,0.12);
      box-sizing: border-box;
    }
    h1 {
      margin-top: 0;
      color: #1f2937;
      font-size: 28px;
    }
    p {
      color: #4b5563;
    }
    label {
      display: block;
      margin-top: 16px;
      margin-bottom: 6px;
      font-weight: bold;
      color: #374151;
    }
    input, textarea {
      width: 100%;
      padding: 12px;
      border: 1px solid #d1d5db;
      border-radius: 8px;
      box-sizing: border-box;
      font-size: 15px;
    }
    textarea {
      resize: vertical;
      min-height: 120px;
    }
    button {
      margin-top: 20px;
      width: 100%;
      padding: 12px;
      border: none;
      border-radius: 8px;
      background: #2563eb;
      color: white;
      font-size: 16px;
      cursor: pointer;
    }
    button:hover {
      background: #1d4ed8;
    }
  </style>
</head>
<body>
  <div class="card">
    <h1>Formulario básico</h1>
    <p>Servidor web hecho en C++ listo para desplegar en Render. La vieja escuela, pero en la nube.</p>
    <form action="/submit" method="post">
      <label for="nombre">Nombre</label>
      <input type="text" id="nombre" name="nombre" required>

      <label for="correo">Correo</label>
      <input type="email" id="correo" name="correo" required>

      <label for="mensaje">Mensaje</label>
      <textarea id="mensaje" name="mensaje" required></textarea>

      <button type="submit">Enviar</button>
    </form>
  </div>
</body>
</html>
)HTML";
}

std::string render_response(const std::string& nombre,
                            const std::string& correo,
                            const std::string& mensaje) {
    std::ostringstream html;
    html << R"HTML(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Datos recibidos</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background: #eef2ff;
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
    }
    .card {
      width: 100%;
      max-width: 560px;
      background: white;
      padding: 32px;
      border-radius: 14px;
      box-shadow: 0 10px 30px rgba(0,0,0,0.12);
      box-sizing: border-box;
    }
    h1 { color: #1f2937; margin-top: 0; }
    .item { margin-bottom: 14px; }
    .label { font-weight: bold; color: #374151; }
    .value { color: #111827; }
    a {
      display: inline-block;
      margin-top: 18px;
      text-decoration: none;
      color: white;
      background: #2563eb;
      padding: 10px 16px;
      border-radius: 8px;
    }
  </style>
</head>
<body>
  <div class="card">
    <h1>Formulario recibido</h1>
    <div class="item"><span class="label">Nombre:</span> <span class="value">)HTML";

    html << nombre;
    html << R"HTML(</span></div>
    <div class="item"><span class="label">Correo:</span> <span class="value">)HTML";
    html << correo;
    html << R"HTML(</span></div>
    <div class="item"><span class="label">Mensaje:</span> <span class="value">)HTML";
    html << mensaje;
    html << R"HTML(</span></div>
    <a href="/">Volver al formulario</a>
  </div>
</body>
</html>
)HTML";

    return html.str();
}
}  // namespace

void start_server(int port) {
    httplib::Server server;

    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(render_form(), "text/html; charset=UTF-8");
    });

    server.Post("/submit", [](const httplib::Request& req, httplib::Response& res) {
        const auto nombre = req.get_param_value("nombre");
        const auto correo = req.get_param_value("correo");
        const auto mensaje = req.get_param_value("mensaje");

        res.set_content(render_response(nombre, correo, mensaje), "text/html; charset=UTF-8");
    });

    std::cout << "Servidor iniciado en el puerto " << port << std::endl;
    server.listen("0.0.0.0", port);
}
