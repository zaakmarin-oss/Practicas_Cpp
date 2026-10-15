#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

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

// Se usan enteros para que la division por restas tenga cociente y residuo.
// Dominio didactico: a [-100,100], b [-9,9]; potencia exige b >= 0.
// Se conservan las variantes de 0, 2 y 3 parametros de la practica anterior.
class Calculadora {
protected:
    long long primero, segundo;
public:
    Calculadora(long long a, long long b) : primero(a), segundo(b) {}
    virtual ~Calculadora() = default;
    long long sumar(long long a, long long b) const { return a+b; }
    long long sumar() const { return sumar(primero,segundo); }
    long long sumar(long long a,long long b,long long c) const { return sumar(a,b)+c; }
    long long restar(long long a, long long b) const { return a-b; }
    long long restar() const { return restar(primero,segundo); }
    long long restar(long long a,long long b,long long c) const { return restar(a,b)-c; }
    virtual long long multiplicar(long long a,long long b) const { return a*b; }
    long long multiplicar() const { return multiplicar(primero,segundo); }
    long long multiplicar(long long a,long long b,long long c) const { return multiplicar(multiplicar(a,b),c); }
    virtual long long dividir(long long a,long long b) const {
        if (b==0) throw std::invalid_argument("No se puede dividir entre cero.");
        return a/b;
    }
    long long dividir() const { return dividir(primero,segundo); }
    long long dividir(long long a,long long b,long long c) const { return dividir(dividir(a,b),c); }
    virtual long long potencia(long long a,long long b) const {
        if (b<0) throw std::invalid_argument("El exponente debe ser no negativo.");
        // La base usa exponenciacion binaria; la derivada usara multiplicaciones sucesivas.
        long long resultado=1;
        while (b>0) { if (b%2==1) resultado*=a; b/=2; if (b>0) a*=a; }
        return resultado;
    }
};
class CalculadoraNueva : public Calculadora {
public:
    using Calculadora::Calculadora;
    using Calculadora::multiplicar; // Evita ocultar las otras sobrecargas.
    using Calculadora::dividir;
    long long multiplicar(long long a,long long b) const override {
        long long resultado=0, veces=(b<0 ? -b:b);
        for (long long i=0;i<veces;++i) resultado+=a;
        return b<0 ? -resultado:resultado;
    }
    long long potencia(long long a,long long b) const override {
        if (b<0) throw std::invalid_argument("El exponente debe ser no negativo.");
        long long resultado=1; // Convencion de esta practica: 0^0 = 1.
        for (long long i=0;i<b;++i) resultado*=a;
        return resultado;
    }
    long long dividir(long long a,long long b) const override {
        if (b==0) throw std::invalid_argument("No se puede dividir entre cero.");
        long long resto=(a<0 ? -a:a), divisor=(b<0 ? -b:b), cociente=0;
        while (resto>=divisor) { resto-=divisor; ++cociente; }
        return (a<0)!=(b<0) ? -cociente:cociente;
    }
};
void ejecutar() {
    long long a=leer<long long>("a (entero -100 a 100): ",-100,100);
    long long b=leer<long long>("b (entero -9 a 9): ",-9,9);
    CalculadoraNueva nueva(a,b);
    const Calculadora& calculadora=nueva; // Polimorfismo: ejecuta los override.
    std::cout << "Multiplicacion por sumas: " << calculadora.multiplicar(a,b) << '\n';
    if (b>=0) std::cout << "Potencia por multiplicaciones: " << calculadora.potencia(a,b) << '\n';
    else std::cout << "Potencia omitida: exponente negativo.\n";
    if (b!=0) {
        long long q=calculadora.dividir(a,b);
        std::cout << "Cociente entero: " << q << " | Residuo: " << a-q*b << '\n';
    } else std::cout << "Division omitida: divisor cero.\n";
    std::cout << "Sobrecarga de 0 parametros: " << nueva.multiplicar() << '\n';
    std::cout << "Sobrecarga de 3 parametros (a,b,2): " << nueva.multiplicar(a,b,2) << '\n';
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
