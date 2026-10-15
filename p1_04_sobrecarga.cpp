#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

// Repite la pregunta si la entrada no es un numero completo dentro del rango.
template <typename T>
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

// Cada operacion tiene el mismo nombre y tres firmas: 0, 2 y 3 parametros.
class Calculadora {
    double primero, segundo;
public:
    Calculadora(double a, double b) : primero(a), segundo(b) {}
    double sumar(double a, double b) const { return a+b; }
    double sumar() const { return sumar(primero, segundo); }
    double sumar(double a, double b, double c) const { return sumar(a,b)+c; }
    double restar(double a, double b) const { return a-b; }
    double restar() const { return restar(primero, segundo); }
    double restar(double a, double b, double c) const { return restar(a,b)-c; }
    double multiplicar(double a, double b) const { return a*b; }
    double multiplicar() const { return multiplicar(primero, segundo); }
    double multiplicar(double a, double b, double c) const { return multiplicar(a,b)*c; }
    double dividir(double a, double b) const {
        if (b == 0) throw std::invalid_argument("No se puede dividir entre cero.");
        return verificarResultado(a/b);
    }
    double dividir() const { return dividir(primero, segundo); }
    double dividir(double a, double b, double c) const { return dividir(dividir(a,b),c); }
};
void ejecutar() {
    double a = leer<double>("a: ", -1e6, 1e6);
    double b = leer<double>("b: ", -1e6, 1e6);
    double c = leer<double>("c: ", -1e6, 1e6);
    Calculadora calc(a,b);
    std::cout << "Orden de columnas: 0 parametros | 2 parametros | 3 parametros\n";
    std::cout << "Suma: " << calc.sumar() << " | " << calc.sumar(a,b) << " | " << calc.sumar(a,b,c) << '\n';
    std::cout << "Resta: " << calc.restar() << " | " << calc.restar(a,b) << " | " << calc.restar(a,b,c) << '\n';
    std::cout << "Multiplicacion: " << calc.multiplicar() << " | " << calc.multiplicar(a,b) << " | " << calc.multiplicar(a,b,c) << '\n';
    // Cada division se comprueba de forma independiente.
    try {
        const double sinParametros = calc.dividir();
        const double dosParametros = calc.dividir(a,b);
        std::cout << "Division (0 y 2 parametros): " << sinParametros << " | " << dosParametros << '\n';
    } catch (const std::exception& e) {
        std::cout << "Division (0 y 2 parametros): " << e.what() << '\n';
    }
    try {
        const double tresParametros = calc.dividir(a,b,c);
        std::cout << "Division (3 parametros): " << tresParametros << '\n';
    } catch (const std::exception& e) {
        std::cout << "Division (3 parametros): " << e.what() << '\n';
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
