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

#include <fstream>
#include <filesystem>
void sierpinski(std::ostream& out,double x,double y,double lado,int nivel) {
    const double alto=lado*std::sqrt(3.0)/2;
    if (nivel==0) { // Caso base: dibujar un triangulo.
        out << "<polygon points='" << x << ',' << y << ' ' << x-lado/2 << ',' << y+alto
            << ' ' << x+lado/2 << ',' << y+alto << "' fill='#1557b0'/>\n";
        return;
    }
    sierpinski(out,x,y,lado/2,nivel-1);
    sierpinski(out,x-lado/4,y+alto/2,lado/2,nivel-1);
    sierpinski(out,x+lado/4,y+alto/2,lado/2,nivel-1);
}
void cantor(std::ostream& out,double x,double y,double largo,int nivel) {
    out << "<rect x='" << x << "' y='" << y << "' width='" << largo << "' height='7' fill='#b32626'/>\n";
    if (nivel==0) return; // No subdividir mas.
    cantor(out,x,y+22,largo/3,nivel-1);
    cantor(out,x+2*largo/3,y+22,largo/3,nivel-1);
}
void ejecutar() {
    int nivel=leer<int>("Nivel de recursion (0 a 6): ",0,6);
    std::ofstream out("fractales.svg");
    if (!out) throw std::runtime_error("No se pudo crear fractales.svg.");
    out << std::setprecision(12);
    out << "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 720 850'>\n"
           "<rect width='720' height='850' fill='white'/>\n"
           "<text x='60' y='35' font-size='22'>Triangulo de Sierpinski</text>\n";
    sierpinski(out,360,60,600,nivel);
    out << "<text x='60' y='630' font-size='22'>Polvo de Cantor - aproximaciones finitas</text>\n";
    cantor(out,60,650,600,nivel);
    out << "</svg>\n";
    out.close();
    if (!out) throw std::runtime_error("Fallo al guardar el SVG.");
    std::cout << "Creado: " << std::filesystem::absolute("fractales.svg").string() << '\n'
              << "Abre el archivo en tu navegador para ver los dibujos.\n"
              << "Cada nivel aproxima el fractal; el conjunto ideal requiere infinitos pasos.\n";
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
