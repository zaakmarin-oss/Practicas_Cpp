# Tus ocho prácticas de C++

Los ocho archivos son independientes y tienen su propio `main()`. Ya no necesitan `../apoyo/entrada.hpp`. Conservan los ejercicios y los conceptos de los originales.

**Compila y ejecuta un solo archivo `.cpp` a la vez.** No agregues los ocho al mismo proyecto ejecutable ni uses `g++ *.cpp`: eso produce un error por tener varios `main()`.

## Abrir directamente en Visual Studio

1. Extrae todo el ZIP.
2. Abre **`Practicas_Cpp.sln`** con doble clic. También puedes usar **Abrir un proyecto o una solución** desde Visual Studio.
3. Haz clic derecho sobre la práctica deseada y selecciona **Establecer como proyecto de inicio**.
4. Pulsa **Ctrl + F5**.

La solución ya incluye los ocho proyectos separados, con C++17 y salida de consola configurados. Puedes compilar la solución completa: cada práctica genera su propio ejecutable. Para ver el código, expande el proyecto y **Archivos de codigo fuente**. Conserva toda la carpeta extraída para que funcionen las rutas.

Necesitas tener instalada la carga **Desarrollo para el escritorio con C++**. Se utiliza el conjunto de herramientas predeterminado de tu instalación. La estructura de la solución se verificó; la apertura en Visual Studio/MSVC queda pendiente de comprobar en Windows.

Las instrucciones para crear proyectos manualmente que aparecen más abajo son una alternativa; con esta solución ya están preparados.

## Alternativa: lanzador de Windows

1. Extrae todo el ZIP en una carpeta; no ejecutes los archivos desde dentro del ZIP.
2. Si ya tienes **g++ instalado y configurado en PATH**, abre `EJECUTAR_WINDOWS.bat` con doble clic.
3. Elige del 1 al 8 para compilar y ejecutar una práctica. Introduce un dato por línea y pulsa Enter después de cada dato.
4. Al terminar, el lanzador mantiene la ventana abierta y permite elegir otra práctica. Usa 0 para salir.

El lanzador también admite el compilador de Visual Studio (`cl`) cuando lo abres desde **Developer Command Prompt for Visual Studio**. No instala compiladores. Si no encuentra ninguno, muestra qué falta.

Los `.exe` se generan dentro de `bin` en tu computadora. El paquete contiene código fuente y no incluye ejecutables de Windows compilados aquí.

## Si utilizas Visual Studio Code

VS Code es un editor: necesitas un compilador de C++ aparte. En una terminal escribe:

```powershell
g++ --version
```

Si muestra una versión, abre la carpeta de las prácticas en VS Code, abre una terminal integrada y prueba:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic p1_03_calculadora.cpp -o calculadora.exe
.\calculadora.exe
```

Para otra práctica, sustituye el nombre del `.cpp` y del `.exe`. Escribe las respuestas en la **terminal**, que permite entrada interactiva. Si aparece “g++ no se reconoce”, falta instalar el compilador o agregar su carpeta `bin` al PATH; vuelve a abrir VS Code después de configurarlo.

## Si utilizas Visual Studio

1. Ten instalada la carga de trabajo **Desarrollo para el escritorio con C++**.
2. Crea un **Proyecto vacío de C++**.
3. En Archivos de código fuente, agrega como elemento existente **uno** de estos `.cpp`.
4. Selecciona el estándar **ISO C++17** en las propiedades del proyecto, en C/C++ → Lenguaje.
5. Ejecuta con **Ctrl + F5**.

Si creaste un proyecto que ya trae otro archivo con `main()`, quita ese archivo del proyecto. Para cambiar de práctica, usa otro proyecto vacío o deja un solo `.cpp` incluido en la compilación.

## Linux

Con g++ instalado, desde la carpeta del paquete:

```bash
bash ejecutar.sh
```

O compila una práctica directamente:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic p1_03_calculadora.cpp -o calculadora
./calculadora
```

