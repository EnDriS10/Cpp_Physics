# MATCLUB-CPP (módulos independientes, solo .cpp)

Librería numérica en C++ estilo MATLAB. Esta versión trae:

- **`matclub.cpp`**: la librería completa en un solo archivo (346 funciones).
- **Carpetas por bloque del programa**, con un `.cpp` por contenido. **Cada archivo es independiente**: compila y funciona él solo, sin `.h` y sin necesitar ningún otro archivo de MATCLUB.

## Estructura


### `Bloque_I_Introduccion/`

| Archivo | Contenido | Propias | Copiadas |
|---|---|---|---|
| `mensajes.cpp` | Mensajes de error, aviso e informacion | 6 | 0 |
| `auxiliares.cpp` | Funciones auxiliares y aritmetica basica | 16 | 2 |
| `vectores.cpp` | Vectores (arrays dinamicos) | 73 | 3 |
| `matrices.cpp` | Matrices (arrays dinamicos 2D) | 44 | 2 |
| `ordenacion.cpp` | Ordenacion de vectores (Introsort) | 7 | 1 |
| `aleatorios.cpp` | Numeros aleatorios | 5 | 2 |
| `archivos.cpp` | Manipulacion de archivos | 13 | 4 |

### `Bloque_II_Sistemas_de_Ecuaciones/`

| Archivo | Contenido | Propias | Copiadas |
|---|---|---|---|
| `ceros_funcion.cpp` | Busqueda de ceros de una funcion | 12 | 7 |
| `factorizacion_lu.cpp` | Sistemas lineales: factorizacion LU | 4 | 4 |
| `eliminacion_gauss.cpp` | Sistemas lineales: eliminacion de Gauss y Gauss-Jordan | 2 | 6 |
| `sistemas_tridiagonales.cpp` | Sistemas lineales: matrices tridiagonales | 2 | 2 |
| `determinantes_inversas.cpp` | Determinantes e inversas | 4 | 8 |
| `metodos_iterativos.cpp` | Sistemas lineales: metodos iterativos | 5 | 11 |
| `minimos_cuadrados.cpp` | Sistemas sobredeterminados y regresiones | 7 | 17 |
| `sistemas_no_lineales.cpp` | Sistemas no lineales | 10 | 20 |
| `minimizacion.cpp` | Minimizacion de funciones | 3 | 10 |

### `Bloque_III_Diagonalizacion/`

| Archivo | Contenido | Propias | Copiadas |
|---|---|---|---|
| `autovalores.cpp` | El problema de los autovalores | 7 | 17 |
| `jacobi.cpp` | Diagonalizacion de matrices simetricas: Metodo de Jacobi | 2 | 9 |
| `qr.cpp` | Metodo QR | 5 | 15 |
| `householder.cpp` | Transformacion de Householder (forma de Hessenberg / tridiagonal) | 2 | 4 |
| `eig_general.cpp` | Interfaz general de autovalores y autovectores | 1 | 20 |

### `Bloque_IV_Integracion_Derivacion/`

| Archivo | Contenido | Propias | Copiadas |
|---|---|---|---|
| `integracion.cpp` | Integracion numerica | 31 | 8 |
| `derivacion.cpp` | Derivacion numerica | 38 | 8 |

### `Bloque_V_EDOs/`

| Archivo | Contenido | Propias | Copiadas |
|---|---|---|---|
| `edo_valores_iniciales.cpp` | EDO's con valores iniciales | 8 | 3 |
| `edo_sistemas.cpp` | Sistemas de EDO's y EDO's de orden superior | 7 | 6 |
| `edo_frontera.cpp` | EDO's con condiciones de frontera | 3 | 3 |
| `edps.cpp` | Ecuaciones en derivadas parciales | 4 | 6 |

### `Complementos/`

| Archivo | Contenido | Propias | Copiadas |
|---|---|---|---|
| `interpolacion.cpp` | Interpolacion numerica | 18 | 11 |
| `estadistica.cpp` | Estadistica descriptiva | 7 | 15 |

Además: `INDICE.md` (qué función está en qué archivo), `Ejemplos/ejemplo_uso.cpp` y `Makefile`.

Además: `PENDIENTE.md` (lo que falta por hacer) y el resumen de teoría en Word del Bloque I (`Bloque_I_Introduccion/Resumen_Teoria_Bloque_I.docx`; los de los demás bloques están pendientes).

## Novedades de esta versión

