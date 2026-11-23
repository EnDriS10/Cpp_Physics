# Índice de MATCLUB-CPP

Para cada módulo: las funciones **propias** (las que define) y las **dependencias copiadas** (funciones de otros módulos que necesita y que lleva dentro para ser independiente).

## Bloque I: Introducción  (`Bloque_I_Introduccion/`)

### `mensajes.cpp`: Mensajes de error, aviso e informacion

- **Propias (6):** `print_error`, `print_warning`, `print_info`, `print_error_int`, `print_error_dim`, `print_line`
- **Copiadas (0):** ninguna

### `auxiliares.cpp`: Funciones auxiliares y aritmetica basica

- **Propias (16):** `intercambiar_elem`, `isNaN`, `isRoot`, `is_in_range`, `clamp`, `deg2rad`, `rad2deg`, `max2`, `min2`, `factorial`, `comb`, `mcd_int`, `mcm_int`, `is_prime`, `PI`, `PHI`
- **Copiadas (2):** `MC_NAN`, `print_error`

### `vectores.cpp`: Vectores (arrays dinamicos)

- **Propias (72):** `del_vect`, `copy_vect`, `prod_vect`, `mod_vect`, `cos_ang_vect`, `suma_vect`, `resta_vect`, `prod_esc_vect`, `lincomb_vect`, `prodeach_vect`, `diveach_vect`, `exp_vect`, `prodx_vect`, `full_vect`, `zeros_vect`, `ones_vect`, `linspace`, `logspace`, `arange`, `pow_vect`, `sqrt_vect`, `abs_vect`, `sin_vect`, `cos_vect`, `tan_vect`, `sec_vect`, `csc_vect`, `cot_vect`, `asin_vect`, `acos_vect`, `atan_vect`, `asec_vect`, `acsc_vect`, `acot_vect`, `log_vect`, `log10_vect`, `sinh_vect`, `cosh_vect`, `tanh_vect`, `asinh_vect`, `acosh_vect`, `atanh_vect`, `sum_elems`, `cumsum_vect`, `prod_elems`, `cumprod_vect`, `mean_vect`, `max_vect`, `min_vect`, `std_vect`, `flip_vect`, `argmax_vect`, `argmin_vect`, `diff_vect`, `concat_vect`, `floor_vect`, `ceil_vect`, `round_vect`, `print_vect`, `input_vect`, `normalize_vect`, `sign_vect`, `clamp_vect`, `polyval_vect`, `polyval`, `slice_vect`, `sum_esc_vect`, `var_vect`, `proj_vect`, `find_gt_vect`, `find_if_vect`, `count_if_vect`
- **Copiadas (3):** `MC_NAN`, `print_error`, `print_error_int`

### `matrices.cpp`: Matrices (arrays dinamicos 2D)

- **Propias (43):** `gen_mat`, `del_mat`, `prod_mat`, `input_mat`, `print_mat`, `coppy_mat`, `transpose_mat`, `zeros_mat`, `ones_mat`, `eye_mat`, `prod_esc_mat`, `trace_mat`, `get_row_mat`, `get_col_mat`, `suma_mat`, `resta_mat`, `prodeach_mat`, `sub_mat`, `horzcat_mat`, `vertcat_mat`, `flatten_mat`, `funeach_mat`, `apply_scalar_vect`, `apply_scalar_mat`, `remove_row_col_mat`, `is_symmetric_mat`, `swap_rows_mat`, `swap_cols_mat`, `find_val_mat`, `find_gt_mat`, `sum_all_mat`, `prod_all_mat`, `max_mat`, `max_abs_mat`, `min_mat`, `rand_mat`, `randi_mat`, `randn_mat`, `clamp_mat`, `reshape_mat`, `diag_mat`, `get_diag_mat`, `prod_mat_vect`
- **Copiadas (2):** `print_error`, `print_error_dim`

### `ordenacion.cpp`: Ordenacion de vectores (Introsort)