## Reglas de captura

- Introduce un dato por línea. No pegues varios números separados por espacios en una sola respuesta.
- Los números decimales aceptan punto o coma: `2.5` y `2,5` significan lo mismo. No uses separadores de miles.
- Las opciones, dimensiones, cantidades y edades deben ser enteros; por ejemplo, escribe `2`, no `2.0`.
- Si escribes letras donde se pide un número, dejas una respuesta vacía o sales del rango permitido, el programa vuelve a preguntar.
- Los nombres y apellidos permiten espacios. Los campos de texto no pueden quedar vacíos.
- Si cierras la entrada antes de completar los datos, el programa muestra un mensaje y termina sin quedarse en un ciclo infinito.
- Los resultados con `double` son aproximaciones numéricas; se muestran hasta 12 cifras significativas. Puede aparecer notación científica para valores muy grandes o pequeños.

## Qué hace cada programa y cómo comprobarlo

### 1. Calculadora — `p1_03_calculadora.cpp`

Usa funciones, parámetros y un menú: 1 sumar, 2 restar, 3 multiplicar, 4 dividir y 0 salir. Los dos operandos están entre −1,000,000 y 1,000,000. El menú se repite para hacer varias operaciones.

**Ejemplo:** opción `1`, primer número `8`, segundo número `3` → `Resultado: 11`. Para cerrar, escribe `0` cuando vuelva a aparecer el menú.

La división entre cero muestra un aviso y permite seguir usando la calculadora. Una división cuyo resultado desborde `double` también se informa.

### 2. Sobrecarga — `p1_04_sobrecarga.cpp`

La clase `Calculadora` ofrece operaciones con el mismo nombre y con 0, 2 y 3 parámetros. Las versiones sin parámetros utilizan los dos valores guardados en el objeto. Captura `a`, `b` y `c`, cada uno entre −1,000,000 y 1,000,000.

**Ejemplo:** `a = 12`, `b = 3`, `c = 2`.

| Operación | 0 parámetros | 2 parámetros | 3 parámetros |
|---|---:|---:|---:|
| Suma | 15 | 15 | 17 |
| Resta | 9 | 9 | 7 |
| Multiplicación | 36 | 36 | 72 |
| División | 4 | 4 | 2 |

La resta de tres valores es `(a - b) - c`; la división es `(a / b) / c`. Si `b` o `c` es cero, se indica qué división no puede hacerse, sin perder los otros resultados.

### 3. Herencia y sobreescritura — `p1_06_herencia_sobreescritura.cpp`

`CalculadoraNueva` hereda de `Calculadora`. Sobreescribe la multiplicación con sumas repetidas, la división con restas repetidas y la potencia con multiplicaciones. Una referencia a la clase base permite comprobar el polimorfismo.

**Ejemplo:** `a = 12`, `b = 3` → multiplicación `36`, potencia `1728`, cociente `4`, residuo `0`, multiplicación sin parámetros `36` y con tres parámetros `(12, 3, 2)` igual a `72`.

- `a` debe ser un entero de −100 a 100; `b`, de −9 a 9. Estos límites evitan desbordar `long long` en las potencias admitidas.
- La división es **entera**, con truncamiento hacia cero: `−13 / 3` produce cociente `−4` y residuo `−1`. Se cumple `a = cociente × b + residuo`.
- Con `b < 0`, se omite la potencia, pero sí se calcula la multiplicación y la división.
- Con `b = 0`, se omite la división. La práctica utiliza la convención informática `0^0 = 1`.

### 4. Tamaños — `p1_07bis_tamanos.cpp`

No pide datos. Usa `sizeof` para mostrar cuántos bytes ocupan tipos básicos, un puntero, `std::string`, estructuras y clases.

**El resultado correcto depende del compilador y de la plataforma.** Por ejemplo, `sizeof(char)` siempre es 1, pero no debes esperar el mismo tamaño de `long`, `std::string` u otros objetos en Windows y Linux. El tamaño puede incluir relleno de alineación; `sizeof(std::string)` no suma el almacenamiento dinámico de su texto. Tener métodos no significa que cada objeto guarde una copia de ellos.

