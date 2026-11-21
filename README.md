<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0f2027,50:203a43,100:2c5364&height=220&section=header&text=Cpp%20Physics&fontSize=70&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=Computaci%C3%B3n%20II%20%C2%B7%20C%2B%2B%20y%20M%C3%A9todos%20Num%C3%A9ricos%20para%20F%C3%ADsica&descAlignY=60&descSize=20" alt="Cpp Physics banner"/>

[![C++](https://img.shields.io/badge/C++-11%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Grado](https://img.shields.io/badge/Grado_en-F%C3%ADsica-6C3483?style=for-the-badge&logo=atom&logoColor=white)](#)
[![Curso](https://img.shields.io/badge/2%C2%BA_curso-Computaci%C3%B3n_II-2C5364?style=for-the-badge)](#)
[![Pr%C3%A1cticas](https://img.shields.io/badge/pr%C3%A1cticas-19%2F19-2ea44f?style=for-the-badge)](#-pr%C3%A1cticas)
[![Ex%C3%A1menes](https://img.shields.io/badge/ex%C3%A1menes-2013--2025-e67e22?style=for-the-badge)](#-ex%C3%A1menes)

**Todo el curso de Computación II en un solo repositorio:**
teoría, 19 prácticas resueltas, una librería propia de álgebra lineal y años de exámenes.

[📚 Temario](#-temario) · [🧪 Prácticas](#-prácticas) · [🧰 Matclub](#-matclub-mi-minilibrería-numérica) · [📝 Exámenes](#-exámenes) · [🚀 Cómo compilar](#-cómo-compilar-y-ejecutar) · [📖 Bibliografía](#-bibliografía)

</div>

---

## ✨ ¿Qué es esto?

Repositorio de la asignatura **Computación II** del segundo curso del Grado en Física. Aquí está todo lo que he ido haciendo para aprender a **programar en C++** y, sobre todo, a **resolver con el ordenador problemas de física que no tienen (o es muy difícil que tengan) solución analítica**: desde entender por qué `0.1 + 0.2 ≠ 0.3`, hasta integrar la órbita de la Tierra o los modos normales de un edificio durante un terremoto.

> *"Los ordenadores no hacen matemáticas exactas: hacen aritmética finita. Entender la diferencia es el primer paso del cálculo numérico."*

| | |
|---|---|
| 🧱 **Bloques** | 5 (Introducción → Sistemas de ecuaciones → Autovalores → Integración y derivación → EDOs) |
| 🧪 **Prácticas** | 19, de la suma de series al método del disparo |
| 🧰 **Librería propia** | `matclub`, con vectores, matrices, estadística y utilidades estilo MATLAB |
| 📝 **Exámenes** | Parciales, controles y finales de 2013 a 2025 |
| 💻 **Lenguaje** | C++ (compilado con g++/MinGW) |

---

## 🗺️ Hoja de ruta del curso

```mermaid
flowchart LR
    A["🧱 Bloque I<br/>Aritmética y C++"] --> B["🎯 Bloque II<br/>Sistemas de ecuaciones"]
    B --> C["🌀 Bloque III<br/>Autovalores"]
    C --> D["∫ Bloque IV<br/>Integración y derivación"]
    D --> E["🌍 Bloque V<br/>EDOs"]
    style A fill:#1f6feb,color:#fff,stroke:none
    style B fill:#8957e5,color:#fff,stroke:none
    style C fill:#db61a2,color:#fff,stroke:none
    style D fill:#e67e22,color:#fff,stroke:none
    style E fill:#2ea44f,color:#fff,stroke:none
```

---

## 📚 Temario

<table>
<tr>
<td width="50%" valign="top">

### 🧱 Bloque I · Introducción
- **I.1** Aritmética en el ordenador: números enteros y de coma flotante
- **I.2** Errores numéricos: definición, fuentes, ejemplos
- **I.3** Introducción a lenguajes de programación (C++, …)

📁 [`Tema1/`](Tema1) · [Teoría](Tema1/Teoria) · [Ejemplos](Tema1/Codigos_Ejemplo)

</td>
<td width="50%" valign="top">

### 🎯 Bloque II · Sistemas de ecuaciones
- **II.1** Búsqueda de ceros de una función
- **II.2** Sistemas lineales: métodos directos e iterativos
- **II.3** Sistemas no lineales: Newton-Raphson. Minimización de funciones: gradiente conjugado

📁 [`Tema2/`](Tema2) · [Teoría](Tema2/Teoria)

</td>
</tr>
<tr>
<td width="50%" valign="top">

### 🌀 Bloque III · Diagonalización
- **III.1** El problema de los autovalores
- **III.2** Matrices simétricas: método de **Jacobi**
- **III.3** Matrices tridiagonales: método **QR**
- **III.4** Simétricas → tridiagonales: método de **Householder**

📁 [`Tema3/`](Tema3) · [Teoría](Tema3/Teoria)

</td>
<td width="50%" valign="top">

### ∫ Bloque IV · Integración y derivación
- **IV.1** Integración numérica: Newton-Côtes y Simpson; cuadraturas gaussianas
- **IV.2** Derivación numérica

📁 [`Tema4/`](Tema4) · [Teoría](Tema4/Teoria)

</td>
</tr>
<tr>
<td colspan="2" valign="top">

### 🌍 Bloque V · Ecuaciones diferenciales ordinarias
- **V.1** EDOs con valores iniciales: métodos de **Euler** y de **Runge-Kutta**
- **V.2** Sistemas de EDOs de primer orden y EDOs de orden superior
- **V.3** EDOs con condiciones de frontera

📁 [`Tema5/`](Tema5) · [Teoría](Tema5/Teoria)

</td>
</tr>
</table>

---

## 🧪 Prácticas

Cada práctica vive en su carpeta `Pra_N/` con el enunciado en PDF, el código `.cpp` y, cuando toca, los datos (`.dat`) y las soluciones.

### 🧱 Bloque I · Aritmética y C++

| Nº | Práctica | Qué se aprende | Carpeta |
|:--:|---|---|:--:|
| 1 | **Series y errores numéricos** | Suma hacia delante vs. hacia atrás en simple y doble precisión, números de Armstrong, factoriales con enteros y reales | [📂](Tema1/Practic/Pra_1) |
| 2 | **Series de Taylor, bucles y ficheros** | `exp(x)` por Taylor con criterio de parada, `while`/`for`/`do-while`, lectura y escritura de ficheros | [📂](Tema1/Practic/Pra_2) |
| 3 | **Funciones** | Medias cuadrática y armónica, producto escalar, norma, paso por valor y por referencia, punteros a funciones | [📂](Tema1/Practic/Pra_3) |
| 4 | **Matrices** | Producto de matrices con funciones y salida ordenada por pantalla | [📂](Tema1/Practic/Pra_4) |
| 5 | **Memoria dinámica** | Vectores y matrices dinámicos (`new`/`delete`), producto de matrices de dimensión arbitraria | [📂](Tema1/Practic/Pra_4) |

### 🎯 Bloque II · Sistemas de ecuaciones

| Nº | Práctica | Qué se aprende | Carpeta |
|:--:|---|---|:--:|
| 6 | **Newton-Raphson: búsqueda de ceros** | Aproximar √2 y raíces de polinomios, convergencia, potencial de Buckingham | [📂](Tema2/Practic/Pra_5) |
| 7 | **Factorización LU** | Resolver sistemas lineales por descomposición LU, aplicación al índice de refracción `n(λ)` | [📂](Tema2/Practic/Pra_6) |
| 8 | **Métodos iterativos** | Jacobi y Gauss-Seidel, lectura de la matriz desde fichero, análisis de convergencia | [📂](Tema2/Practic/Pra_7) |
| 9 | **Sistemas no lineales** | Newton-Raphson en varias variables con matriz jacobiana | [📂](Tema2/Practic/Pra_8) |
| 10 | **LU tridiagonal** | Sistema de n = 1000 ecuaciones con el algoritmo de Thomas (LU adaptado a tridiagonales) | [📂](Tema2/Practic/Pra_9) |

### 🌀 Bloque III · Autovalores y autovectores

| Nº | Práctica | Qué se aprende | Carpeta |
|:--:|---|---|:--:|
| 11 | **Modos normales con Jacobi** | Edificio de cuatro plantas como cuatro masas y cuatro muelles acoplados: frecuencias y modos propios | [📂](Tema3/Practic/Pra_10) |

### ∫ Bloque IV · Integración y derivación

| Nº | Práctica | Qué se aprende | Carpeta |
|:--:|---|---|:--:|
| 12 | **Péndulo físico** | Periodo exacto (integral elíptica) frente a la aproximación de ángulos pequeños, comparando reglas de integración | [📂](Tema4/Practic/Pra_11) |
| 13 | **Espectros XPS** | Áreas de picos de Al 2p, O 1s y C 1s con la regla del trapecio y la de Simpson | [📂](Tema4/Practic/Pra_12) |
| 14 | **Derivación numérica** | Velocidad y aceleración a partir de 500 datos s(t) | [📂](Tema4/Practic/Pra_13) |

### 🌍 Bloque V · EDOs

| Nº | Práctica | Qué se aprende | Carpeta |
|:--:|---|---|:--:|
| 15 | **EDOs de primer orden** | Euler simple, Euler modificado y Runge-Kutta 4, más un circuito RLC en paralelo | [📂](Tema5/Practic/Pra_14) |
| 16 | **Péndulo forzado** | EDO de segundo orden con amortiguamiento y fuerza externa, resuelta con RK4 | [📂](Tema5/Practic/Pra_15) |
| 17 | **Foucault y órbitas** | Péndulo de Foucault y órbita de la Tierra alrededor del Sol, sistemas de EDOs de orden n | [📂](Tema5/Practic/Pra_16) |
| 18 | **Método del disparo** | Problema de contorno lineal: potencial entre dos esferas concéntricas | [📂](Tema5/Practic/Pra_17) |
| 19 | **Diferencias finitas** | El mismo potencial resuelto por diferencias finitas y comparado con la solución exacta | [📂](Tema5/Practic/Pra_18) |

---

## 🧰 Matclub: mi minilibrería numérica

En la carpeta [`Libreria/`](Libreria) hay una librería propia, **Matclub**, pensada para escribir C++ numérico con la comodidad de MATLAB. Se usa con un simple `#include`:

```cpp
#include "matclub.cpp"
using namespace std;

int main() {
    double *a = new double[3]{1, 2, 3};
    double *b = new double[3]{3, 2, 0};

    double *c = suma_vect(a, b, 3);
    print_vect(c, 3, "c");          // c = [4 4 3]

    cout << "media = " << mean_vect(c, 3) << endl;
    cout << "std   = " << std_vect(c, 3)  << endl;
}
```

| Categoría | Ejemplos de funciones |
|---|---|
| 🧮 **Vectores** | `prod_vect`, `mod_vect`, `cos_ang_vect`, `sum_elems`, `max_vect`, `argmax_vect`, `polyval` |
| 🔲 **Matrices** | `print_mat`, `trace_mat`, `is_symmetric_mat`, `max_abs_mat`, `find_val_mat` |
| 📊 **Estadística** | `mean_vect`, `median_vect`, `std_vect`, `var_vect`, `cov_vect`, `corr_vect`, `percentil_vect`, `hist_auto_vect` |
| 🔃 **Ordenación** | `insertion_sort`, `heapsort`, `introsort` |
| 🔢 **Utilidades** | `factorial`, `comb`, `mcd_int`, `mcm_int`, `is_prime`, `deg2rad`, `seccion_aurea` |
| 🛠️ **Entrada/salida** | `print_error`, `print_info`, `print_line`, `file_exists` |

También está la **v1** en [`Libreria/Matclub v1/`](Libreria/Matclub%20v1) con una comparativa visual frente a MATLAB para sistemas lineales, y las funciones clásicas de la asignatura (`crearmatriz`, `muestramatriz`, `leerdatos`, `grabardatos`…) en [`librerias.cpp`](Tema1/Practic/Pra_4/Ejemplos%20matrices%20con%20memoria%20dinamica%20y%20funciones%20en%20fichero%20include/librerias.cpp).

---

## 📝 Exámenes

Colección de exámenes de teoría y de prácticas, ideal para entrenar el formato real de la asignatura.

<details>
<summary><b>📂 Parciales (2016 – 2019)</b></summary>

- [Parciales 1 y 2 · 2016](Examenes/C2%20-%20Parciales%201%20y%202%20-%202016.pdf)
- [Parciales 1 y 2 · 2017](Examenes/C2%20-%20Parciales%201%20y%202%20-%202017.pdf)
- [Parciales 1 y 2 · 2018-2019](Examenes/C2-%20Parciales%201%20y%202%20%282018-2019%29.pdf)

</details>

<details>
<summary><b>📂 Controles de prácticas (2020 – 2025)</b></summary>

- **2020**: dos exámenes de prácticas, con la [solución completa del examen 1](Examenes/Controles/2020/Solucion_examen1) (ceros de funciones y factorización LU, con informe)
- **2021**: [examen 1 de prácticas](Examenes/Controles/2021)
- **2023**: [Parcial I](Examenes/Controles/2023)
- **2024**: [control intermedio con problema de diagonalización (metano/Si)](Examenes/Controles/2024)
- **2025**: [examen y códigos](Examenes/Controles/2025)

</details>

<details>
<summary><b>📂 Finales (2013 – 2024)</b></summary>

- [Enero 2013](Examenes/Finales/2013) · [Enero 2016](Examenes/Finales/2016) · [Enero 2021 (con solución de teoría)](Examenes/Finales/2021) · [Enero 2022](Examenes/Finales/2022) · [Parcial II 2024](Examenes/Finales/2024)

</details>

También hay un [ejemplo de informe](Informes/Ejemplo%20de%20Informe.pdf) y una [plantilla](Informes/plantilla_informe.pdf) para entregar las prácticas.

---

## 🚀 Cómo compilar y ejecutar

**Linux / macOS / WSL**

```bash
git clone https://github.com/EnDriS10/Cpp_Physics.git
cd Cpp_Physics/Tema2/Practic/Pra_5

g++ -std=c++11 -O2 -Wall P1.cpp -o P1 -lm
./P1
```

**Windows**: en la raíz está el instalador de **Dev-C++ 5.11 con TDM-GCC 4.9.2** (`Dev-Cpp 5.11 TDM-GCC 4.9.2 Setup.exe`), que es con lo que se trabaja en clase. Abres el `.cpp`, pulsas `F11` y listo.

> 💡 Los programas que leen datos (`matriz.dat`, `distancia.dat`, `Al2p.dat`…) esperan encontrarlos en la carpeta desde la que se ejecuta el binario. Ejecútalos desde dentro de la carpeta de su práctica.

Para dibujar los resultados que los programas guardan en `.dat`, vale cualquier herramienta: gnuplot, MATLAB/Octave o Python con matplotlib.

```python
import numpy as np, matplotlib.pyplot as plt
t, y = np.loadtxt("resultados.dat", unpack=True)
plt.plot(t, y); plt.xlabel("t"); plt.ylabel("y"); plt.grid(); plt.show()
```

---

## 🗂️ Estructura del repositorio

```text
Cpp_Physics/
├── 📁 Tema1/   Aritmética, errores y C++            (prácticas 1–5)
│   ├── Teoria/  ·  Codigos_Ejemplo/  ·  Practic/Pra_1 … Pra_4
├── 📁 Tema2/   Ceros y sistemas de ecuaciones       (prácticas 6–10)
├── 📁 Tema3/   Autovalores y autovectores           (práctica 11)
├── 📁 Tema4/   Integración y derivación             (prácticas 12–14)
├── 📁 Tema5/   Ecuaciones diferenciales ordinarias  (prácticas 15–19)
├── 📁 Libreria/    matclub: librería numérica propia
├── 📁 Examenes/    Parciales, controles y finales
├── 📁 Informes/    Plantilla y ejemplo de informe
└── 💿 Dev-Cpp 5.11 TDM-GCC 4.9.2 Setup.exe
```

---

## 📖 Bibliografía

**Lenguaje C++**
- *The C++ Programming Language*. Bjarne Stroustrup. Addison-Wesley.
- *Programming with C++*. John Hubbard. Schaum.

**Análisis y cálculo numérico**
- *Análisis Numérico con Aplicaciones*. C. F. Gerald y P. O. Wheatley. Addison-Wesley.
- *Análisis Numérico*. R. L. Burden y J. Douglas Faires. International Thomson Editores.
- *Cálculo Numérico*. B. Carnahan, H. A. Luther y J. O. Wilkes. Rueda.
- *Análisis Numérico. Las matemáticas del cálculo científico*. D. Kincaid y W. Cheney. Addison-Wesley.
- *Elementary Numerical Analysis*. Kendall Atkinson. John Wiley and Sons.
- [*Numerical Recipes: The Art of Scientific Computing*](http://numerical.recipes/). Cambridge University Press. Libro online.

---

<div align="center">

### 👨‍🔬 Autor

**César Acosta Martínez** · [@EnDriS10](https://github.com/EnDriS10)
Estudiante de Física

⭐ Si este repo te ha servido para estudiar, ¡déjale una estrella!

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:2c5364,50:203a43,100:0f2027&height=120&section=footer" alt="footer"/>

</div>