- **Propias (7):** `insertion_sort`, `heapify`, `heapsort_util`, `partition`, `introsort_util`, `sort_vect`, `sort_vect_algorithm`
- **Copiadas (1):** `intercambiar_elem`

### `aleatorios.cpp`: Numeros aleatorios

- **Propias (5):** `rand_vect`, `randi_vect`, `randn_vect`, `randnorm_vect`, `gen_distrib_prob`
- **Copiadas (2):** `PI`, `cumsum_vect`

### `archivos.cpp`: Manipulacion de archivos

- **Propias (13):** `file_exists`, `skip_comments`, `count_text_lines_file`, `count_lines_file`, `read_xy_file`, `save_xy_file`, `save_mat_file`, `read_mat_file`, `count_rows_single_file`, `read_single_vector_file`, `save_vector_file`, `get_file_dimensions`, `read_mat_auto`
- **Copiadas (4):** `print_error`, `print_warning`, `print_info`, `gen_mat`

## Bloque II: Sistemas de ecuaciones  (`Bloque_II_Sistemas_de_Ecuaciones/`)

### `ceros_funcion.cpp`: Busqueda de ceros de una funcion

- **Propias (5):** `biseccion`, `biseccion_multi`, `secante`, `newton`, `newton_multi`
- **Copiadas (5):** `MC_NAN`, `print_error`, `intercambiar_elem`, `isNaN`, `isRoot`

### `factorizacion_lu.cpp`: Sistemas lineales: factorizacion LU

- **Propias (4):** `lu_forma1`, `lu_forma1_sol`, `lu_forma2`, `lu_forma2_sol`
- **Copiadas (4):** `print_warning`, `gen_mat`, `del_mat`, `zeros_mat`

### `eliminacion_gauss.cpp`: Sistemas lineales: eliminacion de Gauss y Gauss-Jordan

- **Propias (2):** `gauss_solve`, `gauss_jordan_solve`
- **Copiadas (6):** `print_error`, `intercambiar_elem`, `copy_vect`, `gen_mat`, `del_mat`, `coppy_mat`

### `sistemas_tridiagonales.cpp`: Sistemas lineales: matrices tridiagonales

- **Propias (2):** `tridiag_solve`, `tridiag_vect_solve`
- **Copiadas (2):** `print_warning`, `print_error_int`

### `determinantes_inversas.cpp`: Determinantes e inversas

- **Propias (4):** `det_gauss`, `det_lu`, `inv_gj`, `inv_lu`
- **Copiadas (8):** `print_error`, `print_warning`, `intercambiar_elem`, `gen_mat`, `del_mat`, `coppy_mat`, `zeros_mat`, `lu_forma1`

### `metodos_iterativos.cpp`: Sistemas lineales: metodos iterativos

- **Propias (5):** `check_dominancia`, `reorder_diagonals`, `jacobi_solve`, `gauss_seidel_solve`, `sor_solve`
- **Copiadas (11):** `print_error`, `print_warning`, `print_info`, `intercambiar_elem`, `copy_vect`, `prod_vect`, `mod_vect`, `resta_vect`, `gen_mat`, `del_mat`, `coppy_mat`

### `minimos_cuadrados.cpp`: Sistemas sobredeterminados y regresiones

- **Propias (7):** `ols_reg`, `poly_reg`, `lin_reg`, `exp_reg`, `regresion_logaritmica`, `regresion_potencial`, `regresion_sinusoidal`
- **Copiadas (17):** `MC_NAN`, `print_error`, `print_warning`, `print_error_dim`, `sum_elems`, `mean_vect`, `gen_mat`, `del_mat`, `prod_mat`, `transpose_mat`, `zeros_mat`, `prod_mat_vect`, `lu_forma1`, `lu_forma2`, `lu_forma2_sol`, `det_lu`, `inv_lu`

### `sistemas_no_lineales.cpp`: Sistemas no lineales

