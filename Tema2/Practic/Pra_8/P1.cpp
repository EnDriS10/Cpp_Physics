
#include <C:/_Stuff/FFisica/2do/Cpp_Physics/Libreria/matclub.cpp>

double f1(double* r, int n = 3){
	return 3*r[0]- cos(r[1]*r[2]) -0.5 ;
}

double f2(double* r, int n = 3){
	return pow(r[0],2)- 81*pow((r[1] + 0.1),2)+sin(r[2]) + 1.06;
}
double f3(double* r, int n = 3){
	return exp(-r[0]*r[1]) + 20*r[2] + ( 10*PI(10) - 3 )/3;
}

int main() {
	double p0[3] = {1,1,1};
	double (*Sist[3])(double*, int) = {f1, f2,f3};

double *sol = newton_raphson_sys(Sist, p0, 3, 1e-8, 1e4);

	print_vect(sol,3,"Bacalado");

	return 0;
}


