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

std::string leerTexto(const std::string& mensaje) {
    for (;;) {
        std::cout << mensaje << std::flush;
        std::string linea;
        if (!std::getline(std::cin, linea))
            throw std::runtime_error("Entrada finalizada antes de completar los datos.");
        const auto inicio = linea.find_first_not_of(" \t\r");
        if (inicio != std::string::npos) {
            const auto fin = linea.find_last_not_of(" \t\r");
            return linea.substr(inicio, fin - inicio + 1);
        }
        std::cout << "El texto no puede estar vacio.\n";
    }
}

struct PersonaPE { std::string nombre,paterno,materno,genero; int edad; };
void mostrar(const PersonaPE* p) {
    std::cout << p->nombre << ' ' << p->paterno << ' ' << p->materno
              << " | " << p->genero << " | " << p->edad << " anios\n";
}
class PersonaPOO {
    std::string nombre,paterno,materno,genero; int edad=0;
public:
    void asignar(const PersonaPE& p) {
        nombre=p.nombre; paterno=p.paterno; materno=p.materno; genero=p.genero; edad=p.edad;
    }
    void mostrar() const {
        std::cout << nombre << ' ' << paterno << ' ' << materno << " | " << genero << " | " << edad << " anios\n";
    }
};
void ejecutar() {
    const int CAPACIDAD=10;
    PersonaPE personas[CAPACIDAD]; PersonaPOO objetos[CAPACIDAD];
    int n=leer<int>("Cantidad de personas (1 a 10): ",1,CAPACIDAD);
    PersonaPE* inicio=personas;
    for (int i=0;i<n;++i) {
        PersonaPE* p=inicio+i; // Aritmetica de punteros: avanzar i personas.
        std::cout << "\nPersona " << i+1 << '\n';
        p->nombre=leerTexto("Nombre: "); p->paterno=leerTexto("Apellido paterno: ");
        p->materno=leerTexto("Apellido materno: "); p->genero=leerTexto("Genero: ");
        p->edad=leer<int>("Edad: ",0,130);
        (objetos+i)->asignar(*p);
    }
    std::cout << "\nPE - acceso indirecto:\n";
    for (const PersonaPE* p=inicio;p<inicio+n;++p) mostrar(p);
    std::cout << "POO - acceso indirecto:\n";
    for (int i=0;i<n;++i) (objetos+i)->mostrar();
    // Los arreglos son automaticos; no se usa delete para estas direcciones.
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