### 5. Estadísticas — `p1_09_estadisticas_arreglo.cpp`

Captura cinco números en un arreglo, recorre sus elementos y calcula suma, media aritmética, mínimo y máximo. Ordena una copia para obtener la mediana sin cambiar el arreglo original. Admite valores entre −1,000,000 y 1,000,000.

**Ejemplo:** introduce `1`, `2`, `3`, `4`, `5` → suma `15`, promedio `3`, mínimo `1`, máximo `5` y mediana `3`.

### 6. Matrices — `p1_11_matrices.cpp`

Captura las filas y columnas de A y B, sus elementos por filas y una constante. Calcula `A × constante` y, si las dimensiones lo permiten, `A × B`. Cada dimensión va de 1 a 5; los elementos y la constante, de −1000 a 1000. Los índices empiezan en cero: `A[0][0]` es la primera celda.

**Ejemplo:** ambas matrices de 2 × 2. Captura A con `1, 2, 3, 4`, B con `5, 6, 7, 8` y constante `2`, siempre un número por línea.

```text
A por constante:
  2  4
  6  8

A por B:
  19  22
  43  50
```

En el producto, cada celda resulta de multiplicar una fila de A por una columna de B y sumar. Por ejemplo, `19 = 1×5 + 2×7`. Las columnas de A deben coincidir con las filas de B. Si no coinciden, se muestra un aviso; el producto por constante sigue disponible.

### 7. Personas y punteros — `p1_13_personas_punteros.cpp`

Captura de 1 a 10 personas con nombre, apellidos, género y edad de 0 a 130. Usa un arreglo de estructuras (PE) y otro de objetos (POO), con acceso mediante punteros. La información se imprime dos veces para comparar los enfoques.

**Ejemplo:** cantidad `1`; nombre `Isaac`; apellido paterno `Marin`; apellido materno `Nolasco`; género `Masculino`; edad `22` (dato de ejemplo).

En PE y POO debe aparecer `Isaac Marin Nolasco | Masculino | 22 anios`.

`inicio + i` apunta a la persona en la posición `i`; `p->edad` accede a su edad. Los arreglos tienen duración automática: no se utiliza `delete` para liberarlos.

### 8. Fractales — `p1_15_fractales.cpp`

Captura un nivel de recursión de 0 a 6. Genera el triángulo de Sierpinski y aproximaciones finitas del conjunto de Cantor en **`fractales.svg`**.

**Ejemplo:** escribe `4`. El programa muestra la ruta completa del SVG. Ábrelo con Chrome, Edge, Firefox u otro navegador para ver el dibujo. Si usas el lanzador, se guarda en la carpeta de las prácticas. No se abre una ventana gráfica automáticamente.

En el nivel 4 aparecen 81 triángulos y 31 segmentos de Cantor repartidos entre las filas de aproximación. También se incluye `ejemplos/fractales_nivel_4.svg`, generado al probar el programa.

Cada ejecución vuelve a escribir `fractales.svg`; renómbralo antes si quieres conservar varios niveles. La carpeta debe permitir crear archivos.

## Correcciones realizadas y verificación

Se sustituyó el encabezado faltante por los includes y las funciones de entrada necesarios en cada archivo. Se añadieron validación de respuestas completas, recuperación ante entradas inválidas, control de fin de entrada, protección frente a desbordamiento en divisiones, mayor precisión de salida, separación legible de columnas de matrices y la ruta del dibujo generado.

Los ocho programas se compilaron y ejecutaron con g++ 13.3.0 en Linux usando C++17. Se comprobaron resultados normales, límites y errores de entrada. El detalle está en `RESULTADOS_PRUEBAS.txt`. El código utiliza bibliotecas estándar de C++; la ejecución en Windows/MSVC y el lanzador `.bat` no se pudieron probar en este entorno.
