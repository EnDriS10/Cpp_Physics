double biseccion(double a, double b, double eps, int & n, double f(double) ){
  n = 0;
  if (f(a) == 0) return a; if (f(b) == 0) {return b;}
  if (f(a)*f(b) > 0){ n = -1; return 0; }
  double xm;
  while( abs(b-a) > eps ){
    n = n + 1;
    xm = (a + b)/2;
    if( f(a)*f(xm) < 0 ){
      b = xm;
    } else if( f(xm)*f(b) < 0 ){ //f(a)*f(xm) > 0
      a = xm;
    } else{
      return xm;
    }
  }
  return xm;

}

double newton_raphson(double x0, double eps, int & n, double f(double), double Df(double) ){
  n = 0;
  if (f(x0) == 0 ) return x0;
  double xa, x;
  xa = x0;
  x = xa - f(xa)/Df(xa);  n+=1;
  while( abs(x - xa) > eps) {
    xa = x;
    x = xa - f(xa)/Df(xa);  n+=1;
  }
  return x;
}
double secante(double x0, double x1, double eps, int & n, double f(double) ){
  n = 0;
  if ( f(x0) == 0 ) return x0; if ( f(x1) == 0 ) return x1;
  double xaa, xa, x; xaa = x0; xa = x1;
  double delta = ( f(xa) - f(xaa) )/(xa - xaa);
  x = xa - f(xa)/delta; n = n + 1;
  while ( abs(x - xa) > eps ){
    xaa = xa; xa = x;
    delta = ( f(xa) - f(xaa) )/(xa - xaa);
    x = xa - f(xa)/delta; n = n + 1;
  }
  return x;
}