- **Propias (5):** `check_convergence_nolin`, `jacobi_nolin`, `gauss_seidel_nolin`, `newton_raphson_sys`, `newton_raphson_multi_sys`
- **Copiadas (14):** `MC_NAN`, `print_error`, `print_warning`, `copy_vect`, `prod_vect`, `mod_vect`, `resta_vect`, `gen_mat`, `del_mat`, `zeros_mat`, `lu_forma2`, `lu_forma2_sol`, `part_derv`, `jacobian_mat`

### `minimizacion.cpp`: Minimizacion de funciones

- **Propias (3):** `seccion_aurea`, `func_S_error`, `steepest_descent_sys`
- **Copiadas (7):** `MC_NAN`, `print_error`, `print_warning`, `intercambiar_elem`, `PHI`, `copy_vect`, `part_derv`

## Bloque III: Diagonalización  (`Bloque_III_Diagonalizacion/`)

### `autovalores.cpp`: El problema de los autovalores

- **Propias (7):** `poly_caract_mat`, `rayleigh_mat`, `resid_eig`, `resid_eig_mat`, `similar_mat`, `potencia_eig`, `potencia_inv_eig`
- **Copiadas (17):** `print_error`, `print_warning`, `print_error_dim`, `intercambiar_elem`, `copy_vect`, `gen_mat`, `del_mat`, `prod_mat`, `coppy_mat`, `zeros_mat`, `trace_mat`, `get_col_mat`, `prod_mat_vect`, `lu_forma1`, `gauss_solve`, `det_lu`, `inv_lu`

### `jacobi.cpp`: Diagonalizacion de matrices simetricas: Metodo de Jacobi

- **Propias (2):** `sort_eig`, `jacobi_eig`
- **Copiadas (9):** `print_error`, `print_warning`, `intercambiar_elem`, `gen_mat`, `del_mat`, `coppy_mat`, `eye_mat`, `is_symmetric_mat`, `get_diag_mat`

### `qr.cpp`: Metodo QR

- **Propias (5):** `qr_gs_mat`, `qr_givens_mat`, `qr_schur_mat`, `qr_triang_mat`, `qr_eig`
- **Copiadas (15):** `print_error`, `print_warning`, `print_error_int`, `print_error_dim`, `intercambiar_elem`, `gen_mat`, `del_mat`, `prod_mat`, `coppy_mat`, `zeros_mat`, `eye_mat`, `get_diag_mat`, `sort_eig`, `hessenberg_mat`, `hessenberg_householder_mat`

### `householder.cpp`: Transformacion de Householder (forma de Hessenberg / tridiagonal)

- **Propias (2):** `hessenberg_mat`, `hessenberg_householder_mat`
- **Copiadas (4):** `intercambiar_elem`, `gen_mat`, `coppy_mat`, `eye_mat`

### `eig_general.cpp`: Interfaz general de autovalores y autovectores

- **Propias (1):** `eig_mat`
- **Copiadas (20):** `print_error`, `print_warning`, `print_error_int`, `print_error_dim`, `intercambiar_elem`, `gen_mat`, `del_mat`, `prod_mat`, `coppy_mat`, `zeros_mat`, `eye_mat`, `is_symmetric_mat`, `get_diag_mat`, `sort_eig`, `jacobi_eig`, `hessenberg_mat`, `hessenberg_householder_mat`, `qr_givens_mat`, `qr_schur_mat`, `qr_eig`

## Bloque IV: Integración y derivación  (`Bloque_IV_Integracion_Derivacion/`)

### `integracion.cpp`: Integracion numerica

- **Propias (22):** `integral_def_func`, `integral_indef_func`, `int_vect`, `nc_trapecio`, `nc_simpson13`, `nc_simpson38`, `trapecio_comp_func`, `simpson38_comp_func`, `trapecio_comp_vect`, `simpson13_comp_vect`, `simpson38_comp_vect`, `richardson_int`, `romberg_mat`, `romberg_int`, `gauss_legendre_nodos`, `gauss_legendre_func`, `pesos_nc`, `integral_doble_func`, `integral_triple_func`, `integral_doble_mat`, `gauss_doble_func`, `gauss_triple_func`
- **Copiadas (6):** `MC_NAN`, `print_warning`, `print_error_int`, `gen_mat`, `del_mat`, `zeros_mat`

