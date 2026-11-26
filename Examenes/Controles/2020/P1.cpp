#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;

double f1(double *r, int n);
double* newton_raphson_iter(double (*AF[])(double*, int), double *x_init, int n, double tol, int &iter);
double* hist_vect_p1(double *datos, int n_datos, double *&dominio_out, int &n_out);

int main() {
	int n; double *x0 = arange(-6,0.1,5,n); double (*Sist[1])(double*, int) = {f1}; double *aux = new double[1];
	int iter; int* iter_array = new int[n];	double Sol_arr[n];double* f1_arr = new double[n];
	ofstream fsalida("Iter.dat", ios::out);
	
	for(int i =0; i<n;i++){
		aux[0]=	x0[i]; f1_arr[i]= f1(aux, 1);
		double* sol = newton_raphson_iter(Sist, aux, 1, 1e-4, iter);
		Sol_arr[i]=sol[0];
		iter_array[i]=iter;
		fsalida << x0[i] << "\t" << iter_array[i] << endl;
		delete [] sol;		
	}
    fsalida.close();
    print_info("Datos guardados exitosamente", "Iter.dat");
	
	

        double *dominio ;int n_unicos;        
        double *frecuencias = hist_vect_p1(Sol_arr, n, dominio, n_unicos);
        
        print_vect(dominio,n_unicos,"Soluciones (diferentes)");
    	print_vect(frecuencias,n_unicos,"Numero de veces que se repiten");
    	
    	save_xy_file("f1_arr.dat", x0, f1_arr, n);
    
    delete [] x0; delete [] aux; delete [] iter_array; delete [] f1_arr; delete [] dominio;  delete [] frecuencias; 
	return 0;
}

double f1(double *r, int n){ return exp(r[0])-r[0]*(r[0]+5)-2;}
double* newton_raphson_iter(double (*AF[])(double*, int), double *x_init, int n, double tol, int &iter) {
    double *x_old = copy_vect(x_init, n);
    double *x_new = new double[n];
    double *F = new double[n];
    double *dx = NULL;
    
    iter = 0;
    double error = tol + 1.0;

    while (error > tol) {
        for (int i = 0; i < n; i++) F[i] = -AF[i](x_old, n);
        
        double **J = jacobian_mat(AF, x_old, n); // Jacobiano por diferencias finitas
        dx = lu_forma2_sol(J, F, n);
        del_mat(J, n);
        
        if (dx == NULL) {
            print_error("Jacobiano singular en Newton-Raphson.");
            delete[] F; delete[] x_old; delete[] x_new;
            return NULL;
        }

        for (int i = 0; i < n; i++) x_new[i] = x_old[i] + dx[i];

        error = mod_vect(dx, n);
        for (int i = 0; i < n; i++) x_old[i] = x_new[i];
        
        iter++;
        delete[] dx; 
    }
    delete[] F; delete[] x_old;
    return x_new;
}

double* hist_vect_p1(double *datos, int n_datos, double *&dominio_out, int &n_out) {
    
    // Arrays temporales (el tamaño máximo posible es n_datos)
    double *temp_dom = new double[n_datos];
    int *temp_freq = new int[n_datos](); // Inicializado a 0
    int unicos = 0;

    // 1. Extraer el dominio único y contar apariciones
    for (int i = 0; i < n_datos; i++) {
        bool encontrado = false;
        for (int j = 0; j < unicos; j++) {
            if (fabs(datos[i] - temp_dom[j]) < 1e-4) { // Si ya existe en el dominio
                temp_freq[j]++;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            temp_dom[unicos] = datos[i];
            temp_freq[unicos] = 1;
            unicos++;
        }
    }

    // 2. Ordenar el dominio de menor a mayor (sincronizando las frecuencias)
    for (int i = 0; i < unicos - 1; i++) {
        for (int j = i + 1; j < unicos; j++) {
            if (temp_dom[j] < temp_dom[i]) {
                // Intercambiar dominio
                double tmp_d = temp_dom[i];
                temp_dom[i] = temp_dom[j];
                temp_dom[j] = tmp_d;
                // Intercambiar frecuencia
                int tmp_f = temp_freq[i];
                temp_freq[i] = temp_freq[j];
                temp_freq[j] = tmp_f;
            }
        }
    }

    // 3. Pasar a los arrays dinámicos definitivos con el tamaño exacto
    n_out = unicos;
    dominio_out = new double[unicos];
    double *frecuencias = new double[unicos];

    for (int i = 0; i < unicos; i++) {
        dominio_out[i] = temp_dom[i];
        frecuencias[i] = (double)temp_freq[i];
    }

    delete[] temp_dom;
    delete[] temp_freq;

    return frecuencias;
}
