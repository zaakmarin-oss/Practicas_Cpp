#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

T leer(const std::string& mensaje, T minimo, T maximo) {
    for (;;) {
        std::cout << mensaje << std::flush;
        std::string linea;
        if (!std::getline(std::cin, linea))
            throw std::runtime_error("Entrada finalizada antes de completar los datos.");

        // Se admite punto o coma decimal, pero no separadores de miles.
        if constexpr (std::is_floating_point_v<T>) {
            const auto coma = linea.find(',');
            if (coma != std::string::npos && linea.find('.') == std::string::npos
                && linea.find(',', coma + 1) == std::string::npos)
                linea[coma] = '.';
        }

        std::istringstream entrada(linea);
        T valor{};
        if (entrada >> valor) {
            entrada >> std::ws;
            if (entrada.eof() && std::isfinite(static_cast<long double>(valor))
                && valor >= minimo && valor <= maximo)
                return valor;
        }
        std::cout << "Entrada invalida. Escribe un "
                  << (std::is_integral_v<T> ? "entero" : "numero")
                  << " entre " << minimo << " y " << maximo << ".\n";
    }
}

double verificarResultado(double valor) {
    if (!std::isfinite(valor))
        throw std::overflow_error("El resultado excede el rango de double.");
    return valor;
}

// Practica 3: funciones, parametros, menu y seleccion.
double sumar(double a, double b) { return a + b; }
double restar(double a, double b) { return a - b; }
double multiplicar(double a, double b) { return a * b; }
double dividir(double a, double b) {
    if (b == 0) throw std::invalid_argument("No se puede dividir entre cero.");
    return verificarResultado(a / b);
}
void ejecutar() {
    for (;;) {
        int op = leer<int>("\n1 Sumar | 2 Restar | 3 Multiplicar | 4 Dividir | 0 Salir: ", 0, 4);
        if (op == 0) break;
        double a = leer<double>("Primer numero: ", -1e6, 1e6);
        double b = leer<double>("Segundo numero: ", -1e6, 1e6);
        try {
            double resultado = 0;
            switch (op) {
                case 1: resultado = sumar(a,b); break;
                case 2: resultado = restar(a,b); break;
                case 3: resultado = multiplicar(a,b); break;
                case 4: resultado = dividir(a,b); break;
            }
            std::cout << "Resultado: " << resultado << '\n';
        } catch (const std::exception& e) { std::cout << e.what() << '\n'; }
    }
}

int main() {
    std::cout << std::setprecision(12);
    try { ejecutar(); }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
