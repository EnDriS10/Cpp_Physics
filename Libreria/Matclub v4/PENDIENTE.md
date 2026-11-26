# Pendiente / ideas para el futuro

## Documentación
1. **Resúmenes de teoría en Word.** Hecho: Bloque I (`Bloque_I_Introduccion/Resumen_Teoria_Bloque_I.docx`).
   **Faltan:** Bloque II (ceros, sistemas lineales directos/iterativos, no lineales y minimización), Bloque III (autovalores, Jacobi, QR, Householder),
   Bloque IV (integración y derivación), Bloque V (EDOs, frontera y EDPs) y Complementos (interpolación). Cada uno debe explicar cómo va cada método,
   por qué, y sobre todo **qué condiciones hacen falta para usarlo**. Todas las diapositivas ya están leídas y el generador de Word está probado, solo falta escribir y revisar el contenido.
2. **Bloque I:** unas 160 funciones (vectores, matrices, archivos…) no tienen "Descripción" ni "Ejemplo de uso". Se dejó así por indicación (la norma empieza en el Bloque II).

## Código
3. **Métodos de las diapositivas sin implementar:** Gradiente conjugado (II.3). Cholesky solo aparece nombrado en las diapositivas de LU.
4. **Operadores extra posibles:** Hessiano (derivadas segundas mixtas), integrales dobles/triples de datos x-y no uniformes.
5. **Bisección:** el criterio de parada de `biseccion` usa `&&` (para en cuanto se cumple UNO de los criterios); las diapositivas siguen mientras alguno NO se cumpla (`||`). No se ha tocado.
6. **Funciones antiguas conviviendo con las nuevas:** `trapecio_comp_vect`, `simpson13_comp_vect`, `simpson38_comp_vect`, `deriv_vect_3p`, `deriv_vect_5p`, `deriv2_vect` (con y y h, solo equiespaciado) y `deriv_vect` / `int_vect`
   siguen igual; las nuevas con x e y son la familia `_xy`. Valorar si se unifican nombres.
7. `matclub.cpp` (archivo único) no tiene las protecciones `#ifndef` de los módulos: usar uno u otro, no mezclarlos.

## Pruebas
8. No probado en Dev-C++ 5.11 ni en Windows (todo verificado con g++ en C++98 y C++11).
9. Erratas detectadas en las diapositivas (para tenerlas presentes): coeficientes de Runge-Kutta-Fehlberg mal tecleados (1392 → 1932, 28564 → 28561, 1589 → 1859);
   Euler mejorado del sistema (x, y): la diapositiva da y(0.1) = −0.9088 y el cálculo a mano da −0.9095; integral triple de ejemplo: con los límites escritos sale −0.5876, no +0.5876.
