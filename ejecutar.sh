#!/usr/bin/env bash
set -u
cd -- "$(dirname -- "$0")" || exit 1
if ! command -v g++ >/dev/null 2>&1; then
    echo 'Falta g++: instala un compilador de C++ antes de ejecutar las practicas.'
    exit 1
fi
mkdir -p bin || exit 1
while true; do
    cat <<'MENU'

PRACTICAS DE C++
1. Calculadora
2. Sobrecarga
3. Herencia y sobreescritura
4. Tamanos de tipos y objetos
5. Estadisticas de un arreglo
6. Matrices
7. Personas y punteros
8. Fractales
0. Salir
MENU
    read -r -p 'Elige una opcion: ' opcion || exit 0
    case "$opcion" in
        1) programa=p1_03_calculadora ;;
        2) programa=p1_04_sobrecarga ;;
        3) programa=p1_06_herencia_sobreescritura ;;
        4) programa=p1_07bis_tamanos ;;
        5) programa=p1_09_estadisticas_arreglo ;;
        6) programa=p1_11_matrices ;;
        7) programa=p1_13_personas_punteros ;;
        8) programa=p1_15_fractales ;;
        0) exit 0 ;;
        *) echo 'Opcion invalida.'; continue ;;
    esac
    if g++ -std=c++17 -Wall -Wextra -Wpedantic "$programa.cpp" -o "bin/$programa"; then
        echo 'Introduce un dato por linea y pulsa Enter.'
        "./bin/$programa"
    else
        echo 'Error de compilacion. Revisa el mensaje anterior.'
    fi
done
