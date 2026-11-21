matrix<double> Jacobi(matrix<double> A, matrix<double> b,
		      matrix<double> xinicial, double eps,
		      int & niter){
  niter = 0;  const int n = b.RowNo();
  matrix<double> C(n,n), Cinv(n,n); C.Null(); Cinv.Null();
  for(int i=0; i<n; i+=1){ C(i,i) = A(i,i); Cinv(i,i) = 1/A(i,i);}
  matrix<double> xa(n,1), x(n,1), I(n,n); I.Unit();

    xa = xinicial;
    x = Cinv * ( b + ( C - A ) * xa );
    niter+=1;
    while( ( x - xa ).Norm() > eps ){
      xa = x;
      x = Cinv * ( b + ( C - A ) * xa ); niter+=1;
    }
  
  return x;

}

matrix<double> GS(matrix<double> A, matrix<double> b,
		      matrix<double> xinicial, double eps,
		      int & niter){
  niter = 0;  const int n = b.RowNo();
  matrix<double> C(n,n), Cinv(n,n); C.Null(); Cinv.Null();
  for(int i=0; i<n; i+=1){ C(i,i) = A(i,i); Cinv(i,i) = 1/A(i,i);}
  matrix<double> xa(n,1), x(n,1), I(n,n); I.Unit();
  double sum1, sum2;

    xa = xinicial;
    //Obtencion de x
    for(int i=0; i<n ; i++){
      sum1 = 0;
      for(int j=0; j<=i-1; j+=1){ sum1 = sum1 + A(i,j)*x(j,0); }
      sum2 = 0;
      for(int j=i+1; j<=n-1; ++j){ sum2 = sum2 + A(i,j)*xa(j,0);}
      x(i,0) = (b(i,0) - sum1 - sum2)/A(i,i);
    }
    niter+=1;
    while( ( x - xa ).Norm() > eps ){
      xa = x;
      //Obtencion de x
      for(int i=0; i<n ; i++){
        sum1 = 0;
        for(int j=0; j<=i-1; j+=1){ sum1 = sum1 + A(i,j)*x(j,0); }
        sum2 = 0;
        for(int j=i+1; j<=n-1; ++j){ sum2 = sum2 + A(i,j)*xa(j,0);}
        x(i,0) = (b(i,0) - sum1 - sum2)/A(i,i);
      }
      niter=niter+1;
    }
  
  return x;

}

matrix<double> JacobiLU(matrix<double> A, matrix<double> b,
		      matrix<double> xinicial, double eps,
			int & niter, matrix<double> x_LU){
  niter = 0;  const int n = b.RowNo();
  matrix<double> C(n,n), Cinv(n,n); C.Null(); Cinv.Null();
  for(int i=0; i<n; i+=1){ C(i,i) = A(i,i); Cinv(i,i) = 1/A(i,i);}
  matrix<double> xa(n,1), x(n,1), I(n,n); I.Unit();

    xa = xinicial;
    x = Cinv * ( b + ( C - A ) * xa );
    niter+=1;
    while( ( x - x_LU ).Norm() > eps ){
      xa = x;
      x = Cinv * ( b + ( C - A ) * xa ); niter+=1;
    }
  
  return x;

}

matrix<double> GSLU(matrix<double> A, matrix<double> b,
		      matrix<double> xinicial, double eps,
		    int & niter, matrix<double> x_LU){
  niter = 0;  const int n = b.RowNo();
  matrix<double> C(n,n), Cinv(n,n); C.Null(); Cinv.Null();
  for(int i=0; i<n; i+=1){ C(i,i) = A(i,i); Cinv(i,i) = 1/A(i,i);}
  matrix<double> xa(n,1), x(n,1), I(n,n); I.Unit();
  double sum1, sum2;

    xa = xinicial;
    //Obtencion de x
    for(int i=0; i<n ; i++){
      sum1 = 0;
      for(int j=0; j<=i-1; j+=1){ sum1 = sum1 + A(i,j)*x(j,0); }
      sum2 = 0;
      for(int j=i+1; j<=n-1; ++j){ sum2 = sum2 + A(i,j)*xa(j,0);}
      x(i,0) = (b(i,0) - sum1 - sum2)/A(i,i);
    }
    niter+=1;
    while( ( x - x_LU ).Norm() > eps ){
      xa = x;
      //Obtencion de x
      for(int i=0; i<n ; i++){
        sum1 = 0;
        for(int j=0; j<=i-1; j+=1){ sum1 = sum1 + A(i,j)*x(j,0); }
        sum2 = 0;
        for(int j=i+1; j<=n-1; ++j){ sum2 = sum2 + A(i,j)*xa(j,0);}
        x(i,0) = (b(i,0) - sum1 - sum2)/A(i,i);
      }
      niter=niter+1;
    }
  
  return x;

}