- **Derivación (IV.2):** `part_derv_c`, `part2_derv_c` (derivadas parciales centrales de 3 a 9 puntos, con paso automático óptimo) y los operadores `gradiente`, `divergencia`, `rotacional`, `rotacional_2d` y `laplaciano`. `part_derv` mantiene su firma pero ahora usa centrales de 5 puntos (error O(h^4)); `grad_vect`, `total_derv` y `jacobian_mat` se benefician.
- **Datos tabulados y(x) con x NO uniforme:** familia `_xy` (`integral_xy`, `trapecio_xy`, `simpson13_xy`, `simpson38_xy`, `deriv_xy`, `deriv_xy_3p`, `deriv_xy_5p`, `deriv2_xy_3p`, `deriv2_xy_5p`). La **precisión se elige** por grado/nº de puntos (`integral_xy`, `deriv_xy`) o por tolerancia (`integral_xy_tol`, `deriv_xy_tol`, `integral_adapt`, `deriv_tol`). Las funciones antiguas `*_vect` (con y y h) se conservan sin cambios.
- **Sistemas no lineales (II.3):** `newton_raphson_sys_rango` y `newton_raphson_sys_rango_aleat` devuelven TODAS las soluciones de F(r) = 0 dentro de un rango (a[i], b[i]).
- **Ceros de funciones (II.1):** `falsa_posicion`, `punto_fijo`, `muller`, `newton_modificado`, `aitken`, `punto_fijo_aitken`, `orden_convergencia`.
- **Otras:** `simpson13_comp_func`, `length_vect`, `mat_from_arr`, `lagrange_base`, `lagrange_interp`, `newton_interp`. Desde el Bloque II, todas las funciones tienen descripción breve y ejemplo de uso.

## Cómo se usa

Los módulos **se incluyen con `#include`** en tu programa (igual que hacías con `matclub.cpp`). Incluye solo los que necesites, en cualquier orden:

```cpp
#include "Bloque_I_Introduccion/vectores.cpp"
#include "Bloque_III_Diagonalizacion/jacobi.cpp"

int main() { /* ... */ }
```

Se compila **solo el archivo de tu programa**:

```
g++ mi_programa.cpp -o mi_programa
```

En Dev-C++: crea tu programa (File → New → Source File) en la carpeta `MATCLUB` (o ajusta las rutas del `#include`) y compílalo normalmente.

## Autovalores y autovectores: tú eliges qué obtener

Todos los métodos de diagonalización (Bloque III) comparten las mismas opciones:

```cpp
double *L; double **U;
jacobi_eig(A, n, L, U, calc_autoval, calc_autovec, ordenar, tol, max_iter);
qr_eig    (A, n, L, U, calc_autoval, calc_autovec, ordenar, tol, max_iter, hess);
eig_mat   (A, n, L, U, calc_autoval, calc_autovec, ordenar, tol, max_iter);   // elige Jacobi o QR solo
```

| Opción | Qué hace |
|---|---|
| `calc_autoval` | `true`: `L` = array con los autovalores. `false`: `L = NULL`. |
| `calc_autovec` | `true`: `U` = matriz con los autovectores en las **columnas**. `false`: `U = NULL` y no se calcula (ahorra trabajo). |
| `ordenar` | `true`: ordena por \|autovalor\| decreciente (los autovectores se reordenan con ellos). |
| `hess` (solo QR) | Reducción previa: `0` ninguna, `1` Hessenberg por Householder, `2` Hessenberg por eliminación. |

Ejemplos: `jacobi_eig(A,n,L,U,true,true,true,1e-12,1000)` (todo, ordenado), `qr_eig(A,n,L,U,true,false,false,1e-12,5000,1)` (solo autovalores), `eig_mat(A,n,L,U,false,true,false,1e-12,5000)` (solo autovectores).
Los métodos devuelven el número de iteraciones (o `-1` si hay error). Las reducciones `hessenberg_mat` y `hessenberg_householder_mat` también permiten elegir si quieres la matriz de transformación (`calc_P` / `calc_Q`).

## Cómo funciona la independencia

- Si un módulo usa funciones de otro (por ejemplo, `print_error` o `zeros_mat`), **las lleva copiadas** en su sección `DEPENDENCIAS`, tal cual están en `matclub.cpp`. La cabecera de cada archivo dice cuáles son.
- Cada función está protegida con `#ifndef MC_FN_<nombre>`. Así puedes incluir varios módulos a la vez aunque compartan funciones: la segunda copia se ignora.
- Un módulo solo contiene **sus** funciones y las que necesitan. Si en tu programa quieres usar, por ejemplo, `zeros_mat` junto con `jacobi.cpp`, incluye también `Bloque_I_Introduccion/matrices.cpp`.

## Qué NO hacer

- **No añadas estos `.cpp` como archivos de un proyecto** (ni los compiles por separado y los enlaces juntos): cada uno lleva sus propias copias y darían errores de definición duplicada. Se usan con `#include`.
- **No mezcles `matclub.cpp` con los módulos** en el mismo programa: usa uno u otro.

## Comprobar que todo compila

```
make comprobar      # cada modulo compila SOLO
make ejemplo        # compila Ejemplos/ejemplo_uso.cpp
```