### `derivacion.cpp`: Derivacion numerica

- **Propias (23):** `part_derv`, `total_derv`, `grad_vect`, `jacobian_mat`, `deriv_vect`, `deriv_prog_2p`, `deriv_reg_2p`, `deriv_prog_3p`, `deriv_reg_3p`, `deriv_cent_3p`, `deriv_prog_5p`, `deriv_cent_5p`, `deriv2_prog_3p`, `deriv2_cent_3p`, `deriv2_prog_5p`, `deriv2_cent_5p`, `deriv_func`, `richardson_deriv_mat`, `deriv_richardson`, `err_deriv_h_mat`, `deriv_vect_3p`, `deriv_vect_5p`, `deriv2_vect`
- **Copiadas (7):** `MC_NAN`, `print_error`, `print_error_int`, `copy_vect`, `gen_mat`, `del_mat`, `zeros_mat`

## Bloque V: EDO's  (`Bloque_V_EDOs/`)

### `edo_valores_iniciales.cpp`: EDO's con valores iniciales

- **Propias (8):** `err_max_vect`, `taylor_eval`, `euler_edo`, `euler_mejorado_edo`, `rk2_edo`, `rk4_edo`, `rkf45_paso`, `rkf45_edo`
- **Copiadas (3):** `print_error`, `print_warning`, `print_error_int`

### `edo_sistemas.cpp`: Sistemas de EDO's y EDO's de orden superior

- **Propias (7):** `eval_sys`, `euler_sys`, `euler_mejorado_sys`, `rk4_sys`, `rkf45_paso_sys`, `rkf45_sys`, `rk4_orden_n`
- **Copiadas (6):** `print_error`, `print_warning`, `copy_vect`, `gen_mat`, `del_mat`, `zeros_mat`

### `edo_frontera.cpp`: EDO's con condiciones de frontera

- **Propias (3):** `ivp_rk4_2o`, `disparo_edo`, `dif_finitas_bvp`
- **Copiadas (3):** `print_warning`, `print_error_int`, `tridiag_vect_solve`

### `edps.cpp`: Ecuaciones en derivadas parciales

- **Propias (4):** `calor_explicito`, `calor_implicito`, `laplace_gs`, `laplace_placa`
- **Copiadas (6):** `print_error`, `print_warning`, `print_error_int`, `gen_mat`, `zeros_mat`, `tridiag_vect_solve`

## Complementos  (`Complementos/`)

### `interpolacion.cpp`: Interpolacion numerica

- **Propias (15):** `spline_coef`, `spline_eval`, `spline_interp`, `newton_coef`, `newton_eval`, `lagrange_coef`, `lagrange_val`, `vandermonde_mat`, `poly_interp_coef`, `dif_divididas_mat`, `newton_error_sig`, `interp_error_cota`, `dif_progresivas_mat`, `newton_prog_eval`, `newton_prog_error_sig`
- **Copiadas (10):** `MC_NAN`, `print_error`, `intercambiar_elem`, `factorial`, `copy_vect`, `gen_mat`, `del_mat`, `coppy_mat`, `zeros_mat`, `gauss_solve`

### `estadistica.cpp`: Estadistica descriptiva

- **Propias (7):** `median_vect`, `hist_vect`, `hist_auto_vect`, `cov_vect`, `corr_vect`, `percentil_vect`, `movmean_vect`
- **Copiadas (15):** `MC_NAN`, `print_error`, `intercambiar_elem`, `zeros_vect`, `sum_elems`, `mean_vect`, `max_vect`, `min_vect`, `std_vect`, `insertion_sort`, `heapify`, `heapsort_util`, `partition`, `introsort_util`, `sort_vect`

## Dónde está cada función

