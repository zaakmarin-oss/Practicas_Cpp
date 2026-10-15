@echo off
setlocal
chcp 65001 >nul
pushd "%~dp0"
if not exist "bin" mkdir "bin"
where g++ >nul 2>nul
if not errorlevel 1 goto usar_gcc
where cl >nul 2>nul
if not errorlevel 1 goto usar_msvc
echo No se encontro un compilador de C++.
echo Si usas VS Code, necesitas g++ instalado y disponible en PATH.
echo Si usas Visual Studio, abre Developer Command Prompt y ejecuta este archivo.
echo Consulta LEEME.md para las instrucciones.
pause
popd
exit /b 1

:usar_gcc
set "compilador=gcc"
goto menu
:usar_msvc
set "compilador=msvc"

:menu
echo.
echo PRACTICAS DE C++
echo 1. Calculadora
echo 2. Sobrecarga
echo 3. Herencia y sobreescritura
echo 4. Tamanos de tipos y objetos
echo 5. Estadisticas de un arreglo
echo 6. Matrices
echo 7. Personas y punteros
echo 8. Fractales
echo 0. Salir
choice /C 123456780 /N /M "Elige una opcion: "
if errorlevel 255 goto fin
if errorlevel 9 goto fin
if errorlevel 8 goto practica8
if errorlevel 7 goto practica7
if errorlevel 6 goto practica6
if errorlevel 5 goto practica5
if errorlevel 4 goto practica4
if errorlevel 3 goto practica3
if errorlevel 2 goto practica2
if errorlevel 1 goto practica1
goto fin

:practica1
set "programa=p1_03_calculadora"
goto compilar
:practica2
set "programa=p1_04_sobrecarga"
goto compilar
:practica3
set "programa=p1_06_herencia_sobreescritura"
goto compilar
:practica4
set "programa=p1_07bis_tamanos"
goto compilar
:practica5
set "programa=p1_09_estadisticas_arreglo"
goto compilar
:practica6
set "programa=p1_11_matrices"
goto compilar
:practica7
set "programa=p1_13_personas_punteros"
goto compilar
:practica8
set "programa=p1_15_fractales"
goto compilar

:compilar
echo.
echo Compilando %programa%.cpp...
if "%compilador%"=="msvc" goto compilar_msvc
g++ -std=c++17 -Wall -Wextra -Wpedantic "%programa%.cpp" -o "bin\%programa%.exe"
if errorlevel 1 goto error_compilacion
goto ejecutar

:compilar_msvc
cl /nologo /std:c++17 /EHsc /W4 /utf-8 "%programa%.cpp" /Fe:"bin\%programa%.exe" /Fo:"bin\%programa%.obj"
if errorlevel 1 goto error_compilacion

:ejecutar
echo Introduce un dato por linea y pulsa Enter.
echo.
"bin\%programa%.exe"
if errorlevel 1 echo El programa termino con un error. Revisa el mensaje anterior.
echo.
pause
goto menu

:error_compilacion
echo No se pudo compilar. Revisa los mensajes anteriores y LEEME.md.
pause
goto menu

:fin
popd
endlocal
exit /b 0
