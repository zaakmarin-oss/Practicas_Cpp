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

#include <vector>
#include <algorithm>
using Matriz=std::vector<std::vector<double>>;
Matriz capturar(const std::string& nombre,int filas,int columnas) {
    Matriz m(filas,std::vector<double>(columnas));
    for (int i=0;i<filas;++i) for (int j=0;j<columnas;++j)
        m[i][j]=leer<double>(nombre+"["+std::to_string(i)+"]["+std::to_string(j)+"]: ",-1000,1000);
    return m;
}
Matriz porConstante(const Matriz& a,double k) {
    Matriz r=a;
    for (auto& fila:r) for (double& valor:fila) valor*=k;
    return r;
}
void validar(const Matriz& m) {
    if (m.empty() || m.front().empty())
        throw std::invalid_argument("La matriz no puede estar vacia.");
    for (const auto& fila : m)
        if (fila.size() != m.front().size())
            throw std::invalid_argument("Todas las filas deben tener igual numero de columnas.");
}
Matriz multiplicar(const Matriz& a,const Matriz& b) {
    validar(a);
    validar(b);
    if (a[0].size()!=b.size()) throw std::invalid_argument("Columnas de A deben ser iguales a filas de B.");
    Matriz r(a.size(),std::vector<double>(b[0].size(),0));
    for (std::size_t i=0;i<a.size();++i)
        for (std::size_t j=0;j<b[0].size();++j)
            for (std::size_t k=0;k<b.size();++k) r[i][j]+=a[i][k]*b[k][j];
    return r;
}
void mostrar(const Matriz& m) {
    // Ajusta el ancho para que ningun numero se pegue al siguiente.
    std::size_t ancho = 1;
    for (const auto& fila : m) for (double valor : fila) {
        std::ostringstream celda;
        celda << std::setprecision(12) << valor;
        ancho = std::max(ancho, celda.str().size());
    }
    for (const auto& fila : m) {
        for (double valor : fila)
            std::cout << std::setw(static_cast<int>(ancho + 2)) << valor;
        std::cout << '\n';
    }
}
void ejecutar() {
    int fa=leer<int>("Filas de A (1 a 5): ",1,5);
    int ca=leer<int>("Columnas de A (1 a 5): ",1,5);
    int fb=leer<int>("Filas de B (1 a 5): ",1,5);
    int cb=leer<int>("Columnas de B (1 a 5): ",1,5);
    Matriz a=capturar("A",fa,ca), b=capturar("B",fb,cb);
    double k=leer<double>("Constante: ",-1000,1000);
    std::cout << "A por constante:\n"; mostrar(porConstante(a,k));
    if (ca!=fb) { std::cout << "No se puede calcular A por B: dimensiones incompatibles.\n"; return; }
    std::cout << "A por B:\n"; mostrar(multiplicar(a,b));
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