| Función | Archivo |
|---|---|
| `abs_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `acos_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `acosh_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `acot_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `acsc_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `apply_scalar_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `apply_scalar_vect` | `Bloque_I_Introduccion/matrices.cpp` |
| `arange` | `Bloque_I_Introduccion/vectores.cpp` |
| `argmax_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `argmin_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `asec_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `asin_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `asinh_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `atan_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `atanh_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `biseccion` | `Bloque_II_Sistemas_de_Ecuaciones/ceros_funcion.cpp` |
| `biseccion_multi` | `Bloque_II_Sistemas_de_Ecuaciones/ceros_funcion.cpp` |
| `calor_explicito` | `Bloque_V_EDOs/edps.cpp` |
| `calor_implicito` | `Bloque_V_EDOs/edps.cpp` |
| `ceil_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `check_convergence_nolin` | `Bloque_II_Sistemas_de_Ecuaciones/sistemas_no_lineales.cpp` |
| `check_dominancia` | `Bloque_II_Sistemas_de_Ecuaciones/metodos_iterativos.cpp` |
| `clamp` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `clamp_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `clamp_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `comb` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `concat_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `coppy_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `copy_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `corr_vect` | `Complementos/estadistica.cpp` |
| `cos_ang_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `cos_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `cosh_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `cot_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `count_if_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `count_lines_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `count_rows_single_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `count_text_lines_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `cov_vect` | `Complementos/estadistica.cpp` |
| `csc_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `cumprod_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `cumsum_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `deg2rad` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `del_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `del_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `deriv2_cent_3p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv2_cent_5p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv2_prog_3p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv2_prog_5p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv2_vect` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_cent_3p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_cent_5p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_func` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_prog_2p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_prog_3p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_prog_5p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_reg_2p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_reg_3p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_richardson` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_vect` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_vect_3p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `deriv_vect_5p` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `det_gauss` | `Bloque_II_Sistemas_de_Ecuaciones/determinantes_inversas.cpp` |
| `det_lu` | `Bloque_II_Sistemas_de_Ecuaciones/determinantes_inversas.cpp` |
| `diag_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `dif_divididas_mat` | `Complementos/interpolacion.cpp` |
| `dif_finitas_bvp` | `Bloque_V_EDOs/edo_frontera.cpp` |
| `dif_progresivas_mat` | `Complementos/interpolacion.cpp` |
| `diff_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `disparo_edo` | `Bloque_V_EDOs/edo_frontera.cpp` |
| `diveach_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `eig_mat` | `Bloque_III_Diagonalizacion/eig_general.cpp` |
| `err_deriv_h_mat` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `err_max_vect` | `Bloque_V_EDOs/edo_valores_iniciales.cpp` |
| `euler_edo` | `Bloque_V_EDOs/edo_valores_iniciales.cpp` |
| `euler_mejorado_edo` | `Bloque_V_EDOs/edo_valores_iniciales.cpp` |
| `euler_mejorado_sys` | `Bloque_V_EDOs/edo_sistemas.cpp` |
| `euler_sys` | `Bloque_V_EDOs/edo_sistemas.cpp` |
| `eval_sys` | `Bloque_V_EDOs/edo_sistemas.cpp` |
| `exp_reg` | `Bloque_II_Sistemas_de_Ecuaciones/minimos_cuadrados.cpp` |
| `exp_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `eye_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `factorial` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `file_exists` | `Bloque_I_Introduccion/archivos.cpp` |
| `find_gt_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `find_gt_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `find_if_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `find_val_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `flatten_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `flip_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `floor_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `full_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `func_S_error` | `Bloque_II_Sistemas_de_Ecuaciones/minimizacion.cpp` |
| `funeach_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `gauss_doble_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `gauss_jordan_solve` | `Bloque_II_Sistemas_de_Ecuaciones/eliminacion_gauss.cpp` |
| `gauss_legendre_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `gauss_legendre_nodos` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `gauss_seidel_nolin` | `Bloque_II_Sistemas_de_Ecuaciones/sistemas_no_lineales.cpp` |
| `gauss_seidel_solve` | `Bloque_II_Sistemas_de_Ecuaciones/metodos_iterativos.cpp` |
| `gauss_solve` | `Bloque_II_Sistemas_de_Ecuaciones/eliminacion_gauss.cpp` |
| `gauss_triple_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `gen_distrib_prob` | `Bloque_I_Introduccion/aleatorios.cpp` |
| `gen_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `get_col_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `get_diag_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `get_file_dimensions` | `Bloque_I_Introduccion/archivos.cpp` |
| `get_row_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `grad_vect` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `heapify` | `Bloque_I_Introduccion/ordenacion.cpp` |
| `heapsort_util` | `Bloque_I_Introduccion/ordenacion.cpp` |
| `hessenberg_householder_mat` | `Bloque_III_Diagonalizacion/householder.cpp` |
| `hessenberg_mat` | `Bloque_III_Diagonalizacion/householder.cpp` |
| `hist_auto_vect` | `Complementos/estadistica.cpp` |
| `hist_vect` | `Complementos/estadistica.cpp` |
| `horzcat_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `input_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `input_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `insertion_sort` | `Bloque_I_Introduccion/ordenacion.cpp` |
| `int_vect` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `integral_def_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `integral_doble_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `integral_doble_mat` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `integral_indef_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `integral_triple_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `intercambiar_elem` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `interp_error_cota` | `Complementos/interpolacion.cpp` |
| `introsort_util` | `Bloque_I_Introduccion/ordenacion.cpp` |
| `inv_gj` | `Bloque_II_Sistemas_de_Ecuaciones/determinantes_inversas.cpp` |
| `inv_lu` | `Bloque_II_Sistemas_de_Ecuaciones/determinantes_inversas.cpp` |
| `is_in_range` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `is_prime` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `is_symmetric_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `isNaN` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `isRoot` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `ivp_rk4_2o` | `Bloque_V_EDOs/edo_frontera.cpp` |
| `jacobi_eig` | `Bloque_III_Diagonalizacion/jacobi.cpp` |
| `jacobi_nolin` | `Bloque_II_Sistemas_de_Ecuaciones/sistemas_no_lineales.cpp` |
| `jacobi_solve` | `Bloque_II_Sistemas_de_Ecuaciones/metodos_iterativos.cpp` |
| `jacobian_mat` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `lagrange_coef` | `Complementos/interpolacion.cpp` |
| `lagrange_val` | `Complementos/interpolacion.cpp` |
| `laplace_gs` | `Bloque_V_EDOs/edps.cpp` |
| `laplace_placa` | `Bloque_V_EDOs/edps.cpp` |
| `lin_reg` | `Bloque_II_Sistemas_de_Ecuaciones/minimos_cuadrados.cpp` |
| `lincomb_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `linspace` | `Bloque_I_Introduccion/vectores.cpp` |
| `log10_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `log_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `logspace` | `Bloque_I_Introduccion/vectores.cpp` |
| `lu_forma1` | `Bloque_II_Sistemas_de_Ecuaciones/factorizacion_lu.cpp` |
| `lu_forma1_sol` | `Bloque_II_Sistemas_de_Ecuaciones/factorizacion_lu.cpp` |
| `lu_forma2` | `Bloque_II_Sistemas_de_Ecuaciones/factorizacion_lu.cpp` |
| `lu_forma2_sol` | `Bloque_II_Sistemas_de_Ecuaciones/factorizacion_lu.cpp` |
| `max2` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `max_abs_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `max_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `max_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `mcd_int` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `mcm_int` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `mean_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `median_vect` | `Complementos/estadistica.cpp` |
| `min2` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `min_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `min_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `mod_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `movmean_vect` | `Complementos/estadistica.cpp` |
| `nc_simpson13` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `nc_simpson38` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `nc_trapecio` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `newton` | `Bloque_II_Sistemas_de_Ecuaciones/ceros_funcion.cpp` |
| `newton_coef` | `Complementos/interpolacion.cpp` |
| `newton_error_sig` | `Complementos/interpolacion.cpp` |
| `newton_eval` | `Complementos/interpolacion.cpp` |
| `newton_multi` | `Bloque_II_Sistemas_de_Ecuaciones/ceros_funcion.cpp` |
| `newton_prog_error_sig` | `Complementos/interpolacion.cpp` |
| `newton_prog_eval` | `Complementos/interpolacion.cpp` |
| `newton_raphson_multi_sys` | `Bloque_II_Sistemas_de_Ecuaciones/sistemas_no_lineales.cpp` |
| `newton_raphson_sys` | `Bloque_II_Sistemas_de_Ecuaciones/sistemas_no_lineales.cpp` |
| `normalize_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `ols_reg` | `Bloque_II_Sistemas_de_Ecuaciones/minimos_cuadrados.cpp` |
| `ones_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `ones_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `part_derv` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `partition` | `Bloque_I_Introduccion/ordenacion.cpp` |
| `percentil_vect` | `Complementos/estadistica.cpp` |
| `pesos_nc` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `PHI` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `PI` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `poly_caract_mat` | `Bloque_III_Diagonalizacion/autovalores.cpp` |
| `poly_interp_coef` | `Complementos/interpolacion.cpp` |
| `poly_reg` | `Bloque_II_Sistemas_de_Ecuaciones/minimos_cuadrados.cpp` |
| `polyval` | `Bloque_I_Introduccion/vectores.cpp` |
| `polyval_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `potencia_eig` | `Bloque_III_Diagonalizacion/autovalores.cpp` |
| `potencia_inv_eig` | `Bloque_III_Diagonalizacion/autovalores.cpp` |
| `pow_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `print_error` | `Bloque_I_Introduccion/mensajes.cpp` |
| `print_error_dim` | `Bloque_I_Introduccion/mensajes.cpp` |
| `print_error_int` | `Bloque_I_Introduccion/mensajes.cpp` |
| `print_info` | `Bloque_I_Introduccion/mensajes.cpp` |
| `print_line` | `Bloque_I_Introduccion/mensajes.cpp` |
| `print_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `print_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `print_warning` | `Bloque_I_Introduccion/mensajes.cpp` |
| `prod_all_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `prod_elems` | `Bloque_I_Introduccion/vectores.cpp` |
| `prod_esc_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `prod_esc_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `prod_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `prod_mat_vect` | `Bloque_I_Introduccion/matrices.cpp` |
| `prod_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `prodeach_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `prodeach_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `prodx_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `proj_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `qr_eig` | `Bloque_III_Diagonalizacion/qr.cpp` |
| `qr_givens_mat` | `Bloque_III_Diagonalizacion/qr.cpp` |
| `qr_gs_mat` | `Bloque_III_Diagonalizacion/qr.cpp` |
| `qr_schur_mat` | `Bloque_III_Diagonalizacion/qr.cpp` |
| `qr_triang_mat` | `Bloque_III_Diagonalizacion/qr.cpp` |
| `rad2deg` | `Bloque_I_Introduccion/auxiliares.cpp` |
| `rand_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `rand_vect` | `Bloque_I_Introduccion/aleatorios.cpp` |
| `randi_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `randi_vect` | `Bloque_I_Introduccion/aleatorios.cpp` |
| `randn_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `randn_vect` | `Bloque_I_Introduccion/aleatorios.cpp` |
| `randnorm_vect` | `Bloque_I_Introduccion/aleatorios.cpp` |
| `rayleigh_mat` | `Bloque_III_Diagonalizacion/autovalores.cpp` |
| `read_mat_auto` | `Bloque_I_Introduccion/archivos.cpp` |
| `read_mat_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `read_single_vector_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `read_xy_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `regresion_logaritmica` | `Bloque_II_Sistemas_de_Ecuaciones/minimos_cuadrados.cpp` |
| `regresion_potencial` | `Bloque_II_Sistemas_de_Ecuaciones/minimos_cuadrados.cpp` |
| `regresion_sinusoidal` | `Bloque_II_Sistemas_de_Ecuaciones/minimos_cuadrados.cpp` |
| `remove_row_col_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `reorder_diagonals` | `Bloque_II_Sistemas_de_Ecuaciones/metodos_iterativos.cpp` |
| `reshape_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `resid_eig` | `Bloque_III_Diagonalizacion/autovalores.cpp` |
| `resid_eig_mat` | `Bloque_III_Diagonalizacion/autovalores.cpp` |
| `resta_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `resta_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `richardson_deriv_mat` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `richardson_int` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `rk2_edo` | `Bloque_V_EDOs/edo_valores_iniciales.cpp` |
| `rk4_edo` | `Bloque_V_EDOs/edo_valores_iniciales.cpp` |
| `rk4_orden_n` | `Bloque_V_EDOs/edo_sistemas.cpp` |
| `rk4_sys` | `Bloque_V_EDOs/edo_sistemas.cpp` |
| `rkf45_edo` | `Bloque_V_EDOs/edo_valores_iniciales.cpp` |
| `rkf45_paso` | `Bloque_V_EDOs/edo_valores_iniciales.cpp` |
| `rkf45_paso_sys` | `Bloque_V_EDOs/edo_sistemas.cpp` |
| `rkf45_sys` | `Bloque_V_EDOs/edo_sistemas.cpp` |
| `romberg_int` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `romberg_mat` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `round_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `save_mat_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `save_vector_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `save_xy_file` | `Bloque_I_Introduccion/archivos.cpp` |
| `sec_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `secante` | `Bloque_II_Sistemas_de_Ecuaciones/ceros_funcion.cpp` |
| `seccion_aurea` | `Bloque_II_Sistemas_de_Ecuaciones/minimizacion.cpp` |
| `sign_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `similar_mat` | `Bloque_III_Diagonalizacion/autovalores.cpp` |
| `simpson13_comp_vect` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `simpson38_comp_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `simpson38_comp_vect` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `sin_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `sinh_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `skip_comments` | `Bloque_I_Introduccion/archivos.cpp` |
| `slice_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `sor_solve` | `Bloque_II_Sistemas_de_Ecuaciones/metodos_iterativos.cpp` |
| `sort_eig` | `Bloque_III_Diagonalizacion/jacobi.cpp` |
| `sort_vect` | `Bloque_I_Introduccion/ordenacion.cpp` |
| `sort_vect_algorithm` | `Bloque_I_Introduccion/ordenacion.cpp` |
| `spline_coef` | `Complementos/interpolacion.cpp` |
| `spline_eval` | `Complementos/interpolacion.cpp` |
| `spline_interp` | `Complementos/interpolacion.cpp` |
| `sqrt_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `std_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `steepest_descent_sys` | `Bloque_II_Sistemas_de_Ecuaciones/minimizacion.cpp` |
| `sub_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `sum_all_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `sum_elems` | `Bloque_I_Introduccion/vectores.cpp` |
| `sum_esc_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `suma_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `suma_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `swap_cols_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `swap_rows_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `tan_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `tanh_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `taylor_eval` | `Bloque_V_EDOs/edo_valores_iniciales.cpp` |
| `total_derv` | `Bloque_IV_Integracion_Derivacion/derivacion.cpp` |
| `trace_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `transpose_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `trapecio_comp_func` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `trapecio_comp_vect` | `Bloque_IV_Integracion_Derivacion/integracion.cpp` |
| `tridiag_solve` | `Bloque_II_Sistemas_de_Ecuaciones/sistemas_tridiagonales.cpp` |
| `tridiag_vect_solve` | `Bloque_II_Sistemas_de_Ecuaciones/sistemas_tridiagonales.cpp` |
| `vandermonde_mat` | `Complementos/interpolacion.cpp` |
| `var_vect` | `Bloque_I_Introduccion/vectores.cpp` |
| `vertcat_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `zeros_mat` | `Bloque_I_Introduccion/matrices.cpp` |
| `zeros_vect` | `Bloque_I_Introduccion/vectores.cpp` |
