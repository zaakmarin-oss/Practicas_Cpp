// Archivo independiente. Compilar con C++17.
#include <iostream>
#include <string>
#include <stdexcept>

#include <climits>
#include <iomanip>
// PE: estructuras con campos publicos y funciones externas.
struct AutoPE { double precio; int anio; };
struct PersonaPE { std::string nombre,paterno,materno,genero; int edad; };
// POO: atributos privados; metodos publicos para operar con el objeto.
class AutoPOO {
    double precio=0; int anio=0;
public:
    void establecer(double p,int a) { precio=p; anio=a; }
    double obtenerPrecio() const { return precio; }
};
class PersonaPOO {
    std::string nombre,paterno,materno,genero; int edad=0;
public:
    void establecerEdad(int valor) { edad=valor; }
    int obtenerEdad() const { return edad; }
};
template<class T> void mostrar(const std::string& tipo) {
    std::cout << std::left << std::setw(22) << tipo << sizeof(T) << " bytes\n";
}
void ejecutar() {
    std::cout << "Bits por byte en este sistema: " << CHAR_BIT << "\n\n";
    mostrar<bool>("bool"); mostrar<char>("char"); mostrar<short>("short");
    mostrar<int>("int"); mostrar<long>("long"); mostrar<long long>("long long");
    mostrar<float>("float"); mostrar<double>("double"); mostrar<long double>("long double");
    mostrar<int*>("int* (puntero)"); mostrar<std::string>("std::string");
    mostrar<AutoPE>("AutoPE"); mostrar<AutoPOO>("AutoPOO");
    mostrar<PersonaPE>("PersonaPE"); mostrar<PersonaPOO>("PersonaPOO");
    std::cout << "\nsizeof depende del compilador y la plataforma.\n"
              << "Puede incluir relleno (padding); no suma toda la memoria dinamica de string.\n";
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
