<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0f2027,50:203a43,100:2c5364&height=220&section=header&text=Cpp%20Physics&fontSize=70&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=Computaci%C3%B3n%20II%20%C2%B7%20C%2B%2B%20and%20Numerical%20Methods%20for%20Physics&descAlignY=60&descSize=20" alt="Cpp Physics banner"/>

[![C++](https://img.shields.io/badge/C++-98%2F11-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Degree](https://img.shields.io/badge/BSc-Physics-6C3483?style=for-the-badge&logo=atom&logoColor=white)](#)
[![Course](https://img.shields.io/badge/2nd_year-Computaci%C3%B3n_II-2C5364?style=for-the-badge)](#)
[![Practicals](https://img.shields.io/badge/practicals-19%2F19-2ea44f?style=for-the-badge)](#-practicals)
[![Library](https://img.shields.io/badge/Matclub-300%2B_functions-c0392b?style=for-the-badge)](#-matclub-my-numerical-library)
[![Exams](https://img.shields.io/badge/exams-2013--2025-e67e22?style=for-the-badge)](#-exams)

**The whole *Computación II* course in a single repository:**
theory notes, 19 solved practicals, a home-made numerical library and a decade of past exams.

[📚 Syllabus](#-syllabus) · [🧪 Practicals](#-practicals) · [🧰 Matclub](#-matclub-my-numerical-library) · [📝 Exams](#-exams) · [🚀 Getting started](#-getting-started) · [📖 Bibliography](#-bibliography)

</div>

---

## ✨ What is this?

This is the repository for **Computación II** (Computing II), a second-year course of the Physics degree. It collects everything I did to learn **C++** and, above all, to **solve physics problems on a computer that have no closed-form solution** (or a very painful one): from understanding why `0.1 + 0.2 ≠ 0.3`, to integrating the orbit of the Earth or computing the normal modes of a building during an earthquake.

> *"Computers don't do exact maths: they do finite arithmetic. Understanding the difference is the first step of numerical computing."*

| | |
|---|---|
| 🧱 **Blocks** | 5 (Introduction → Systems of equations → Eigenvalues → Integration & differentiation → ODEs) |
| 🧪 **Practicals** | 19, from summing series to the shooting method |
| 🧰 **Own library** | **Matclub**: ~300 functions for vectors, matrices, solvers, eigenvalues, integration, ODEs and more |
| 📝 **Exams** | Midterms, controls and finals from 2013 to 2025 |
| 📈 **Plotting** | MATLAB helper scripts to plot the `.dat` files written by the C++ programs |
| 💻 **Language** | C++ (g++ / MinGW) |

> 🌐 **Note:** the course material itself (statements, notes, exams) is written in Spanish. This README is in English; code identifiers and comments mostly follow the Spanish course.

---

## 🗺️ Course roadmap

```mermaid
flowchart LR
    A["🧱 Block I<br/>Arithmetic & C++"] --> B["🎯 Block II<br/>Systems of equations"]
    B --> C["🌀 Block III<br/>Eigenvalues"]
    C --> D["∫ Block IV<br/>Integration & differentiation"]
    D --> E["🌍 Block V<br/>ODEs"]
    style A fill:#1f6feb,color:#fff,stroke:none
    style B fill:#8957e5,color:#fff,stroke:none
    style C fill:#db61a2,color:#fff,stroke:none
    style D fill:#e67e22,color:#fff,stroke:none
    style E fill:#2ea44f,color:#fff,stroke:none
```

---

## 📚 Syllabus

<table>
<tr>
<td width="50%" valign="top">

### 🧱 Block I · Introduction
- **I.1** Computer arithmetic: integer and floating-point numbers
- **I.2** Numerical errors: definition, sources, examples
- **I.3** Introduction to programming languages (C++, …)

📁 [`Tema1/`](Tema1) · [Theory](Tema1/Teoria) · [Example codes](Tema1/Codigos_Ejemplo)

</td>
<td width="50%" valign="top">

### 🎯 Block II · Systems of equations
- **II.1** Finding the zeros of a function
- **II.2** Linear systems: direct and iterative methods
- **II.3** Non-linear systems: Newton-Raphson. Function minimisation: conjugate gradient

📁 [`Tema2/`](Tema2) · [Theory](Tema2/Teoria)

</td>
</tr>
<tr>
<td width="50%" valign="top">

### 🌀 Block III · Diagonalisation
- **III.1** The eigenvalue problem
- **III.2** Symmetric matrices: the **Jacobi** method
- **III.3** Tridiagonal matrices: the **QR** method
- **III.4** Symmetric → tridiagonal: the **Householder** method

📁 [`Tema3/`](Tema3) · [Theory](Tema3/Teoria)

</td>
<td width="50%" valign="top">

### ∫ Block IV · Integration & differentiation
- **IV.1** Numerical integration: Newton-Cotes and Simpson rules; Gaussian quadrature
- **IV.2** Numerical differentiation

📁 [`Tema4/`](Tema4) · [Theory](Tema4/Teoria)

</td>
</tr>
<tr>
<td colspan="2" valign="top">

### 🌍 Block V · Ordinary differential equations
- **V.1** Initial-value ODEs: **Euler** and **Runge-Kutta** methods
- **V.2** Systems of first-order ODEs and higher-order ODEs
- **V.3** Boundary-value ODEs

📁 [`Tema5/`](Tema5) · [Theory](Tema5/Teoria)

</td>
</tr>
</table>

---

## 🧪 Practicals

Each practical lives in its own `Pra_N/` folder with the statement (PDF), the `.cpp` source and, when needed, the data files (`.dat`) and worked solutions.

### 🧱 Block I · Arithmetic & C++

| # | Practical | What it teaches | Folder |
|:--:|---|---|:--:|
| 1 | **Series and numerical errors** | Forward vs. backward summation in single and double precision, Armstrong numbers, factorials with integers and reals | [📂](Tema1/Practic/Pra_1) |
| 2 | **Taylor series, loops and files** | `exp(x)` via Taylor with a stopping criterion, `while` / `for` / `do-while`, reading and writing files | [📂](Tema1/Practic/Pra_2) |
| 3 | **Functions** | Quadratic and harmonic means, dot product, norm, pass by value / by reference, pointers to functions | [📂](Tema1/Practic/Pra_3) |
| 4 | **Matrices** | Matrix product with functions and tidy console output | [📂](Tema1/Practic/Pra_4) |
| 5 | **Dynamic memory** | Dynamic vectors and matrices (`new` / `delete`), product of matrices of arbitrary size | [📂](Tema1/Practic/Pra_4) |

### 🎯 Block II · Systems of equations

| # | Practical | What it teaches | Folder |
|:--:|---|---|:--:|
| 6 | **Newton-Raphson: root finding** | Approximating √2 and polynomial roots, convergence, the Buckingham potential | [📂](Tema2/Practic/Pra_5) |
| 7 | **LU factorisation** | Solving linear systems by LU decomposition, application to the refractive index `n(λ)` | [📂](Tema2/Practic/Pra_6) |
| 8 | **Iterative methods** | Jacobi and Gauss-Seidel, reading the matrix from a file, convergence analysis | [📂](Tema2/Practic/Pra_7) |
| 9 | **Non-linear systems** | Multivariate Newton-Raphson with the Jacobian matrix | [📂](Tema2/Practic/Pra_8) |
| 10 | **Tridiagonal LU** | A system of n = 1000 equations with the Thomas algorithm (LU adapted to tridiagonal matrices) | [📂](Tema2/Practic/Pra_9) |

### 🌀 Block III · Eigenvalues and eigenvectors

| # | Practical | What it teaches | Folder |
|:--:|---|---|:--:|
| 11 | **Normal modes with Jacobi** | A four-storey building modelled as four masses and four coupled springs: natural frequencies and modes | [📂](Tema3/Practic/Pra_10) |

### ∫ Block IV · Integration & differentiation

| # | Practical | What it teaches | Folder |
|:--:|---|---|:--:|
| 12 | **The physical pendulum** | Exact period (elliptic integral) vs. the small-angle approximation, comparing integration rules | [📂](Tema4/Practic/Pra_11) |
| 13 | **XPS spectra** | Peak areas of Al 2p, O 1s and C 1s with the trapezoidal and Simpson rules | [📂](Tema4/Practic/Pra_12) |
| 14 | **Numerical differentiation** | Velocity and acceleration from 500 `s(t)` data points | [📂](Tema4/Practic/Pra_13) |

### 🌍 Block V · ODEs

| # | Practical | What it teaches | Folder |
|:--:|---|---|:--:|
| 15 | **First-order ODEs** | Simple Euler, modified Euler and Runge-Kutta 4, plus a parallel RLC circuit | [📂](Tema5/Practic/Pra_14) |
| 16 | **The forced pendulum** | Second-order ODE with damping and an external force, solved with RK4 | [📂](Tema5/Practic/Pra_15) |
| 17 | **Foucault and orbits** | Foucault's pendulum and the Earth's orbit around the Sun, systems of n-th order ODEs | [📂](Tema5/Practic/Pra_16) |
| 18 | **Shooting method** | Linear boundary-value problem: potential between two concentric spheres | [📂](Tema5/Practic/Pra_17) |
| 19 | **Finite differences** | The same potential solved by finite differences and compared with the exact solution | [📂](Tema5/Practic/Pra_18) |

---

## 🧰 Matclub: my numerical library

[`Libreria/`](Libreria) contains **Matclub**, a library I wrote to do numerical C++ with the comfort of MATLAB. It grew with the course through several versions:

| Version | Folder | What it is |
|---|---|---|
| **v1** | [`Matclub v1/`](Libreria/Matclub%20v1) | First single-file version, with a visual comparison against MATLAB for linear systems |
| **v2** | [`Matclub v2/`](Libreria/Matclub%20v2) | Single `matclub.cpp` covering the whole syllabus, used with a plain `#include` |
| **v2.1** | [`Matclub v2.1/`](Libreria/Matclub%20v2.1) | **Current version.** Modular: one header + source per topic, grouped by course block, with a master header `matclub.h` |
| **Exam kit** | [`Examenes/`](Libreria/Examenes) | Exam-day toolkit: single-file Matclub, a C++ basics cheat sheet and MATLAB plotting scripts |

### Modules of Matclub v2.1

| Block | Module | Highlights |
|---|---|---|
| 🧱 **I · Basics** | `vectores`, `matrices`, `auxiliares`, `ordenacion`, `aleatorios`, `archivos`, `mensajes` | `linspace`, `sin_vect`, `cumsum_vect`, `prod_mat`, `transpose_mat`, `eye_mat`, `print_mat`, `sort_vect`, `randn_vect`, `read_xy_file`, `save_mat_file`, `print_error`… |
| 🎯 **II · Systems of equations** | `ceros_funcion`, `eliminacion_gauss`, `factorizacion_lu`, `sistemas_tridiagonales`, `metodos_iterativos`, `determinantes_inversas`, `sistemas_no_lineales`, `minimizacion`, `minimos_cuadrados` | `biseccion`, `secante`, `newton`, `gauss_solve`, `lu_forma1`, `tridiag_solve`, `jacobi_solve`, `gauss_seidel_solve`, `sor_solve`, `inv_lu`, `newton_raphson_sys`, `steepest_descent_sys`, `seccion_aurea`, `poly_reg`, `lin_reg`… |
| 🌀 **III · Eigenvalues** | `jacobi`, `qr`, `householder`, `autovalores` | `jacobi_eig`, `sort_eig`, `qr_eig`, `qr_givens_mat`, `hessenberg_householder_mat`, `potencia_eig`, `potencia_inv_eig`, `rayleigh_mat` |
| ∫ **IV · Integration & differentiation** | `integracion`, `derivacion` | `nc_trapecio`, `nc_simpson13`, `nc_simpson38`, `romberg_int`, `gauss_legendre_func`, `integral_doble_func`, `deriv_cent_3p`, `deriv_richardson`, `jacobian_mat`, `grad_vect`… |
| 🌍 **V · ODEs & PDEs** | `edo_valores_iniciales`, `edo_sistemas`, `edo_frontera`, `edps` | `euler_edo`, `rk4_edo`, `rkf45_edo`, `rk4_sys`, `rk4_orden_n`, `disparo_edo`, `dif_finitas_bvp`, `calor_explicito`, `calor_implicito`, `laplace_gs` |
| ➕ **Extras** | `interpolacion`, `estadistica` | `spline_interp`, `lagrange_val`, `newton_coef`, `median_vect`, `hist_auto_vect`, `corr_vect`, `percentil_vect`, `movmean_vect` |

### Syllabus ↔ Matclub

| Syllabus topic | Matclub functions |
|---|---|
| **II.1** Zeros of a function | `biseccion`, `secante`, `newton` |
| **II.2** Linear systems (direct) | `gauss_solve`, `gauss_jordan_solve`, `lu_forma1`, `lu_forma2`, `tridiag_solve` |
| **II.2** Linear systems (iterative) | `jacobi_solve`, `gauss_seidel_solve`, `sor_solve` |
| **II.3** Non-linear systems / minimisation | `newton_raphson_sys`, `steepest_descent_sys`, `seccion_aurea` |
| **III.2** Jacobi diagonalisation | `jacobi_eig`, `sort_eig` |
| **III.3** QR method | `qr_eig`, `qr_gs_mat`, `qr_givens_mat` |
| **III.4** Householder | `hessenberg_householder_mat` |
| **IV.1** Integration | `nc_trapecio`, `nc_simpson13`, `romberg_int`, `gauss_legendre_func` |
| **IV.2** Differentiation | `deriv_cent_3p`, `deriv_cent_5p`, `deriv_richardson` |
| **V.1–V.2** Initial-value ODEs | `euler_edo`, `rk4_edo`, `rkf45_edo`, `rk4_sys`, `rk4_orden_n` |
| **V.3** Boundary-value ODEs | `disparo_edo`, `dif_finitas_bvp` |

### Quick taste

```cpp
#include "matclub.h"
using namespace std;

double f(double x) { return x * x - 2.0; }

int main() {
    // Block II: root of x^2 - 2 by bisection
    cout << "sqrt(2) = " << biseccion(f, 0.0, 2.0, 1e-10, 1e-10, 100) << endl;

    // Block II: solve a 3x3 linear system
    double **A = zeros_mat(3, 3);
    A[0][0] =  2; A[0][1] =  1; A[0][2] = -1;
    A[1][0] = -3; A[1][1] = -1; A[1][2] =  2;
    A[2][0] = -2; A[2][1] =  1; A[2][2] =  2;
    double b[3] = {8, -11, -3};
    double *x = gauss_solve(A, b, 3);
    print_vect(x, 3, "x");          // x = [ 2, 3, -1 ]
}
```

Full per-block demo: [`ejemplo_uso.cpp`](Libreria/Matclub%20v2.1/ejemplo_uso.cpp).

---

## 📝 Exams

A collection of theory and practical exams, ideal to train for the real format of the course.

<details>
<summary><b>📂 Midterms (2016 – 2019)</b></summary>

- [Midterms 1 & 2 · 2016](Examenes/C2%20-%20Parciales%201%20y%202%20-%202016.pdf)
- [Midterms 1 & 2 · 2017](Examenes/C2%20-%20Parciales%201%20y%202%20-%202017.pdf)
- [Midterms 1 & 2 · 2018-2019](Examenes/C2-%20Parciales%201%20y%202%20%282018-2019%29.pdf)

</details>

<details>
<summary><b>📂 Practical controls (2020 – 2025)</b></summary>

- **2020**: two practical exams, with the [full solution of exam 1](Examenes/Controles/2020/Solucion_examen1) (root finding and LU factorisation, with written reports)
- **2021**: [practical exam 1](Examenes/Controles/2021)
- **2023**: [Midterm I](Examenes/Controles/2023)
- **2024**: [first control, with a methane / silicon diagonalisation problem](Examenes/Controles/2024)
- **2025**: [exam and source codes](Examenes/Controles/2025)

</details>

<details>
<summary><b>📂 Finals (2013 – 2024)</b></summary>

- [January 2013](Examenes/Finales/2013) · [January 2016](Examenes/Finales/2016) · [January 2021 (with theory solution)](Examenes/Finales/2021) · [January 2022](Examenes/Finales/2022) · [Midterm II 2024](Examenes/Finales/2024)

</details>

There is also a [sample report](Informes/Ejemplo%20de%20Informe.pdf) and a [template](Informes/plantilla_informe.pdf) to hand in the practicals.

---

## 🚀 Getting started

**Linux / macOS / WSL**: a single practical

```bash
git clone https://github.com/EnDriS10/Cpp_Physics.git
cd Cpp_Physics/Tema2/Practic/Pra_5

g++ -O2 -Wall P1.cpp -o P1 -lm
./P1
```

**Using Matclub v2.1** (compile the example together with all the library sources):

```bash
cd "Cpp_Physics/Libreria/Matclub v2.1"
g++ -O2 -std=c++98 ejemplo_uso.cpp Bloque_*/*.cpp Complementos/*.cpp -o ejemplo
./ejemplo
```

For a quick program or an exam, the single-file versions need no linking at all, just `#include "matclub.cpp"` ([`Libreria/Examenes/Matclub/`](Libreria/Examenes/Matclub) or [`Libreria/Matclub v2/`](Libreria/Matclub%20v2)).

**Windows**: the root of the repo includes the **Dev-C++ 5.11 with TDM-GCC 4.9.2** installer (`Dev-Cpp 5.11 TDM-GCC 4.9.2 Setup.exe`), which is what we use in class. Open the `.cpp`, press `F11` and you are done.

> 💡 Programs that read data (`matriz.dat`, `distancia.dat`, `Al2p.dat`…) expect to find it in the folder they are run from. Run them from inside their practical's folder.

### 📈 Plotting the results

The programs write their results to `.dat` files. Ready-made MATLAB scripts live in [`Libreria/Examenes/`](Libreria/Examenes): [`Graficar.m`](Libreria/Examenes/Graficar.m) (plotting cheat sheet), [`Exportar_Importar_datos.m`](Libreria/Examenes/Exportar_Importar_datos.m) (import / export data) and a complete [`EJEMPLO_GRAFICAR_DAT`](Libreria/Examenes/EJEMPLO_GRAFICAR_DAT) example. Any other tool works too, for instance Python:

```python
import numpy as np, matplotlib.pyplot as plt
t, y = np.loadtxt("resultados.dat", unpack=True)
plt.plot(t, y); plt.xlabel("t"); plt.ylabel("y"); plt.grid(); plt.show()
```

---

## 🗂️ Repository structure

```text
Cpp_Physics/
├── 📁 Tema1/   Arithmetic, errors and C++            (practicals 1–5)
│   ├── Teoria/  ·  Codigos_Ejemplo/  ·  Practic/Pra_1 … Pra_4
├── 📁 Tema2/   Roots and systems of equations        (practicals 6–10)
├── 📁 Tema3/   Eigenvalues and eigenvectors          (practical 11)
├── 📁 Tema4/   Integration and differentiation       (practicals 12–14)
├── 📁 Tema5/   Ordinary differential equations       (practicals 15–19)
├── 📁 Libreria/
│   ├── Matclub v1/      first version
│   ├── Matclub v2/      single-file version
│   ├── Matclub v2.1/    modular version (current)
│   └── Examenes/        exam kit: single-file Matclub, cheat sheet, MATLAB scripts
├── 📁 Examenes/    Midterms, controls and finals
├── 📁 Informes/    Report template and sample
└── 💿 Dev-Cpp 5.11 TDM-GCC 4.9.2 Setup.exe
```

> 🔢 **Folder numbering:** practical 5 lives inside `Pra_4` (it is the "4b" sheet), so from practical 6 onwards the folder `Pra_N` holds practical `N + 1`.

---

## 📖 Bibliography

**C++ language**
- *The C++ Programming Language*. Bjarne Stroustrup. Addison-Wesley.
- *Programming with C++*. John Hubbard. Schaum.

**Numerical analysis**
- *Análisis Numérico con Aplicaciones*. C. F. Gerald and P. O. Wheatley. Addison-Wesley.
- *Análisis Numérico*. R. L. Burden and J. Douglas Faires. International Thomson Editores.
- *Cálculo Numérico*. B. Carnahan, H. A. Luther and J. O. Wilkes. Rueda.
- *Análisis Numérico. Las matemáticas del cálculo científico*. D. Kincaid and W. Cheney. Addison-Wesley.
- *Elementary Numerical Analysis*. Kendall Atkinson. John Wiley and Sons.
- [*Numerical Recipes: The Art of Scientific Computing*](http://numerical.recipes/). Cambridge University Press. Online book.

---

<div align="center">

### 👨‍🔬 Author

**César Acosta Martínez** · [@EnDriS10](https://github.com/EnDriS10)
Physics student

⭐ If this repo helped you study, leave it a star!

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:2c5364,50:203a43,100:0f2027&height=120&section=footer" alt="footer"/>

</div>
