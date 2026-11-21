matrix<double>  LU(matrix<double> A, matrix<double> b){
  const int n = b.RowNo();
  matrix<double> L(n,n),U(n,n),z(n,1),x(n,1);
  double sum;

  //Obtener L y U a partir de A = L * U
  for (int i=0; i<n ; i=i+1){
    for( int j=0; j<n; j+=1){
      if (i<j){
	L(i,j)=0;
	sum = 0;
	for(int k = 0; k<=i-1; k++){
	  sum = sum + L(i,k)*U(k,j);
	}
	U(i,j) = A(i,j) - sum;
	
      } else if (i == j){
	L(i,j) = 1;
	sum = 0;
	for(int k = 0; k<=i-1; k++){
	  sum = sum + L(i,k)*U(k,j);
	}
	U(i,j) = A(i,j) - sum;
	
      } else{
	U(i,j) = 0;
	sum = 0;
	for(int k=0; k<=j-1; ++k){
	  sum = sum + L(i,k)*U(k,j);
	}
	L(i,j) = ( A(i,j) - sum )/U(j,j);
	
      }
    }
  }
  //Comprobacion de que A = L * U
  //cout<<"Comprobacion A = L * U "<<endl;
  //cout<<A - (L * U)<<endl;

  //Obtener z a partir de L * z = b
  for(int i=0; i<n; i=i+1){
    sum = 0;
    for(int j=0; j<=i-1; j+=1){
      sum = sum + L(i,j)*z(j,0);
    }
    z(i,0) = b(i,0) - sum;
  }
  
  //cout<<"Comprobacion L z = b \n";
  //cout<<b - (L*z)<<endl;

  //Obtener x a partir de  U * x = z
  for(int i=n-1; i>=0; i=i-1){
    sum = 0;
    for(int j=i+1; j<=n-1; j++){
      sum = sum + U(i,j)*x(j,0);
    }
    x(i,0) = ( z(i,0) - sum )/U(i,i);

    //cout<<"Comprobacion U x = z \n";
    //cout<<(U*x)-z<<endl;
    
    
  }

  return x;
}
