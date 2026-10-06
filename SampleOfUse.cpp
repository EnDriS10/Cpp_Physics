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
	cout<<PI(3);
	return 0;
}
