// Archivo independiente: no requiere entrada.hpp ni bibliotecas externas.
// Compilar con C++17. Introduce un dato por linea y pulsa Enter.
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

// Repite la pregunta si la entrada no es un numero completo dentro del rango.
// getline evita que letras sobrantes afecten a la siguiente pregunta.
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

#include <algorithm>
void ejecutar() {
    const int N=5;
    double numeros[N]; // Cinco datos dentro de un solo arreglo.
    for (int i=0;i<N;++i)
        numeros[i]=leer<double>("Numero "+std::to_string(i+1)+": ",-1e6,1e6);
    double suma=0, minimo=numeros[0], maximo=numeros[0];
    for (int i=0;i<N;++i) {
        suma+=numeros[i];
        if (numeros[i]<minimo) minimo=numeros[i];
        if (numeros[i]>maximo) maximo=numeros[i];
    }
    std::cout << "Suma: " << suma << "\nPromedio / media aritmetica: " << suma/N
              << "\nMinimo: " << minimo << "\nMaximo: " << maximo << '\n';
    // Media y promedio son sinonimos aqui. Mediana se agrega como dato extra.
    double copia[N]; std::copy(numeros,numeros+N,copia); std::sort(copia,copia+N);
    std::cout << "Mediana (extra): " << copia[N/2] << '\n';
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
