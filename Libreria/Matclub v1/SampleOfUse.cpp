#include "matclub.cpp"

using namespace std;

int main() {
	int dim =3;
	double a_[dim] = {1,2,3} ; double b_[dim] = {3,2,0} ;
	
	double *a;  a= new double [dim];
	double *b;  b= new double [dim];
	
	for ( int i = 0; i<dim ; i++){
		a[i]= a_[i];
		b[i]= b_[i];		
	}
	
	
	double *c;
	c = suma_vect(a,b,dim);

	print_vect(c,dim,"bbesita");
	print_vect(tanh_vect(c,dim),dim,"bbesita");
	cout<<PI(3)<<endl;
	
	
	// Equivalente exacto a [v, x] = hist(datos, 10) en MATLAB
        double *x_centros;
        // Genera 10 barras automáticamente a partir de los datos
        double *frecuencias = hist_auto_vect(c, dim, 4, x_centros);
        
        print_vect(x_centros, 4, "Dominio (Centros)");
        print_vect(frecuencias, 4, "Frecuencias (v)");
	return 0;
}
